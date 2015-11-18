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

#include "line_opengl.hpp"

#include "glutils.hpp"
#include "../common/error_handling.hpp"


namespace cpe
{

line_opengl::line_opengl()
    :vbo_data(0),shader_id_data(0)
{}

void line_opengl::init()
{

    shader_id_data = read_shader("shaders/shader_line.vert","shaders/shader_line.frag");

    vec3 line[]={ {0.0f,0.0f,0.0f} , {1.0f,0.0f,0.0f} };
    glGenBuffers(1,&vbo_data);                                             PRINT_OPENGL_ERROR();

    ASSERT_CPE(vbo_data!=0,"Problem creating VBO");

    glBindBuffer(GL_ARRAY_BUFFER,vbo_data);                                PRINT_OPENGL_ERROR();
    glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),&line[0],GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();

    ASSERT_CPE(glIsBuffer(vbo_data),"Problem creating VBO");
}


line_opengl::~line_opengl()
{
    if(vbo_data!=0)
        glDeleteBuffers(1,&vbo_data);                                      PRINT_OPENGL_ERROR();
}

GLuint line_opengl::shader_id() const {return shader_id_data;}

void line_opengl::draw(vec3 const& p0,vec3 const& p1)
{

    glBindBuffer(GL_ARRAY_BUFFER,vbo_data);
    ASSERT_CPE(glIsBuffer(vbo_data),"vbo incorrect");

    vec3 line[]={p0,p1};

    glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),&line[0],GL_DYNAMIC_DRAW); PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();
    glDrawArrays(GL_LINES,0,2);
}

}
