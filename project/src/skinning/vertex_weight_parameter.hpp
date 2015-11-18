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

#ifndef VERTEX_WEIGHT_PARAMETER_HPP
#define VERTEX_WEIGHT_PARAMETER_HPP

#include "skinning_weight.hpp"
#include <array>

#define WEIGHTS_PER_VERTEX 6

namespace cpe
{

/** The skinning weights associated to a vertex
    In this implementation the number of weight per vertex is fixed
     and equals to WEIGHTS_PER_VERTEX.
    Each value is associated to a specific joint_id with a given weight.
    The sum of the weights over all the contribution for each vertex should be one.
*/
class vertex_weight_parameter
{
public:

    vertex_weight_parameter();

    /** Return WEIGHTS_PER_VERTEX */
    int size() const;

    /** Get the k-th skinning weight */
    skinning_weight const& operator[](int index) const;
    /** Get the k-th skinning weight */
    skinning_weight& operator[](int index);

    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::iterator begin();
    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::iterator end();
    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator begin() const;
    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator end() const;
    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator cbegin() const;
    /** STL compatible ranged-loop */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX>::const_iterator cend() const;


private:

    /** Internal storage of the skinning weights data as a static size array */
    std::array<skinning_weight,WEIGHTS_PER_VERTEX> weight_data;
};

/** Return a vertex_weight_parameter such that the sum of the skinning weights equals one. */
vertex_weight_parameter normalized(vertex_weight_parameter const& weight);

}

#endif
