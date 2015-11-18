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

#include "mesh_io_obj.hpp"
#include "../../common/error_handling.hpp"
#include "../../mesh/mesh.hpp"

#include <sstream>
#include <fstream>
#include <assert.h>
#include <map>

namespace cpe
{

std::vector<int> split_face_data(std::string const& face_data_str)
{
    std::vector<int> data;
    std::string current_str=face_data_str;

    while(current_str.length()>0)
    {
        while(current_str.length()>0 && current_str[0]=='/')
        {
            std::string temp_str=current_str.substr(1,current_str.length()-1);
            current_str=temp_str;
        }

        int value;
        std::stringstream tokenizer(current_str);
        tokenizer>>value;
        data.push_back(value);

        std::string residual;
        tokenizer>>residual;

        current_str=residual;
    }

    return data;
}

void read_vertex_obj(std::stringstream& tokens,obj_structure& obj)
{
    vec3 v;
    tokens >> v.x();
    tokens >> v.y();
    tokens >> v.z();
    obj.data_vertex.push_back(v);
}

void read_texture_obj(std::stringstream& tokens,obj_structure& obj)
{
    vec2 t;
    tokens >> t.x();
    tokens >> t.y();
    obj.data_texture.push_back(t);
}

void read_normal_obj(std::stringstream& tokens,obj_structure& obj)
{
    vec3 n;
    tokens >> n.x();
    tokens >> n.y();
    tokens >> n.z();
    obj.data_normal.push_back(n);
}

void read_face_obj(std::stringstream& tokens,obj_structure& obj)
{
    std::vector<std::vector<int> > face_data;
    while(tokens.good())
    {
        std::string polygon_index_str;
        tokens >> polygon_index_str;

        std::vector<int> const current_data=split_face_data(polygon_index_str);
        face_data.push_back(current_data);
    }

    std::vector<int> temp_vertex;
    std::vector<int> temp_texture;
    std::vector<int> temp_normal;
    for(auto const& index_face : face_data)
    {
        int const N_dim=index_face.size();
        for(int k_dim=0;k_dim<N_dim;++k_dim)
        {
            int const value=index_face[k_dim];

            switch(k_dim)
            {
            case 0:
                temp_vertex.push_back(value-1);
                break;
            case 1:
                temp_texture.push_back(value-1);
                break;
            case 2:
                temp_normal.push_back(value-1);
                break;
            default:
                std::cerr<<"Error reading file "<<std::endl;
                exit(1);
            }
        }
    }

    if(temp_vertex.size()>0)
        obj.data_face_vertex.push_back(temp_vertex);
    if(temp_texture.size()>0)
        obj.data_face_texture.push_back(temp_texture);
    if(temp_normal.size()>0)
        obj.data_face_normal.push_back(temp_normal);
}

obj_structure load_file_obj_structure(std::string const& filename)
{
    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_cpe("Cannot open file "+filename,MACRO_EXCEPTION_PARAMETER);

    std::string buffer;

    obj_structure structure;

    //read the whole file
    while(fid.good()==true)
    {
        //read line
        std::getline(fid,buffer);

        if(buffer.size()>0)
        {
            std::stringstream tokens_buffer(buffer);
            std::string first_word;
            tokens_buffer>>first_word;

            //skip comments
            if(first_word.length()>0 && first_word[0]!='#')
            {
                //vertices
                if(first_word=="v")
                    read_vertex_obj(tokens_buffer,structure);

                //texture
                if(first_word=="vt")
                    read_texture_obj(tokens_buffer,structure);

                //normal
                if(first_word=="vn")
                    read_normal_obj(tokens_buffer,structure);

                //connectivity
                if(first_word=="f")
                    read_face_obj(tokens_buffer,structure);
            }

        }

    }

    fid.close();

    return structure;
}



mesh load_mesh_file_obj(const std::string& filename)
{
    mesh mesh_loaded;

    obj_structure obj=load_file_obj_structure(filename);

    bool is_vertex=obj.data_vertex.size()>0 && obj.data_face_vertex.size()>0;
    bool is_normal=obj.data_normal.size()>0 && obj.data_face_normal.size()>0;
    bool is_texture=obj.data_texture.size()>0 && obj.data_face_texture.size()>0;



    if(is_vertex && !is_normal && !is_texture)
    {
        int const N_face=obj.data_face_vertex.size();
        for(int k_face=0;k_face<N_face;++k_face)
        {
            auto const& polygon=obj.data_face_vertex[k_face];
            int const dim=polygon.size();

            assert(dim>=2);
            for(int k=2;k<dim;++k)
                mesh_loaded.add_triangle_index({polygon[0],polygon[1],polygon[k]});
        }

        int const N_vertex=obj.data_vertex.size();
        for(int k_vertex=0;k_vertex<N_vertex;++k_vertex)
            mesh_loaded.add_vertex(obj.data_vertex[k_vertex]);
    }

    if((is_vertex && !is_normal && is_texture) || (is_vertex && is_normal && is_texture) )//note: normal are not read
    {
        std::vector<vec3> data_vertex;
        std::vector<vec2> data_texture;

        std::map<int,int> map_vertex;
        std::map<int,int> map_texture;
        long int counter_max=0;

        int const N_face=obj.data_face_vertex.size();
        assert(static_cast<int>(obj.data_face_texture.size())==N_face);
        for(int k_face=0;k_face<N_face;++k_face)
        {
            std::vector<int> const& face_vertex=obj.data_face_vertex[k_face];
            std::vector<int> const& face_texture=obj.data_face_texture[k_face];

            int const dim=face_vertex.size();
            assert(dim>2);
            assert(static_cast<int>(face_texture.size())==dim);
            for(int k_dim=0;k_dim<dim;++k_dim)
            {
                int const idx_vertex=face_vertex[k_dim];
                int const idx_texture=face_texture[k_dim];

                std::map<int,int>::const_iterator it_vertex=map_vertex.find(idx_vertex);
                std::map<int,int>::const_iterator it_texture=map_texture.find(idx_texture);

                if(it_vertex==map_vertex.end() || it_texture==map_texture.end())
                {
                    map_vertex[idx_vertex]=counter_max;
                    map_texture[idx_texture]=counter_max;

                    counter_max++;

                    assert(static_cast<int>(obj.data_vertex.size())>idx_vertex);
                    assert(static_cast<int>(obj.data_texture.size())>idx_texture);

                    mesh_loaded.add_vertex(obj.data_vertex[idx_vertex]);
                    mesh_loaded.add_texture_coord(obj.data_texture[idx_texture]);

                    data_vertex.push_back(obj.data_vertex[idx_vertex]);
                    data_texture.push_back(obj.data_texture[idx_texture]);

                    assert(static_cast<int>(data_vertex.size())==counter_max);
                    assert(static_cast<int>(data_texture.size())==counter_max);
                }
            }

            int const index_0=map_vertex[face_vertex[0]];
            for(int k_dim=1;k_dim<dim-1;++k_dim)
            {
                int const index_1=map_vertex[face_vertex[k_dim]];
                int const index_2=map_vertex[face_vertex[k_dim+1]];
                mesh_loaded.add_triangle_index({index_0,index_1,index_2});
            }

        }
    }

    mesh_loaded.fill_empty_field_by_default();
    ASSERT_CPE(mesh_loaded.valid_mesh(),"Mesh is invalid");

    return mesh_loaded;

}

}

