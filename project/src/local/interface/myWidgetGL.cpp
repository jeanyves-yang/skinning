#include "myWidgetGL.hpp"

#include "GL/glew.h"
#include "GL/gl.h"

#include "../../lib/3d/mat4.hpp"
#include "../../lib/3d/mat3.hpp"

#include "../../lib/opengl/glutils.hpp"
#include "../../lib/common/error_handling.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include <cmath>
#include <iostream>
#include <unistd.h>


void myWidgetGL::paintGL()
{
    //compute current cameras
    setup_camera();

    //clear screen
    glViewport (0, 0, nav.screen_size_x(),nav.screen_size_y()); PRINT_OPENGL_ERROR();
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);                      PRINT_OPENGL_ERROR();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        PRINT_OPENGL_ERROR();

    //draw 3D scene
    if(draw_state)
        scene_3d.draw_scene();

    //draw indicating axes
    draw_axes();

}


void myWidgetGL::keyPressEvent(QKeyEvent *event)
{
    QString k=event->text();


    int current=event->key();
    Qt::KeyboardModifiers mod=event->modifiers();

    // We can quit the scene with 'Q'
    if( (mod&Qt::ShiftModifier)!=0 && (current==Qt::Key_Q) )
    {
        std::cout<<"\n[EXIT OK]\n\n"<<std::endl;
        this->window()->close();
    }

    QGLWidget::keyPressEvent(event);
    updateGL();

}



void myWidgetGL::mouseMoveEvent(QMouseEvent *event)
{
    int const x=event->x();
    int const y=event->y();

    int const ctrl_pressed  = (event->modifiers() & Qt::ControlModifier);
    int const shift_pressed = (event->modifiers() & Qt::ShiftModifier);

    // Left button controls the rotation
    if (!ctrl_pressed && !shift_pressed && (event->buttons() & Qt::LeftButton) )
        nav.trackball_rotate(x,y);

    // Right button controls the zoom
    if (!ctrl_pressed && !shift_pressed && (event->buttons() & Qt::RightButton))
        nav.trackball_zoom(y);

    // Shift+Left button controls the window translation (left/right, bottom/up)
    float const dL=0.0001f*(1+10*std::abs(nav.dist_cam()));
    if( !ctrl_pressed && shift_pressed && (event->buttons() & Qt::LeftButton) )
    {
        nav.go_up(dL*(y-nav.y_previous()));
        nav.go_right(-dL*(x-nav.x_previous()));
    }

    // Shift+Right button enables to translate forward/backward
    if( !ctrl_pressed && shift_pressed && (event->buttons() & Qt::RightButton) )
        nav.go_forward(5.0f*dL*(y-nav.y_previous()));


    nav.x_previous()=x;
    nav.y_previous()=y;

    updateGL(); PRINT_OPENGL_ERROR();

}


void myWidgetGL::timerEvent(QTimerEvent *event)
{
    event->accept();
    updateGL(); PRINT_OPENGL_ERROR();
}





myWidgetGL::myWidgetGL(const QGLFormat& format,QGLWidget *parent) :
    QGLWidget(format,parent),nav(),scene_3d(),draw_state(true)
{
    QWidget::setFocusPolicy(Qt::StrongFocus);
    startTimer(25); //start timer every 25ms
}

myWidgetGL::~myWidgetGL()
{}

void myWidgetGL::initializeGL()
{

    //Init OpenGL
    setup_opengl();

    //Init Scene 3D
    scene_3d.set_widget(this);
    scene_3d.load_scene();

    //Activate depth buffer
    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();
}

GLuint myWidgetGL::load_texture_file(std::string const& filename)
{
    if(access(filename.data(),F_OK) == -1)
    {
        std::cerr<<"Cannot load texture file "<<filename<<std::endl;
        std::cerr<<"Wrong path ?"<<std::endl;
        abort();
    }

    GLuint const value=bindTexture(QString(filename.data()), GL_TEXTURE_2D);

    if(value==0)
        throw cpe::exception_cpe("Failed to load texture "+filename,EXCEPTION_PARAMETERS_CPE);

    return value;
}

void myWidgetGL::setup_opengl()
{
    print_opengl_info();
    print_current_opengl_context();
    setup_glew();

    axes.init();
}

