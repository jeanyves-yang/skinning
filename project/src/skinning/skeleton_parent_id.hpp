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

#include <vector>
#include <string>
#include <ostream>


namespace cpe
{

/** A class storing for each entry the index of its parent.
    This class should be associated to a skeleton_geometry storing the geometrical data of the frame.

    For instance skeleton_parent_id[5] = 2 means that the joint 5 is the child of the joint 2.
    By convention, the parent of the joint 0 is usually chosen to be -1.
    Note that the skeleton classes are usually assuming that k > parent_id(k).
*/
class skeleton_parent_id
{
public:
    skeleton_parent_id();

    /** Add a parent id into the structure */
    void push_back(int parent_id);

    /** Get the parent id*/
    int operator[](int index) const;

    /** Number of joint in the structure */
    int size() const;

    /** Load the parent id structure from a .skeleton file
     *  Only store the first number of each line of the file.
    */
    void load(std::string const& filename);

    /** STL compatible ranged-loop */
    std::vector<int>::const_iterator begin() const;
    /** STL compatible ranged-loop */
    std::vector<int>::const_iterator end() const;
    /** STL compatible ranged-loop */
    std::vector<int>::const_iterator cbegin() const;
    /** STL compatible ranged-loop */
    std::vector<int>::const_iterator cend() const;

private:

    /** Internal storage of the parent id */
    std::vector<int> parent_id_data;
};

/** Printing parent_id structure */
std::ostream& operator<<(std::ostream& stream,skeleton_parent_id const& parent_id);

}
