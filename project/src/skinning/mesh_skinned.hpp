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

#ifndef MESH_SKINNED_HPP
#define MESH_SKINNED_HPP

#include "vertex_weight_parameter.hpp"
#include "../lib/mesh/mesh.hpp"


namespace cpe
{

class skeleton_geometry;

/** A derived class of mesh with skinning weight information per vertex
    Note that the class store twice the vertices:
     - Once to store the deformed vertices after appliccation of the skinning (access with standard .vertex(index)).
     - Another time to always store the original position of the vertices to enable several application of the skinning.
*/
class mesh_skinned : public mesh
{
public:

    using mesh::mesh;

    /** Access to the skinning weights associated to a given vertex */
    vertex_weight_parameter const& vertex_weight(int index) const;
    /** Access to the skinning weights associated to a given vertex */
    vertex_weight_parameter& vertex_weight(int index);

    /** Access to original vertex */
    vec3 const& vertex_original(int index) const;

    /** Add a vertex both as an original position and in the default vertex storage
        \note overloading of the add_vertex method of mesh
    */
    void add_vertex(vec3 const& p);

    /** Add skinning weights information to the data structure (in the same order than the vertices) */
    void add_vertex_weight(vertex_weight_parameter const& w);

    /** Size of the vertex weights information (should be equals to size_vertex() when all the informations are provided) */
    int size_vertex_weight() const;

    /** Load a mesh with its skinning information from a given file
     * \note Only handle custom 'obj' file with same connectivity for vertex, normals, texture, and skinning weights.
    */
    void load(std::string const& filename);

    /** Apply the skinning deformation using a given skeleton deformation
     * \note The skeleton should store the matrices T*B^{-1}, where T is the
     * global frame of the joint, and B is the bind pose of the joint in the local frame.
    */
    void apply_skinning(skeleton_geometry const& skeleton);

private:

    /** Internal storage for the original vertices positions.
     *  These positions are not modified when applying the skinning.
    */
    std::vector<vec3> vertices_original_data;

    /** Internal storage for the vertex weight information*/
    std::vector<vertex_weight_parameter> vertex_weight_data;
};



}

#endif
