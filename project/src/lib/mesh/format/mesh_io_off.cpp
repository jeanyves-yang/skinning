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

#include "mesh_io_off.hpp"
#include "../../common/error_handling.hpp"
#include "../../mesh/mesh.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


namespace cpe
{

mesh load_mesh_file_off(std::string const& filename)
{
    mesh m;

    std::vector<vec3> v_vertices;
    std::vector<int> v_connectivity;

    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_cpe("Cannot open file "+filename,EXCEPTION_PARAMETERS_CPE);

    std::string buffer;

    //find OFF header
    bool find_off=false;
    while(find_off==false)
    {
        if(!fid.good())
            throw exception_cpe("Cannot find OFF header in file "+filename,EXCEPTION_PARAMETERS_CPE);
        std::getline(fid,buffer);
        if(buffer.find("OFF")!=std::string::npos)
            find_off=true;
    }

    //read number of vertices + triangles
    int N_vertex=0,N_triangle=0;
    std::getline(fid,buffer);
    std::stringstream tokens(buffer);
    tokens>>N_vertex>>N_triangle;


    //read vertices
    for(int k=0;k<N_vertex;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        vec3 p;
        std::stringstream tokens_vertices(buffer);
        tokens_vertices>>p.x()>>p.y()>>p.z();

        v_vertices.push_back(p);
    }

    //read connectivity
    for(int k=0;k<N_triangle;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        int N_size,u0,u1,u2;
        std::stringstream tokens_connectivity(buffer);
        tokens_connectivity>>N_size>>u0>>u1>>u2;


        if(N_size!=3)
            throw exception_cpe("Cannot read OFF with non triangular faces for file "+filename,MACRO_EXCEPTION_PARAMETER);

        v_connectivity.push_back(u0);v_connectivity.push_back(u1);v_connectivity.push_back(u2);
    }

    fid.close();

    if(v_connectivity.size()%3!=0)
        throw exception_cpe("Problem with size of connectivity in file "+filename,EXCEPTION_PARAMETERS_CPE);

    for(int k=0,N=v_connectivity.size()/3;k<N;++k)
    {
        int const u0=v_connectivity[3*k+0];
        int const u1=v_connectivity[3*k+1];
        int const u2=v_connectivity[3*k+2];
        m.add_triangle_index({u0,u1,u2});
    }
    for(auto& p : v_vertices)
        m.add_vertex(p);

    m.fill_empty_field_by_default();

    ASSERT_CPE(m.valid_mesh(),"Mesh "+filename+" is invalid");

    return m;
}



}

