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

#ifndef AXES_HELPER_HPP
#define AXES_HELPER_HPP

#include "GL/glew.h"
#include "GL/gl.h"

namespace cpe
{

/** A container to draw 3D axes using OpenGL */
class axes_helper
{
public:
    axes_helper();

    /** Init axes and load OpenGL data */
    void init();
    /** Draw the axes */
    void draw() const;

    /** The associated shader id */
    GLuint shader_id() const;

private:

    /** Storage for the VBO on the GPU */
    GLuint vbo_data;
    /** Storage of the Shader ID */
    GLuint shader_id_data;

};
}

#endif
