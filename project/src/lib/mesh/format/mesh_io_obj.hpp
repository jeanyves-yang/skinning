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

#ifndef MESH_IO_OBJ_HPP
#define MESH_IO_OBJ_HPP

#include <vector>
#include "../../3d/vec3.hpp"
#include "../../3d/vec2.hpp"

namespace cpe
{

class mesh;

/** Load a mesh structure from a OFF file */
mesh load_mesh_file_obj(std::string const& filename);


/** An obj structure following the definition of an obj file */
struct obj_structure
{
    std::vector<vec3> data_vertex;    //the coordinates of vertices
    std::vector<vec2> data_texture;   //the coordinates of textures (optional)
    std::vector<vec3> data_normal;    //the coordinates of normals (optional)

    std::vector<std::vector<int>> data_face_vertex;  //the indices of the polygon of vertices
    std::vector<std::vector<int>> data_face_texture; //the indices of the polygon of texture (optional)
    std::vector<std::vector<int>> data_face_normal;  //the indices of the polygon of normal (optional)
};

/** Split a given string of face f from obj style into a set of values.
 *
 *  ex. 1/2 4/5 7/8 -> 1 2 4 5 7 8
 *      1/2/3 4/4/1 4/7/8 -> 1 2 3 4 4 1 4 7 8
 *      1//3 4//1 7//9 -> 1 3 4 1 7 9
 *      4 7 8 4 -> 4 7 8 4
 *
*/
std::vector<int> split_face_data(std::string const& face_data_str);

/** Read an obj file and return an obj structure. */
obj_structure load_file_obj_structure(std::string const& filename);


void read_vertex_obj(std::stringstream& tokens,obj_structure& obj);
void read_texture_obj(std::stringstream& tokens,obj_structure& obj);


}

#endif
