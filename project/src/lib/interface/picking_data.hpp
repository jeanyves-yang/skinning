/*
**    TP CPE Lyon
**    Copyright (C) 2014 Damien Rohmer
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

#ifndef PICKING_DATA_HPP
#define PICKING_DATA_HPP

#include "../3d/vec3.hpp"
#include <map>

namespace cpe
{
/** \brief Helper class to store picking parameters */
class picking_data
{
    public:

        /** \brief Defaut constructor */
        picking_data();

        /** \brief get the is_picked value */
        bool get_is_picked() const;
        /** \brief set the is_picked value */
        void set_is_picked(bool value);

        /** \brief get the picked indices */
        std::map<unsigned int,std::pair<unsigned int,unsigned int> > const& get_picked_index() const;
        /** \brief set the picked indices */
        void set_picked_index(const std::map<unsigned int,std::pair<unsigned int,unsigned int> >& value);

        /** \brief get the is_up_to_date value */
        bool get_is_up_to_date() const;
        /** \brief set the is_up_to_date value */
        void set_is_up_to_date(bool value);



    private:

        /** \brief Internal storage to know if the picking mode is active */
        bool is_picked;
        /** \brief Internal storage to know if the surface is up to date and at high resolution */
        bool is_up_to_date;
        /** \brief Internal storage of the picked indices (unique ID,<u_index,v_index>)
            The unique ID is given by u_index+N_u*v_index;
        */
        std::map<unsigned int,std::pair<unsigned int,unsigned int> > picked_index;

};
}

#endif
