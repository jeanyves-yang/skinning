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

#ifndef MESH_HPP
#define MESH_HPP


#include "mesh_basic.hpp"


namespace cpe
{
class mat3;
class mat4;

/** A derivated class for mesh_basic giving public access to modifier */
class mesh : public mesh_basic
{
public:

    using mesh_basic::mesh_basic;


    vec3 vertex(int index) const;
    vec3& vertex(int index);
    vec3 normal(int index) const;
    vec3& normal(int index);
    vec3 color(int index) const;
    vec3& color(int index);
    vec2 texture_coord(int index) const;
    vec2& texture_coord(int index);
    triangle_index connectivity(int index) const;
    triangle_index& connectivity(int index);

    void add_vertex(vec3 const& v);
    void add_normal(vec3 const& n);
    void add_color(vec3 const& c);
    void add_texture_coord(vec2 const& t);
    void add_triangle_index(triangle_index const& idx);

    void load(std::string const& filename);

};

}


#endif
