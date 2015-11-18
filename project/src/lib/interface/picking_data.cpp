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

#include "picking_data.hpp"

namespace cpe
{
picking_data::picking_data()
    :is_picked(false),is_up_to_date(false)
{}

bool picking_data::get_is_picked() const {return is_picked;}
void picking_data::set_is_picked(bool const value) {is_picked=value;}

const std::map<unsigned int,std::pair<unsigned int,unsigned int> >& picking_data::get_picked_index() const {return picked_index;}
void picking_data::set_picked_index(std::map<unsigned int,std::pair<unsigned int,unsigned int> > const& value) {picked_index=value;}

bool picking_data::get_is_up_to_date() const {return is_up_to_date;}
void picking_data::set_is_up_to_date(bool const value) {is_up_to_date=value;}

}
