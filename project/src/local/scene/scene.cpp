

#include <GL/glew.h>

#include "scene.hpp"
#include "../../lib/opengl/glutils.hpp"

#include "../../lib/perlin/perlin.hpp"
#include "../../lib/3d/quaternion.hpp"

#include "../interface/myWidgetGL.hpp"

#include <cmath>


#include <string>
#include <sstream>
#include "../../lib/mesh/mesh_io.hpp"



using namespace cpe;


static cpe::mesh build_ground(float const L,float const h)
{
    mesh m;
    m.add_vertex(vec3(-L, h,-L));
    m.add_vertex(vec3(-L, h, L));
    m.add_vertex(vec3( L, h, L));
    m.add_vertex(vec3( L, h,-L));

    m.add_triangle_index({0,2,1});
    m.add_triangle_index({0,3,2});

    m.fill_color(vec3(0.8,0.9,0.8));

    return m;
}


static cpe::mesh_skinned build_cylinder(float const R, float const L, int const sample_size, int const sample_axis)
{
    mesh_skinned m;
    for(int i = 0; i< sample_axis;i++)
    {
         float z = L * i / sample_axis;
         for(int j = 0; j<sample_size;j++)
         {
             float x = cos(2 * M_PI * j / sample_size) * R;
             float y = sin(2 * M_PI * j / sample_size) * R;
             m.add_vertex(vec3(x,y,z));
         }
    }
    for(int i = 0; i < m.size_vertex()-sample_size-1; i++)
    {
        if(i!=sample_size-1)
        {
            m.add_triangle_index({i,i+1,i+1+sample_size});
            m.add_triangle_index({i,i+sample_size,i+1+sample_size});
        }
    }
    //exception
    for(int j = 0;j<sample_axis-1;j++)
    {
        m.add_triangle_index({j*sample_size,(j+1)*sample_size-1,(j+1)*sample_size});
        m.add_triangle_index({(j+1)*sample_size-1,(j+1)*sample_size,(j+2)*sample_size-1});
    }

    //caps
    for(int i = 0;i<sample_axis;i++)
    {
        m.add_vertex(vec3(0.0,0.0,L*i/sample_axis));
        for(int j = 0;j<sample_size;j++)
        {
            m.add_triangle_index({i*sample_size+j,i*sample_size+j+1,sample_axis*sample_size+i});
        }
        //exception
        m.add_triangle_index({(i+1)*sample_size-1,i*sample_size,sample_axis*sample_size+i});
    }
    m.fill_color(vec3(1.0,0.0,0.0));
    return m;
}


void scene::init_cylinder_sk(float const L, int const sample_axis)
{
    for(int i = 0; i<sample_axis;i++)
    {
        skeleton_joint j0;
        j0.orientation = quaternion(0,0,0,1);
        j0.position = vec3(0,0,L*i/sample_axis);
        sk_cylinder_bind_pose.push_back(j0);
        sk_cylinder_parent_id.push_back(i-1);
    }
}


void scene::load_scene()
{


    //*****************************************//
    // Preload default structure               //
    //*****************************************//
    texture_default = load_texture_file("data/white.jpg");
    shader_mesh     = read_shader("shaders/shader_mesh.vert",
                                  "shaders/shader_mesh.frag");           PRINT_OPENGL_ERROR();
    shader_skeleton = read_shader("shaders/shader_skeleton.vert",
                                  "shaders/shader_skeleton.frag");       PRINT_OPENGL_ERROR();


    //*****************************************//
    // Build ground
    //*****************************************//
    mesh_ground = build_ground(100.0f , -25.0f);
    mesh_ground.fill_empty_field_by_default();
    mesh_ground_opengl.fill_vbo(mesh_ground);

    float const r_cylinder = 4.0f;
    float const l_cylinder = 50.0f;
    int const sample_size = 6;
    int const sample_axis = 6;
    mesh_cylinder = build_cylinder(r_cylinder, l_cylinder,sample_size,sample_axis);
    mesh_cylinder.fill_empty_field_by_default();
    mesh_cylinder_opengl.fill_vbo(mesh_cylinder);

    init_cylinder_sk(l_cylinder, sample_axis);
}



void scene::draw_scene()
{

    setup_shader_skeleton(shader_skeleton);

    //Here we can draw skeletons as 3D segments

    setup_shader_mesh(shader_mesh);

    mesh_ground_opengl.draw();

    mesh_cylinder_opengl.draw();


}


void scene::setup_shader_mesh(GLuint const shader_id)
{
    //Setup uniform parameters
    glUseProgram(shader_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();

    //load white texture
    glBindTexture(GL_TEXTURE_2D,texture_default);                                                      PRINT_OPENGL_ERROR();
    glLineWidth(1.0f);                                                                                 PRINT_OPENGL_ERROR();

}

void scene::setup_shader_skeleton(GLuint const shader_id)
{
    //Setup uniform parameters
    glUseProgram(shader_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniform3f(get_uni_loc(shader_id,"color") , 0.0f,0.0f,0.0f);                                      PRINT_OPENGL_ERROR();

    //size of the lines
    glLineWidth(3.0f);                                                                                 PRINT_OPENGL_ERROR();
}

void scene::draw_skeleton(std::vector<vec3> const& positions) const
{
    // Create temporary a VBO to store data
    GLuint vbo_skeleton=0;
    glGenBuffers(1,&vbo_skeleton);                                                                     PRINT_OPENGL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER,vbo_skeleton);                                                        PRINT_OPENGL_ERROR();

    // Update data on the GPU
    glBufferData(GL_ARRAY_BUFFER , sizeof(vec3)*positions.size() , &positions[0] , GL_STATIC_DRAW);    PRINT_OPENGL_ERROR();

    // Draw data
    glEnableClientState(GL_VERTEX_ARRAY);                                                              PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, 0, 0);                                                                PRINT_OPENGL_ERROR();
    glDrawArrays(GL_LINES,0,positions.size());                                                         PRINT_OPENGL_ERROR();

    // Delete temporary VBO
    glDeleteBuffers(1,&vbo_skeleton);                                                                  PRINT_OPENGL_ERROR();
}

scene::scene()
    :shader_mesh(0)
{}


GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}


