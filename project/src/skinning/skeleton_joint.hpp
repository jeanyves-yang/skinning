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

#ifndef SKELETON_JOINT_HPP
#define SKELETON_JOINT_HPP

#include "../lib/3d/vec3.hpp"
#include "../lib/3d/quaternion.hpp"

namespace cpe
{

/** A geometrical joint storing a 3D position and an orientation as a quaternion. */
struct skeleton_joint
{
    skeleton_joint();
    skeleton_joint(vec3 const& position_param,quaternion const& orientation_param);

    /** 3D position of the joint */
    vec3 position;
    /** Orientation of the joint */
    quaternion orientation;
};
}

#endif
