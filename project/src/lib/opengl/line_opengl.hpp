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

#pragma once

#ifndef LINE_OPENGL_HPP
#define LINE_OPENGL_HPP

#include "../3d/vec3.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

namespace cpe
{

/** Helper class to draw line */
class line_opengl
{
public:

    line_opengl();
    ~line_opengl();

    /** Init the shaders and data for drawing a line */
    void init();
    /** Draw a line between p0 and p1 */
    void draw(vec3 const& p0,vec3 const& p1);

    /** The current id of the shader */
    GLuint shader_id() const;

private:
    /** The internal vbo storage */
    GLuint vbo_data;
    /** The shader id used to draw the lines */
    GLuint shader_id_data;
};

}

#endif
