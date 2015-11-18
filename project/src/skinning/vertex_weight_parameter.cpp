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


#include "vertex_weight_parameter.hpp"

#include "../lib/common/error_handling.hpp"
#include <cmath>

namespace cpe
{



vertex_weight_parameter::vertex_weight_parameter()
    :weight_data()
{}

int vertex_weight_parameter::size() const
{
    return WEIGHTS_PER_VERTEX;
}

skinning_weight const& vertex_weight_parameter::operator[](int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size(),"Index ("+std::to_string(index)+") must be less than the number of weight per vertex ("+std::to_string(size())+")");

    return weight_data[index];
}
skinning_weight& vertex_weight_parameter::operator[](int const index)
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<size(),"Index ("+std::to_string(index)+") must be less than the number of weight per vertex ("+std::to_string(size())+")");

    return weight_data[index];
}

std::array<skinning_weight,WEIGHTS_PER_VERTEX>::iterator vertex_weight_parameter::begin() {return weight_data.begin();}
std::array<skinning_weight,WEIGHTS_PER_VERTEX>::iterator vertex_weight_parameter::end()   {return weight_data.end();}
std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator vertex_weight_parameter::begin() const {return weight_data.begin();}
std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator vertex_weight_parameter::end() const   {return weight_data.end();}
std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator vertex_weight_parameter::cbegin() const{return weight_data.cbegin();}
std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator vertex_weight_parameter::cend() const  {return weight_data.cend();}

vertex_weight_parameter normalized(vertex_weight_parameter const& skinning_info)
{
    float total = 0.0f;
    for(skinning_weight const& s : skinning_info)
        total += s.weight;

    if(std::abs(total)<1e-3f)
        return skinning_info; //all the weights are almost zero

    vertex_weight_parameter new_skinning_info;
    int const N = skinning_info.size();
    for(int k=0 ; k<N ; ++k)
    {
        new_skinning_info[k].weight = skinning_info[k].weight/total;
        new_skinning_info[k].joint_id = skinning_info[k].joint_id;
    }
    return new_skinning_info;

}

}
