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

#ifndef MESH_BASIC_HPP
#define MESH_BASIC_HPP

#include "../3d/vec3.hpp"
#include "../3d/vec2.hpp"
#include "triangle_index.hpp"

#include <vector>


namespace cpe
{
class mat3;
class mat4;

/** Basic container for a triangular mesh structure.
 * Used as a parent class for other mesh classes.
 * The mesh contains:
 * - a vector of 3D vertices
 * - 1 normal per vertex
 * - 1 color (r,g,b) per vertex
 * - 1 texture coordinate (u,v) per vertex
*/
class mesh_basic
{
public:

    mesh_basic();

    /******************************************/
    // Size
    /******************************************/

    /** Give the number of vertices */
    int size_vertex() const;
    /** Give the number of normals */
    int size_normal() const;
    /** Give the number of colors */
    int size_color() const;
    /** Give the number of texture coordinates */
    int size_texture_coord() const;
    /** Give the number of triangles */
    int size_connectivity() const;

    /******************************************/
    // FILLING
    /******************************************/

    /** Fill the mesh with a uniform color (r,g,v). Each component is between [0,1]. */
    void fill_color(vec3 const& c);
    /** Fill the mesh with color depending on its (x,y,z) coordinates. */
    void fill_color_xyz();
    /** Fill the mesh with color depending on its normal coordinates. */
    void fill_color_normal();

    /** Fill automatically the normals of the mesh. */
    void fill_normal();

    /** Fill all the fields (normal, color, texture, etc) if they are not already filled. */
    void fill_empty_field_by_default();


    /******************************************/
    // Deformations
    /******************************************/

    /** Inverse all the normals */
    void transform_opposite_normal_orientation();
    /** Multiply all the vertices by the given matrix */
    void transform_apply_matrix(mat3 const& T);
    /** Multiply all the vertices by the given matrix */
    void transform_apply_matrix(mat4 const& T);
    /** Center the mesh around the origin and set its maximal size in x,y or z direction to 1. */
    void transform_apply_auto_scale_and_center();
    /** Scale the mesh */
    void transform_apply_scale(float s);
    /** Scale the mesh */
    void transform_apply_scale(float sx,float sy,float sz);
    /** Translate the mesh */
    void transform_apply_translation(vec3 const& t);
    /** Rotate the mesh */
    void transform_apply_rotation(vec3 const& axis,float angle);

    /******************************************/
    // Pointers
    /******************************************/

    /** Get a pointer on the vertices (for OpenGL) */
    float const* pointer_vertex() const;
    /** Get a pointer on the normals (for OpenGL) */
    float const* pointer_normal() const;
    /** Get a pointer on the color (for OpenGL) */
    float const* pointer_color() const;
    /** Get a pointer on the textures (for OpenGL) */
    float const* pointer_texture_coord() const;
    /** Get a pointer on the indices of the triangles (for OpenGL) */
    int const* pointer_triangle_index() const;



    bool valid_mesh() const;

protected:

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

    /** Compute the two extremities of the Axis Aligned Bounding Box */
    void compute_mesh_aabb_extremities(vec3& corner_min,vec3& corner_max);


protected:


    /** Internal storage for the vertices */
    std::vector<vec3> vertex_data;
    /** Internal storage for the normals */
    std::vector<vec3> normal_data;
    /** Internal storage for the colors */
    std::vector<vec3> color_data;
    /** Internal storage for the texture coordinates */
    std::vector<vec2> texture_coord_data;

    /** Internal storage for the triangles indices */
    std::vector<triangle_index> connectivity_data;
};

}


#endif
