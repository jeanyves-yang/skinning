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


#include "mesh_skinned.hpp"

#include "../lib/common/error_handling.hpp"
#include "../lib/mesh/mesh_io.hpp"
#include "skeleton_geometry.hpp"

#include <sstream>
#include <fstream>


namespace cpe
{

int mesh_skinned::size_vertex_weight() const
{
    return vertex_weight_data.size();
}

vertex_weight_parameter const& mesh_skinned::vertex_weight(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<int(vertex_weight_data.size()) , "Index ("+std::to_string(index)+") must be less than the current size of the weight vector ("+std::to_string(vertex_weight_data.size())+")");

    return vertex_weight_data[index];
}
vertex_weight_parameter& mesh_skinned::vertex_weight(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<int(vertex_weight_data.size()),"Index ("+std::to_string(index)+") must be less than the current size of the weight vector ("+std::to_string(vertex_weight_data.size())+")");

    return vertex_weight_data[index];
}

void mesh_skinned::add_vertex_weight(vertex_weight_parameter const& w)
{
    vertex_weight_data.push_back(w);
}


void mesh_skinned::load(std::string const& filename)
{
    //Warning: Can only handle meshes with same connectivity for vertex and textures
    //(Format de fichier de David Odin)

    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_cpe("Cannot open file "+filename,MACRO_EXCEPTION_PARAMETER);

    std::string buffer;

    std::vector<vertex_weight_parameter> skinning_info;


    //read the whole file
    while(fid.good()==true)
    {
        //read line
        std::getline(fid,buffer);

        if(buffer.size()>0)
        {
            std::stringstream tokens(buffer);
            std::string first_word;
            tokens >> first_word;

            //skip comments
            if(first_word.length()>0 && first_word[0]!='#')
            {
                //vertices
                if(first_word=="v")
                {
                  vec3 vertex;
                  tokens >> vertex.x();
                  tokens >> vertex.y();
                  tokens >> vertex.z();

                  add_vertex(vertex);
                }

                //texture
                if(first_word=="vt")
                {
                  vec2 texture;
                  tokens >> texture.x();
                  tokens >> texture.y();

                  add_texture_coord(texture);
                }

                // normal
                if(first_word=="vn")
                {
                  vec3 normal;
                  tokens >> normal.x();
                  tokens >> normal.y();
                  tokens >> normal.z();

                  add_normal(normal);
                }

                //skinning
                if(first_word=="sk")
                {
                    vertex_weight_parameter temp_skinning;
                    int const N_bone = temp_skinning.size();
                    for(int k_bone=0 ; k_bone<N_bone ; ++k_bone)
                    {
                        tokens >> temp_skinning[k_bone].joint_id;
                        tokens >> temp_skinning[k_bone].weight;
                    }
                    skinning_info.push_back(temp_skinning);
                }


                //read connectivity
                if(first_word=="f")
                {
                  std::string u0_str,u1_str,u2_str;
                  tokens >> u0_str >> u1_str >> u2_str;

                  int const u0 = std::stoi(u0_str)-1;
                  int const u1 = std::stoi(u1_str)-1;
                  int const u2 = std::stoi(u2_str)-1;

                  add_triangle_index({u0,u1,u2});

                }
            }

        }

    }

    fid.close();

    //add the skinning weights in the mesh structure
    for(auto const& s : skinning_info)
        add_vertex_weight(normalized(s));

    ASSERT_CPE(size_vertex_weight()==size_vertex(),"Mesh skinned seems to have the wrong number of skinning weights");

}


vec3 const& mesh_skinned::vertex_original(int index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<int(vertices_original_data.size()) , "Index ("+std::to_string(index)+") must be less than the current size of the vertex original vector ("+std::to_string(vertices_original_data.size())+")");

    return vertices_original_data[index];
}

void mesh_skinned::add_vertex(vec3 const& p)
{
    mesh::add_vertex(p);
    vertices_original_data.push_back(p);
}

void mesh_skinned::apply_skinning(skeleton_geometry const& skeleton)
{
    int const N_vertex = size_vertex();
    ASSERT_CPE(N_vertex==int(vertices_original_data.size()),"Incorrect size");

    for(int k_vertex=0 ; k_vertex<N_vertex ; ++k_vertex)
    {
        //TO DO: Calculer deformation par skinning
        //  vertex(k_vertex) = ...
    }

}

}
