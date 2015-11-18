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

#include "mesh_basic.hpp"

#include "../common/error_handling.hpp"
#include "../3d/mat3.hpp"
#include "../3d/mat4.hpp"
#include <cmath>

namespace cpe
{

mesh_basic::mesh_basic()
    :vertex_data(),normal_data(),color_data(),texture_coord_data(),connectivity_data()
{}

int mesh_basic::size_vertex() const {return vertex_data.size();}
int mesh_basic::size_normal() const {return normal_data.size();}
int mesh_basic::size_color() const {return color_data.size();}
int mesh_basic::size_texture_coord() const {return texture_coord_data.size();}
int mesh_basic::size_connectivity() const {return connectivity_data.size();}

vec3 mesh_basic::vertex(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_vertex(),"Index ("+std::to_string(index)+") must be less than the current size of the vertices ("+std::to_string(size_vertex())+")");

    return vertex_data[index];
}
vec3& mesh_basic::vertex(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_vertex(),"Index ("+std::to_string(index)+") must be less than the current size of the vertices ("+std::to_string(size_vertex())+")");

    return vertex_data[index];
}

vec3 mesh_basic::normal(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_normal(),"Index ("+std::to_string(index)+") must be less than the current size of the normals ("+std::to_string(size_normal())+")");

    return normal_data[index];
}
vec3& mesh_basic::normal(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_normal(),"Index ("+std::to_string(index)+") must be less than the current size of the normals ("+std::to_string(size_normal())+")");

    return normal_data[index];
}

vec3 mesh_basic::color(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_color(),"Index ("+std::to_string(index)+") must be less than the current size of the colors ("+std::to_string(size_color())+")");

    return color_data[index];
}
vec3& mesh_basic::color(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_color(),"Index ("+std::to_string(index)+") must be less than the current size of the colors ("+std::to_string(size_color())+")");

    return color_data[index];
}

vec2 mesh_basic::texture_coord(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_texture_coord(),"Index ("+std::to_string(index)+") must be less than the current size of the texture coordinates ("+std::to_string(size_texture_coord())+")");

    return texture_coord_data[index];
}
vec2& mesh_basic::texture_coord(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_texture_coord(),"Index ("+std::to_string(index)+") must be less than the current size of the texture coordinates ("+std::to_string(size_texture_coord())+")");

    return texture_coord_data[index];
}

triangle_index mesh_basic::connectivity(int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_connectivity(),"Index ("+std::to_string(index)+") must be less than the current size of the connectivity ("+std::to_string(size_connectivity())+")");

    return connectivity_data[index];
}
triangle_index& mesh_basic::connectivity(int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size_connectivity(),"Index ("+std::to_string(index)+") must be less than the current size of the connectivity ("+std::to_string(size_connectivity())+")");

    return connectivity_data[index];
}

void mesh_basic::add_vertex(vec3 const& v)
{
    vertex_data.push_back(v);
}

void mesh_basic::add_normal(vec3 const& n)
{
    normal_data.push_back(n);
}

void mesh_basic::add_color(vec3 const& c)
{
    color_data.push_back(c);
}

void mesh_basic::add_texture_coord(vec2 const& t)
{
    texture_coord_data.push_back(t);
}

void mesh_basic::add_triangle_index(triangle_index const& idx)
{
    connectivity_data.push_back(idx);
}


void mesh_basic::fill_color(vec3 const& c)
{
    if(size_color()!=size_vertex())
        color_data.resize(size_vertex());

    for(auto& col : color_data)
        col=c;
}

void mesh_basic::fill_color_xyz()
{
    int const N=size_vertex();

    if(size_color()!=N)
        color_data.resize(N);

    vec3 p_min,p_max;
    compute_mesh_aabb_extremities(p_min,p_max);

    //diagonal linking the two extremities
    vec3 d=p_max-p_min;

    //ensure a non zero size
    for(int k_dim=0;k_dim<3;++k_dim)
        if(d[k_dim]<1e-6)
            d[k_dim]=1.0f;

    //fill the color vector
    for(int k=0;k<N;++k)
    {
        //normalize the color (black at p_min, and white at p_max)
        vec3 p=vertex(k)-p_min;
        color(k) = vec3(p.x()/d.x(),p.y()/d.y(),p.z()/d.z());
    }

}

