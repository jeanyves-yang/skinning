/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mesh_opengl.hpp"

#include "../mesh/mesh_basic.hpp"
#include "glutils.hpp"
#include "../common/error_handling.hpp"



namespace cpe
{

mesh_opengl::mesh_opengl()
    :vbo_vertex(0),vbo_normal(0),vbo_color(0),vbo_texture(0),vbo_index(0),number_of_triangles(0)
{

}

mesh_opengl::~mesh_opengl()
{
    delete_vbo();
}



void mesh_opengl::fill_vbo(mesh_basic const& m)
{
    if(m.valid_mesh()!=true)
        throw cpe::exception_cpe("Mesh is considered as invalid, cannot fill vbo",EXCEPTION_PARAMETERS_CPE);

    number_of_triangles=m.size_connectivity();
    if(number_of_triangles<=0)
        throw cpe::exception_cpe("incorrect number of triangles",MACRO_EXCEPTION_PARAMETER);

    //create the new vbo
    if(vbo_vertex==0)
    {glGenBuffers(1,&vbo_vertex);PRINT_OPENGL_ERROR();}
    ASSERT_CPE(vbo_vertex!=0,"Problem creation of VBO");

    if(vbo_normal==0)
    {glGenBuffers(1,&vbo_normal);PRINT_OPENGL_ERROR();}
    ASSERT_CPE(vbo_normal!=0,"Problem creation of VBO");

    if(vbo_color==0)
    {glGenBuffers(1,&vbo_color);PRINT_OPENGL_ERROR();}
    ASSERT_CPE(vbo_color!=0,"Problem creation of VBO");

    if(vbo_texture==0)
    {glGenBuffers(1,&vbo_texture);PRINT_OPENGL_ERROR();}
    ASSERT_CPE(vbo_texture!=0,"Problem creation of VBO");

    if(vbo_index==0)
    {glGenBuffers(1,&vbo_index);PRINT_OPENGL_ERROR();}
    ASSERT_CPE(vbo_index!=0,"Problem creation of VBO");



    //VBO vertex
    glBindBuffer(GL_ARRAY_BUFFER,vbo_vertex); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_vertex))
        throw cpe::exception_cpe("vbo_buffer incorrect",EXCEPTION_PARAMETERS_CPE);
    glBufferData(GL_ARRAY_BUFFER,3*sizeof(float)*m.size_vertex(),m.pointer_vertex(),GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

    //VBO normal
    glBindBuffer(GL_ARRAY_BUFFER,vbo_normal); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_normal))
        throw cpe::exception_cpe("vbo_normal incorrect",EXCEPTION_PARAMETERS_CPE);
    glBufferData(GL_ARRAY_BUFFER,3*sizeof(float)*m.size_normal(),m.pointer_normal(),GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

    //VBO color
    glBindBuffer(GL_ARRAY_BUFFER,vbo_color); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_color))
        throw cpe::exception_cpe("vbo_color incorrect",EXCEPTION_PARAMETERS_CPE);
    glBufferData(GL_ARRAY_BUFFER,3*sizeof(float)*m.size_color(),m.pointer_color(),GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

    //VBO texture
    glBindBuffer(GL_ARRAY_BUFFER,vbo_texture); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_texture))
        throw cpe::exception_cpe("vbo_texture incorrect",EXCEPTION_PARAMETERS_CPE);
    glBufferData(GL_ARRAY_BUFFER,2*sizeof(float)*m.size_texture_coord(),m.pointer_texture_coord(),GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

    //VBO index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo_index); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_index))
        throw cpe::exception_cpe("vbo_index incorrect",EXCEPTION_PARAMETERS_CPE);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*m.size_connectivity(),m.pointer_triangle_index(),GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

}

void mesh_opengl::delete_vbo()
{

    if(vbo_vertex!=0)
    {glDeleteBuffers(1,&vbo_vertex); PRINT_OPENGL_ERROR();}

    if(vbo_normal!=0)
    {glDeleteBuffers(1,&vbo_normal); PRINT_OPENGL_ERROR();}

    if(vbo_color!=0)
    {glDeleteBuffers(1,&vbo_color); PRINT_OPENGL_ERROR();}

    if(vbo_texture!=0)
    {glDeleteBuffers(1,&vbo_texture); PRINT_OPENGL_ERROR();}


    if(vbo_index!=0)
    {glDeleteBuffers(1,&vbo_index); PRINT_OPENGL_ERROR();}


}

void mesh_opengl::draw() const
{
    if(number_of_triangles<=0)
        throw cpe::exception_cpe("Incorrect number of triangles",EXCEPTION_PARAMETERS_CPE);


    glBindBuffer(GL_ARRAY_BUFFER,vbo_vertex); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_vertex))
        throw cpe::exception_cpe("vbo_vertex incorrect",EXCEPTION_PARAMETERS_CPE);
    glEnableClientState(GL_VERTEX_ARRAY); PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER,vbo_normal); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_normal))
        throw cpe::exception_cpe("vbo_normal incorrect",EXCEPTION_PARAMETERS_CPE);
    glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();
    glNormalPointer(GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER,vbo_color); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_color))
        throw cpe::exception_cpe("vbo_color incorrect",EXCEPTION_PARAMETERS_CPE);
    glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();
    glColorPointer(3,GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER,vbo_texture); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_texture))
        throw cpe::exception_cpe("vbo_texture incorrect",EXCEPTION_PARAMETERS_CPE);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();
    glTexCoordPointer(2,GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo_index); PRINT_OPENGL_ERROR();
    if(!glIsBuffer(vbo_index))
        throw cpe::exception_cpe("vbo_index incorrect",EXCEPTION_PARAMETERS_CPE);
    glDrawElements(GL_TRIANGLES, 3*number_of_triangles, GL_UNSIGNED_INT, 0); PRINT_OPENGL_ERROR();

}


void mesh_opengl::update_vbo_vertex(mesh_basic const& m)
{
    //VBO vertex
    glBindBuffer(GL_ARRAY_BUFFER,vbo_vertex); PRINT_OPENGL_ERROR();
    ASSERT_CPE(glIsBuffer(vbo_vertex),"vbo_buffer incorrect");

    glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float)*m.size_vertex(),m.pointer_vertex()); PRINT_OPENGL_ERROR();
}

void mesh_opengl::update_vbo_normal(mesh_basic const& m)
{
    //VBO vertex
    glBindBuffer(GL_ARRAY_BUFFER,vbo_normal); PRINT_OPENGL_ERROR();
    ASSERT_CPE(glIsBuffer(vbo_normal),"vbo_buffer incorrect");

    glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float)*m.size_normal(),m.pointer_normal()); PRINT_OPENGL_ERROR();
}

void mesh_opengl::update_vbo_color(mesh_basic const& m)
{
    //VBO vertex
    glBindBuffer(GL_ARRAY_BUFFER,vbo_color); PRINT_OPENGL_ERROR();
    ASSERT_CPE(glIsBuffer(vbo_color),"vbo_buffer incorrect");

    glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float)*m.size_color(),m.pointer_color()); PRINT_OPENGL_ERROR();
}

void mesh_opengl::update_vbo_texture(mesh_basic const& m)
{
    //VBO vertex
    glBindBuffer(GL_ARRAY_BUFFER,vbo_texture); PRINT_OPENGL_ERROR();
    ASSERT_CPE(glIsBuffer(vbo_texture),"vbo_buffer incorrect");

    glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float)*m.size_texture_coord(),m.pointer_texture_coord()); PRINT_OPENGL_ERROR();
}




}