void myWidgetGL::setup_glew()
{
    //initialize Glew
    GLenum GlewInitResult=glewInit();
    //error handling
    if(GLEW_OK != GlewInitResult)
    {
        std::cerr<<"Error: "<<glewGetErrorString(GlewInitResult)<<std::endl;
        exit(EXIT_FAILURE);
    }
    //print debug info
    std::cout<<"Glew initialized ("<<glewGetString(GLEW_VERSION)<<")"<<std::endl;
}

void myWidgetGL::print_current_opengl_context() const
{
    std::cout<<"Current OpenGL context: "<< context()->format().majorVersion() << "." << context()->format().minorVersion()<<std::endl;
}

void myWidgetGL::change_draw_state()
{
    draw_state=!draw_state;
    updateGL();
}
void myWidgetGL::wireframe(bool const is_wireframe)
{
    if(is_wireframe==true)
    {glPolygonMode( GL_FRONT_AND_BACK, GL_LINE); PRINT_OPENGL_ERROR();}
    else
    {glPolygonMode( GL_FRONT_AND_BACK, GL_FILL); PRINT_OPENGL_ERROR();}

    updateGL();
}


void myWidgetGL::resizeGL(int const width,int const height)
{
    nav.screen_size_x()=width;
    nav.screen_size_y()=height;
    glViewport(0,0, width, height); PRINT_OPENGL_ERROR();
}

void myWidgetGL::mousePressEvent(QMouseEvent *event)
{
    nav.x_previous()=event->x();
    nav.y_previous()=event->y();

    updateGL(); PRINT_OPENGL_ERROR();
}




cpe::mat4 build_normal_matrix(const cpe::mat4& w)
{
    //the normal matrix is used to compute the transformation of the normals of the meshes
    cpe::mat4 normal_matrix=cpe::mat4(w(0,0),w(1,0),w(2,0),0,
                                      w(0,1),w(1,1),w(2,1),0,
                                      w(0,2),w(1,2),w(2,2),0,
                                      0,0,0,1);
    cpe::vec4 tr(w(0,3),w(1,3),w(2,3),1.0f);
    cpe::vec4 tr_inv=-normal_matrix*tr;
    normal_matrix(0,3)=tr_inv[0];
    normal_matrix(1,3)=tr_inv[1];
    normal_matrix(2,3)=tr_inv[2];

    normal_matrix=transposed(normal_matrix);

    return normal_matrix;
}

void myWidgetGL::setup_camera()
{
    // SETUP PROJECTION MATRIX
    cpe::mat4 projection_matrix;
    float const ratio=static_cast<float>(nav.screen_size_x())/nav.screen_size_y();
    projection_matrix.set_projection_perspective(55.0f*M_PI/180.0f,ratio,1e-3f,500.0f);

    // SETUP WORLD MATRIX (MODELVIEW)
    cpe::mat4 world_matrix_zoom; world_matrix_zoom.set_translation({0.0f,0.0f,nav.dist_cam()});
    cpe::mat4 world_matrix_translation; world_matrix_translation.set_translation(nav.camera_translation());
    cpe::mat4 world_matrix_rotation=nav.camera_orientation();
    cpe::mat4 world_matrix=world_matrix_zoom*world_matrix_rotation*world_matrix_translation;

    // SETUP NORMAL MATRIX
    cpe::mat4 normal_matrix=build_normal_matrix(world_matrix);

    camera_data={world_matrix,projection_matrix,normal_matrix};
}
cpe::camera_matrices const& myWidgetGL::camera() const
{
    return camera_data;
}

void myWidgetGL::draw_axes()
{
    glUseProgram(axes.shader_id());

    float const ratio=static_cast<float>(nav.screen_size_x())/nav.screen_size_y();
    cpe::mat4 const orientation=nav.camera_orientation();

    cpe::mat4 const scaling=cpe::mat4(1.0f,0.0f,0.0f,0.0f,
                                      0.0f,ratio,0.0f,0.0f,
                                      0.0f,0.0f,1.0f,0.0f,
                                      0.0f,0.0f,0.0f,1.0f);
    glUniformMatrix4fv(get_uni_loc(axes.shader_id(),"camera_modelview"),1,false,orientation.pointer()); PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(axes.shader_id(),"camera_projection"),1,false,scaling.pointer());    PRINT_OPENGL_ERROR();

    glClear(GL_DEPTH_BUFFER_BIT); PRINT_OPENGL_ERROR();

    glLineWidth(2.0);
    axes.draw();
    glLineWidth(1.0);
}
