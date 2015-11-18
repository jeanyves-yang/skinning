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

#include "mesh.hpp"

#include "../common/error_handling.hpp"
#include "../3d/mat3.hpp"
#include "../3d/mat4.hpp"
#include "mesh_io.hpp"
#include <cmath>

namespace cpe
{


vec3 mesh::vertex(int const index) const                 {return mesh_basic::vertex(index);}
vec3& mesh::vertex(int const index)                      {return mesh_basic::vertex(index);}
vec3 mesh::normal(int const index) const                 {return mesh_basic::normal(index);}
vec3& mesh::normal(int const index)                      {return mesh_basic::normal(index);}
vec3 mesh::color(int const index) const                  {return mesh_basic::color(index);}
vec3& mesh::color(int const index)                       {return mesh_basic::color(index);}
vec2 mesh::texture_coord(int const index) const          {return mesh_basic::texture_coord(index);}
vec2& mesh::texture_coord(int const index)               {return mesh_basic::texture_coord(index);}
triangle_index mesh::connectivity(int const index) const {return mesh_basic::connectivity(index);}
triangle_index& mesh::connectivity(int const index)      {return mesh_basic::connectivity(index);}

void mesh::add_vertex(vec3 const& v)                     {mesh_basic::add_vertex(v);}
void mesh::add_normal(vec3 const& n)                     {mesh_basic::add_normal(n);}
void mesh::add_color(vec3 const& c)                      {mesh_basic::add_color(c);}
void mesh::add_texture_coord(vec2 const& t)              {mesh_basic::add_texture_coord(t);}
void mesh::add_triangle_index(triangle_index const& idx) {mesh_basic::add_triangle_index(idx);}

void mesh::load(std::string const& filename)
{
    *this = load_mesh_file(filename);
}

}
