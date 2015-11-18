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

#include "mesh_parametric.hpp"
#include "../common/error_handling.hpp"

namespace cpe
{

mesh_parametric::mesh_parametric()
    :mesh_basic(),size_u_data(0),size_v_data(0)
{}


void mesh_parametric::set_plane_xy_unit(int const size_u_param,int const size_v_param)
{
    ASSERT_CPE(size_u_param>0 && size_v_param>0 , "Problem of mesh size");
    size_u_data = size_u_param;
    size_v_data = size_v_param;

    //set data
    for(int kv=0 ; kv<size_v_param ; ++kv)
    {
        float const v = static_cast<float>(kv)/(size_v_param-1);
        for(int ku=0 ; ku<size_u_param ; ++ku)
        {
            float const u = static_cast<float>(ku)/(size_u_param-1);

            add_vertex( {u,v,0.0f} );
            add_texture_coord( {u,v} );
            add_normal( {0.0f,0.0f,1.0f} );
        }
    }

    //set connectivity
    for(int kv=0 ; kv<size_v_param-1 ; ++kv)
    {
        for(int ku=0 ; ku<size_u_param-1 ; ++ku)
        {
            int const offset = ku+size_u_param*kv;
            triangle_index tri0 = {offset,offset+1,offset+size_u_param+1};
            triangle_index tri1 = {offset,offset+size_u_param+1,offset+size_u_param};

            add_triangle_index(tri0);
            add_triangle_index(tri1);
        }
    }

    fill_empty_field_by_default();

    ASSERT_CPE(valid_mesh(),"Mesh is not valid");
}

int mesh_parametric::size_u() const {return size_u_data;}
int mesh_parametric::size_v() const {return size_v_data;}

vec3 mesh_parametric::vertex(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::vertex(offset);
}

vec3& mesh_parametric::vertex(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::vertex(offset);
}

vec3 mesh_parametric::normal(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::normal(offset);
}
vec3& mesh_parametric::normal(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::normal(offset);
}

vec3 mesh_parametric::color(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::color(offset);
}
vec3& mesh_parametric::color(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::color(offset);
}

vec2 mesh_parametric::texture_coord(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::texture_coord(offset);
}
vec2& mesh_parametric::texture_coord(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(ku >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(ku < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku+size_u_data*kv;
    return mesh_basic::texture_coord(offset);
}

bool mesh_parametric::valid_mesh() const
{
    int const total_size=size_u()*size_v();

    if(size_vertex()!=total_size ||
            size_color()!=total_size ||
            size_texture_coord()!=total_size ||
            size_normal()!=total_size )
    {
        std::cout<<"mesh parametric has incorrect data size"<<std::endl;
        return false;
    }

    return mesh_basic::valid_mesh();
}

}
