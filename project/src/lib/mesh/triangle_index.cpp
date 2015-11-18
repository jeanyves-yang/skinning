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

#include "triangle_index.hpp"

#include "../common/error_handling.hpp"

namespace cpe
{
triangle_index::triangle_index()
    :u0_data(0),u1_data(0),u2_data(0)
{}
triangle_index::triangle_index(int const u0,int const u1,int const u2)
    :u0_data(u0),u1_data(u1),u2_data(u2)
{}

int triangle_index::u0() const {return u0_data;}
int triangle_index::u1() const {return u1_data;}
int triangle_index::u2() const {return u2_data;}
int& triangle_index::u0() {return u0_data;}
int& triangle_index::u1() {return u1_data;}
int& triangle_index::u2() {return u2_data;}

int triangle_index::operator[](int const index) const
{
    ASSERT_CPE(index<3,"Index should be <3");
    ASSERT_CPE(index>=0,"Negative index");
    switch (index)
    {
    case 0:
        return u0_data;
    case 1:
        return u1_data;
    case 2:
        return u2_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

int& triangle_index::operator[](int const index)
{
    ASSERT_CPE(index<3,"Index should be <3");
    ASSERT_CPE(index>=0,"Negative index");
    switch (index)
    {
    case 0:
        return u0_data;
    case 1:
        return u1_data;
    case 2:
        return u2_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

int triangle_index::operator()(int const index) const
{
    return (*this)[index];
}
int& triangle_index::operator()(int const index)
{
    return (*this)[index];
}

const int *triangle_index::pointer() const {return &u0_data;}
constexpr int triangle_index::size() {return 3;}

int* triangle_index::begin() {return &u0_data;}
int* triangle_index::end() {return &u2_data+1;}
const int* triangle_index::begin() const{return &u0_data;}
const int* triangle_index::end() const{return &u2_data+1;}
const int* triangle_index::cbegin() const{return &u0_data;}
const int* triangle_index::cend() const{return &u2_data+1;}

std::ostream& operator<<(std::ostream& stream,triangle_index const& tri)
{
    stream<<tri.u0()<<" "<<tri.u1()<<" "<<tri.u2();
    return stream;
}

}
