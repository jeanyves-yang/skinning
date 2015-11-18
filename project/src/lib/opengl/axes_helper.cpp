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

#include "axes_helper.hpp"

#include "glutils.hpp"
#include "../common/error_handling.hpp"

namespace cpe
{

axes_helper::axes_helper()
    :vbo_data(0),shader_id_data(0)
{}

void axes_helper::init()
{
    float const data[]={0.0f,0.0f,0.0f , 1.0f,0.0f,0.0f , // (p0,c0)
                        1.0f,0.0f,0.0f , 1.0f,0.0f,0.0f , // (pa,c0)

                        0.0f,0.0f,0.0f , 0.0f,1.0f,0.0f , // (p0,c1)
                        0.0f,1.0f,0.0f , 0.0f,1.0f,0.0f , // (pb,c1)

                        0.0f,0.0f,0.0f , 0.0f,0.0f,1.0f , // (p0,c2)
                        0.0f,0.0f,1.0f , 0.0f,0.0f,1.0f , // (pc,c2)
                       };

    //load shaders
    shader_id_data = read_shader("shaders/shader_axes.vert",
                                 "shaders/shader_axes.frag");

    ASSERT_CPE(vbo_data==0,"VBO should have initial value 0");
    glGenBuffers(1,&vbo_data); PRINT_OPENGL_ERROR();
    ASSERT_CPE(vbo_data!=0,"Problem initializing VBO");

    //Send data on the GPU
    glBindBuffer(GL_ARRAY_BUFFER,vbo_data);                               PRINT_OPENGL_ERROR();
    glBufferData(GL_ARRAY_BUFFER,12*3*sizeof(float),data,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
}

void axes_helper::draw() const
{
    ASSERT_CPE(vbo_data!=0,"VBO for Axes Helper should be initialized before been drawed");

    glBindBuffer(GL_ARRAY_BUFFER,vbo_data);                                         PRINT_OPENGL_ERROR();

    glEnableClientState(GL_VERTEX_ARRAY);                                           PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, 2*3*sizeof(float), 0);                             PRINT_OPENGL_ERROR();

    glEnableClientState(GL_COLOR_ARRAY);                                            PRINT_OPENGL_ERROR();
    glColorPointer(3, GL_FLOAT, 2*3*sizeof(float), buffer_offset(3*sizeof(float))); PRINT_OPENGL_ERROR();

    glDrawArrays(GL_LINES,0,6);                                                     PRINT_OPENGL_ERROR();
}

GLuint axes_helper::shader_id() const
{
    return shader_id_data;
}

}
