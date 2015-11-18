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

#include "selected_index.hpp"

namespace cpe
{

selected_index::selected_index()
    :data()
{}

void selected_index::add(int const ku,int const kv)
{
    if(exist(ku,kv)==false)
        data.push_back({ku,kv});
}

bool selected_index::exist(int const ku,int const kv) const
{
    for(auto const& p : data)
        if(p.first==ku && p.second==kv)
            return true;
    return false;
}

void selected_index::remove(int const ku,int const kv)
{
    data.remove({ku,kv});
}

void selected_index::clear()
{
    data.clear();
}

int selected_index::size() const {return data.size();}
std::list<std::pair<int,int> >::const_iterator selected_index::begin() const {return data.begin();}
std::list<std::pair<int,int> >::const_iterator selected_index::cbegin() const {return data.cbegin();}
std::list<std::pair<int,int> >::iterator selected_index::begin() {return data.begin();}

std::list<std::pair<int,int> >::const_iterator selected_index::end() const {return data.end();}
std::list<std::pair<int,int> >::const_iterator selected_index::cend() const {return data.cend();}
std::list<std::pair<int,int> >::iterator selected_index::end() {return data.end();}

}
