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

#include "skeleton_geometry.hpp"

#include <ostream>

namespace cpe
{
/** Class storing a set of keyframe skeletons. */
class skeleton_animation
{

public:

    skeleton_animation();

    /** The number of keyframes */
    int size() const;

    /** Access to a skeleton at a specific keyframe */
    skeleton_geometry const& operator[](int frame) const;
    /** Access to an interpolated skeleton at time given by (keyframe,alpha value)
     * The alpha value is supposed to be between [0,1]  */
    skeleton_geometry operator()(int frame,float alpha) const;

    /** Load a skeleton animation from a .animation file */
    void load(std::string const& filename,int nbr_joint);

    /** Add a skeleton keyframe into the structure */
    void push_back(skeleton_geometry const& skeleton);

    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::iterator begin();
    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::iterator end();
    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::const_iterator begin() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::const_iterator end() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::const_iterator cbegin() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_geometry>::const_iterator cend() const;

private:
    /** Internal data */
    std::vector<skeleton_geometry> data;
};

/** Print all skeleton keyframe */
std::ostream& operator<<(std::ostream& stream , skeleton_animation const& animation);

}
