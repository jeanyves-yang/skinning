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

#ifndef SELECTED_INDEX_HPP
#define SELECTED_INDEX_HPP

#include "../3d/vec3.hpp"
#include <list>


namespace cpe
{
/** \brief Helper class to store 2D picked indices */
class selected_index
{
    public:

        /** Defaut constructor */
        selected_index();

        /** Add an index */
        void add(int ku,int kv);
        /** Check if an index is already stored */
        bool exist(int ku,int kv) const;
        /** Remove the index if it is stored. Do nothing otherwise. */
        void remove(int ku,int kv);

        /** Remove all indices. */
        void clear();

        /** Returns the number of stored index  */
        int size() const;

        /** STL compliant function */
        std::list<std::pair<int,int> >::const_iterator begin() const;
        /** STL compliant function */
        std::list<std::pair<int,int> >::const_iterator cbegin() const;
        /** STL compliant function */
        std::list<std::pair<int,int> >::iterator begin();

        /** STL compliant function */
        std::list<std::pair<int,int> >::const_iterator end() const;
        /** STL compliant function */
        std::list<std::pair<int,int> >::const_iterator cend() const;
        /** STL compliant function */
        std::list<std::pair<int,int> >::iterator end();

    private:

        /** The internal storage data as a list of (ku,kv) */
        std::list<std::pair<int,int> > data;
};
}

#endif
