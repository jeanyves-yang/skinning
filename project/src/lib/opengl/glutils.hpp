/*
**    TP CPE Lyon
**    Copyright (C) 2015 David Odin & Damien Rohmer
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

#ifndef GL_UTILS_H
#define GL_UTILS_H

#include <vector>
#include <string>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/gl.h>


/** Macro indicating OpenGL errors (file and line) */
#define PRINT_OPENGL_ERROR() print_opengl_error(__FILE__, __LINE__)


/** Draw OpenGL Informations */
void print_opengl_info();

/** Print OpenGL Error given the information of the file and the line
 *  Function called by the macro PRINT_OPENGL_ERROR */
bool print_opengl_error(const char *file, int line);

/** Returns the OpenGL Version */
void get_gl_version(int *major, int *minor);

/** Look for a specific uniform variable in the shader */
GLint get_uni_loc(GLuint program, const GLchar *name);

/** Load a shader from a text file
  * 1st arg: Vertex shader file path
  * 2nd arg: Fragment shader file path
  * The argument can be the empty string "" when no shader should be loaded */
GLuint read_shader(std::string const&vertex_filename,
                   std::string const&fragment_filename);

/** Offset conversion for the VBO buffer (cast to a pointer) */
GLubyte* buffer_offset(int offset);

#endif