void mesh_basic::fill_color_normal()
{
    int const N=size_vertex();

    if(size_color()!=N)
        color_data.resize(N);

    //fill the color value with c=|n|
    for(int k=0;k<N;++k)
    {
        vec3 const& n=normal(k);
        color(k) = vec3(std::abs(n.x()),std::abs(n.y()),std::abs(n.z()));
    }
}

void mesh_basic::fill_normal()
{
    int const N_vertex=size_vertex();
    if(size_normal()!=N_vertex)
        normal_data.resize(N_vertex);

    //init normal data to 0
    for(auto& n : normal_data)
        n=vec3();

    //walk through all the triangles and add each triangle normal to the vertices
    int const N_triangle=size_connectivity();
    for(int k_triangle=0;k_triangle<N_triangle;++k_triangle)
    {
        //get current triangle index
        triangle_index const& tri=connectivity(k_triangle);

        //check that the index given have correct values
        ASSERT_CPE(tri.u0()>=0 && tri.u0()<N_vertex,"Incorrect triangle index");
        ASSERT_CPE(tri.u1()>=0 && tri.u1()<N_vertex,"Incorrect triangle index");
        ASSERT_CPE(tri.u2()>=0 && tri.u2()<N_vertex,"Incorrect triangle index");

        //compute current normal
        vec3 const& p0=vertex(tri.u0());
        vec3 const& p1=vertex(tri.u1());
        vec3 const& p2=vertex(tri.u2());

        vec3 const u1=normalized(p1-p0);
        vec3 const u2=normalized(p2-p0);
        vec3 const n=normalized(cross(u1,u2));

        //add the computed normal to the normal_data
        for(int kv=0;kv<3;++kv)
            normal_data[tri[kv]] += n;
    }

    //normalize all normal value
    for(auto& n : normal_data)
        n=normalized(n);

}

void mesh_basic::transform_opposite_normal_orientation()
{
    for(auto& n : normal_data)
        n=-n;
}

void mesh_basic::transform_apply_matrix(mat3 const& T)
{
    for(auto& p : vertex_data)
        p=T*p;
}

void mesh_basic::transform_apply_matrix(mat4 const& T)
{
    for(auto& p : vertex_data)
        p=T*p;
}

void mesh_basic::transform_apply_auto_scale_and_center()
{

    vec3 corner_min,corner_max;
    compute_mesh_aabb_extremities(corner_min,corner_max);
    vec3 const center=(corner_min+corner_max)/2;
    vec3 const d=corner_max-corner_min;

    transform_apply_translation(-center);
    float const s=std::max(std::max(d.x(),d.y()),d.z());
    if(s>1e-6f)
        transform_apply_scale(1.0f/s);
}

void mesh_basic::transform_apply_scale(float const s)
{
    for(auto& p : vertex_data)
        p=s*p;
}

void mesh_basic::transform_apply_scale(float const sx,float const sy,float const sz)
{
    for(vec3& p : vertex_data)
    {
        p.x()*=sx;
        p.y()*=sy;
        p.z()*=sz;
    }
}

void mesh_basic::transform_apply_translation(vec3 const& t)
{
    for(vec3& p : vertex_data)
        p+=t;
}

void mesh_basic::transform_apply_rotation(vec3 const& axis,float const angle)
{
    mat3 R;R.set_rotation(axis,angle);
    for(vec3& p : vertex_data)
        p=R*p;
}

