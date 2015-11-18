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


#include "skeleton_animation.hpp"

#include "../lib/common/error_handling.hpp"

#include <sstream>
#include <fstream>

namespace cpe
{

skeleton_animation::skeleton_animation()
    :data()
{}

int skeleton_animation::size() const
{
    return data.size();
}
skeleton_geometry const& skeleton_animation::operator[](int const frame) const
{
    ASSERT_CPE(frame>=0,"Frame ("+std::to_string(frame)+") must be positive");
    ASSERT_CPE(frame<int(data.size()) , "Frame ("+std::to_string(frame)+") must be less than the current data size ("+std::to_string(data.size())+")");

    return data[frame];
}

void skeleton_animation::load(std::string const& filename,int const nbr_joint)
{
    std::ifstream fid(filename.c_str());
    if(!fid.good())
      throw exception_cpe("Cannot open file "+filename,MACRO_EXCEPTION_PARAMETER);

    std::string buffer;

    int counter = 0;

    skeleton_geometry temp_geometry;

    //read the whole file
    while(fid.good()==true)
    {
      //read line
      std::getline(fid,buffer);

      if( buffer.size()>0 && buffer[0] != '#')
      {

          skeleton_joint joint;

          std::stringstream tokens(buffer);

          tokens >> joint.position.x();
          tokens >> joint.position.y();
          tokens >> joint.position.z();

          tokens >> joint.orientation.x();
          tokens >> joint.orientation.y();
          tokens >> joint.orientation.z();
          tokens >> joint.orientation.w();

          joint.orientation = normalized(joint.orientation);

          temp_geometry.push_back(joint);
          ++counter;

          if(counter%nbr_joint==0)
          {
              data.push_back(temp_geometry);
              temp_geometry.clear();
          }
      }
    }
}

std::vector<skeleton_geometry>::iterator skeleton_animation::begin() {return data.begin();}
std::vector<skeleton_geometry>::iterator skeleton_animation::end() {return data.end();}
std::vector<skeleton_geometry>::const_iterator skeleton_animation::begin() const {return data.begin();}
std::vector<skeleton_geometry>::const_iterator skeleton_animation::end() const {return data.end();}
std::vector<skeleton_geometry>::const_iterator skeleton_animation::cbegin() const {return data.cbegin();}
std::vector<skeleton_geometry>::const_iterator skeleton_animation::cend() const {return data.cend();}

std::ostream& operator<<(std::ostream& stream , skeleton_animation const& animation)
{
    int counter=0;
    for(skeleton_geometry const& sk : animation)
    {
        stream<<"Frame "<<counter++<<std::endl;
        stream<<"***************************"<<std::endl;
        stream<<sk<<std::endl;
    }
    return stream;
}

void skeleton_animation::push_back(skeleton_geometry const& skeleton)
{
    data.push_back(skeleton);

}

skeleton_geometry skeleton_animation::operator()(int const frame,float const alpha) const
{
    int const N_frame = size();
    ASSERT_CPE(frame<N_frame,"Incorrect frame number");

    skeleton_geometry const& sk0 = (*this)[frame];

    int const frame_next = (frame+1)%N_frame;

    skeleton_geometry const& sk1 = (*this)[frame_next];

    return interpolated(sk0,sk1,alpha);
}

}
