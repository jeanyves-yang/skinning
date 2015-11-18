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

#ifndef INTERSECTION_HELPER_HPP
#define INTERSECTION_HELPER_HPP

#include "../3d/vec3.hpp"
#include <vector>

namespace cpe
{


namespace intersection
{
/** \brief Compute the intersection between a sphere and a ray
    \return true if there is an intersection, false otherwise.
    The t-value (parameter along the line) at the intersection point
    is filled in the parameters intersection_0 and intersection_1.
    Ray_direction is supposed to be a vector of norm 1.
*/
bool sphere_ray(vec3 const& sphere_center,
                float       sphere_radius,
                vec3 const& ray_center,
                vec3 const& ray_direction,
                float&      intersection_0,
                float&      intersection_1);
}

}

#endif