bool mesh_basic::valid_mesh() const
{
    //mesh_basic should have at least one vertex
    if(size_vertex()<=0)
    {
        std::cout<<"mesh_basic has 0 vertex"<<std::endl;
        return false;
    }
    //mesh_basic should have at least one triangle
    if(size_connectivity()<=0)
    {
        std::cout<<"Connectivity has size 0";
        return false;
    }

    //mesh_basic should identical size for vertex, normal, color and texture_coord
    if(size_vertex()!=size_normal())
    {
        std::cout<<"Normal size is different than vertex size"<<std::endl;
        return false;
    }
    if(size_vertex()!=size_color())
    {
        std::cout<<"Normal size is different than color size"<<std::endl;
        return false;
    }
    if(size_vertex()!=size_texture_coord())
    {
        std::cout<<"Normal size is different than texture_coord size"<<std::endl;
        return false;
    }

    //vertices should not have too large coordinates
    for(int k=0,N=size_vertex();k<N;++k)
    {
        vec3 const& p=vertex_data[k];
        if(std::abs(p.x())>50000 || std::abs(p.y())>50000 || std::abs(p.z())>50000)
        {
            std::cout<<"Vertex "<<k<<" ("<<p<<") has very large size"<<std::endl;
            return false;
        }
    }

    //normals should be normalized
    for(int k=0,N=size_normal();k<N;++k)
    {
        vec3 const& n=normal_data[k];
        if(std::abs(norm(n)-1.0f)>1e-6f)
        {
            std::cout<<"Normal "<<k<<"("<<n<<") is not normalized"<<std::endl;
            return false;
        }
    }

    //color components should be in [0,1]
    for(int k=0,N=size_color();k<N;++k)
    {
        vec3 const& c=color_data[k];
        if(c.x()<0 || c.x()>1 || c.y()<0 || c.y()>1 || c.z()<0 || c.z()>1)
        {
            std::cout<<"Color "<<k<<"("<<c<<") has values outside [0,1]"<<std::endl;
            return false;
        }
    }

    //all triangle indices should be in the vertex list with non degenerated triangle
    int const N_vertex=size_vertex();
    for(int k=0,N=size_connectivity();k<N;++k)
    {
        triangle_index const& tri = connectivity_data[k];
        int const u0=tri.u0();
        int const u1=tri.u1();
        int const u2=tri.u2();

        if(u0==u1 || u0==u2 || u1==u2)
        {
            std::cout<<"Triangle index "<<k<<" ("<<tri<<") is degenerated"<<std::endl;
            return false;
        }

        if(u0<0 || u1<0 || u2<0 || u0>=N_vertex || u1>=N_vertex || u2>=N_vertex)
        {
            std::cout<<"Triangle index "<<k<<" ("<<tri<<") has incorrect value with respect to the current vertex list of size "<<N_vertex<<std::endl;
            return false;
        }
    }

    return true;

}

float const* mesh_basic::pointer_vertex() const
{
    ASSERT_CPE(size_vertex()>0,"No vertex");
    return vertex_data[0].pointer();
}
float const* mesh_basic::pointer_normal() const
{
    ASSERT_CPE(size_normal()>0,"No normal");
    return normal_data[0].pointer();
}
float const* mesh_basic::pointer_color() const
{
    ASSERT_CPE(size_color()>0,"No color");
    return color_data[0].pointer();
}
float const* mesh_basic::pointer_texture_coord() const
{
    ASSERT_CPE(size_texture_coord()>0,"No texture coord");
    return texture_coord_data[0].pointer();
}
int const* mesh_basic::pointer_triangle_index() const
{
    ASSERT_CPE(size_connectivity()>0,"No connectivity");
    return connectivity_data[0].pointer();
}

void mesh_basic::fill_empty_field_by_default()
{
    int const N_vertex=size_vertex();

    if(size_normal()!=N_vertex)
        fill_normal();
    ASSERT_CPE(size_normal()==N_vertex,"Invalid normal computation");

    if(size_color()!=N_vertex)
        fill_color({0.8f,0.8f,0.8f});
    ASSERT_CPE(size_color()==N_vertex,"Invalid color set up");

    if(size_texture_coord()!=N_vertex)
    {
        texture_coord_data.clear();
        for(int k=0;k<N_vertex;++k)
            add_texture_coord({0.0f,0.0f});
    }

}

void mesh_basic::compute_mesh_aabb_extremities(vec3& corner_min,vec3& corner_max)
{
    int const N=size_vertex();
    if(N==0) return ;
    corner_min=vertex(0);
    corner_max=vertex(0);
    for(int k=1;k<N;++k)
    {
        vec3 const& p=vertex(k);
        for(int k_dim=0;k_dim<3;++k_dim)
        {
            if(p[k_dim]<corner_min[k_dim]) corner_min[k_dim]=p[k_dim];
            if(p[k_dim]>corner_max[k_dim]) corner_max[k_dim]=p[k_dim];
        }
    }
}




}
