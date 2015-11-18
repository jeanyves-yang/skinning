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


#include "intersection.hpp"
#include <cmath>
#include <vector>

namespace cpe
{
namespace intersection
{

bool sphere_ray(vec3 const& sphere_center,
                float       sphere_radius,
                vec3 const& ray_center,
                vec3 const& ray_direction,
                float&      intersection_0,
                float&      intersection_1)
{
    vec3 const x0=ray_center-sphere_center;
    float const dx=dot(ray_direction,x0);

    float const delta=dx*dx-dot(x0,x0)+sphere_radius*sphere_radius;

    if(delta<0) //no intersection
        return false;
    else if(delta<1e-6)
    {
        intersection_0=-dx;
        intersection_1=-dx;

        return true;
    }
    else
    {
        float const s=std::sqrt(delta);

        intersection_0=-dx+s;
        intersection_1= dx+s;

        return true;
    }
}

}
}
