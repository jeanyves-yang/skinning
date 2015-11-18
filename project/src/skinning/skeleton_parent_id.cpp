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


#include "skeleton_parent_id.hpp"

#include "../lib/common/error_handling.hpp"

#include <sstream>
#include <fstream>

namespace cpe
{

skeleton_parent_id::skeleton_parent_id()
    :parent_id_data()
{}

void skeleton_parent_id::push_back(int const parent_id)
{
    parent_id_data.push_back(parent_id);
}

int skeleton_parent_id::size() const
{
    return parent_id_data.size();
}

int skeleton_parent_id::operator[](int const index) const
{
    ASSERT_CPE(index>=0,"Index ("+std::to_string(index)+") must be positive");
    ASSERT_CPE(index<int(parent_id_data.size()) , "Index ("+std::to_string(index)+") must be less than the current data size ("+std::to_string(parent_id_data.size())+")");

    return parent_id_data[index];
}

void skeleton_parent_id::load(std::string const& filename)
{
    parent_id_data.clear();

    std::ifstream fid(filename.c_str());
    if(!fid.good())
      throw exception_cpe("Cannot open file "+filename,EXCEPTION_PARAMETERS_CPE);

    std::string buffer;

    //read the whole file
    while(fid.good()==true)
    {
      //read line
      std::getline(fid,buffer);

      if(buffer.size()>0 && buffer[0] != '#')
      {
          std::string trash;
          std::stringstream tokens(buffer);

          int parent_id = -1;
          tokens >> parent_id;

          for(int k=0 ; k<7 ; ++k)
              tokens >> trash;

          parent_id_data.push_back(parent_id);
      }
    }
}

std::vector<int>::const_iterator skeleton_parent_id::begin() const {return parent_id_data.begin();}
std::vector<int>::const_iterator skeleton_parent_id::end() const {return parent_id_data.end();}
std::vector<int>::const_iterator skeleton_parent_id::cbegin() const {return parent_id_data.cbegin();}
std::vector<int>::const_iterator skeleton_parent_id::cend() const {return parent_id_data.cend();}

std::ostream& operator<<(std::ostream& stream,skeleton_parent_id const& parent_id)
{
    for(int id : parent_id)
        stream<<id<<" ";
    return stream;
}



}
