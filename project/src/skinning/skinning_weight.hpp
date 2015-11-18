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

#ifndef SKINNING_WEIGHT_HPP
#define SKINNING_WEIGHT_HPP

namespace cpe
{

/** Container for a weight associated to a given joint of a skeleton */
struct skinning_weight
{
    skinning_weight();

    /** The id of the joint of the skeleton */
    int joint_id;
    /** The associated skinning weight */
    float weight;
};



}

#endif
