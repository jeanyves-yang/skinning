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

#include "skeleton_joint.hpp"

#include <vector>
#include <ostream>

namespace cpe
{
class skeleton_parent_id;

/** A class storing for each entry the geometrical frame of a joint of a skeleton.
    This class do not store the hierarchy of the structure (skeleton_parent_id), only the geometry of the k-th joint.
*/
class skeleton_geometry
{
public:

    skeleton_geometry();

    /** The number of joint of the skeleton */
    int size() const;

    /** Empty the structure */
    void clear();

    /** Add a geometrical joint in the next entry of the structure */
    void push_back(skeleton_joint const& joint);

    /** Get the k-th joint geometry */
    skeleton_joint const& operator[](int index) const;
    /** Get the k-th joint geometry */
    skeleton_joint& operator[](int index);

    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::iterator begin();
    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::iterator end();
    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::const_iterator begin() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::const_iterator end() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::const_iterator cbegin() const;
    /** STL compatible ranged-loop */
    std::vector<skeleton_joint>::const_iterator cend() const;

    /** Load geometrical structure from a .skeleton file */
    void load(std::string const& filename);
    /** Save a .skeleton file
     * \note requires the parent_id for the hierarchy information in the file
    */
    void save(std::string const& filename,skeleton_parent_id const& parent_id);


private:

    /** Internal data of the joint geometry*/
    std::vector<skeleton_joint> data;
};

/** Print all the data */
std::ostream& operator<<(std::ostream& stream , skeleton_geometry const& skeleton);

/** Convert joint frame expressed with respect to their parent into a global coordinate frame. */
skeleton_geometry local_to_global(skeleton_geometry const& skeleton,skeleton_parent_id const& parent_id);
/** Take the inverse of the frame (used to compute the inversed bind pose frames). */
skeleton_geometry inversed(skeleton_geometry const& skeleton);
/** Multiply each frames of the skeleton each other.
 *  The two skeleton must have the same number of joints.  */
skeleton_geometry multiply(skeleton_geometry const& skeleton_1,skeleton_geometry const& skeleton_2);

/** Extract a vector storing all the bones positions using pair of vertices.
 * For instance T = extract_bones(); bone_0 = [T[0],T[1]]; bone_1 = [T[2];T[3]]; etc.
 * \param skeleton: A geometrical skeleton with joint expressed in the global coordinate system.
 * \param parent_id: The structure storing the id of the parent of each joint.
*/
std::vector<vec3> extract_bones(skeleton_geometry const& skeleton,skeleton_parent_id const& parent_id);

/** Interpolate each joint frames of the input skeletons between the two poses given an alpha interpolated value.
 * alpha is supposed to be between [0,1]. */
skeleton_geometry interpolated(skeleton_geometry const& skeleton_1,skeleton_geometry const& skeleton_2,float alpha);

}
