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


#include "mat4x1.hpp"

#include "../common/error_handling.hpp"

#include "mat1x4.hpp"
#include "mat4.hpp"

#include <cmath>


namespace cpe
{

mat4x1::mat4x1()
    :data()
{}

mat4x1::mat4x1(float const x00,float const x10,float const x20,float const x30)
    :data(x00,x10,x20,x30)
{}

float mat4x1::operator[](int const k) const
{
    ASSERT_CPE(k>=0,"Index should be >=0");
    ASSERT_CPE(k<4,"Index should be <4");
    return data[k];
}
float& mat4x1::operator[](int const k)
{
    ASSERT_CPE(k>=0,"Index should be >=0");
    ASSERT_CPE(k<4,"Index should be <4");
    return data[k];
}

float mat4x1::operator()(int const k1,int const k2) const
{
    ASSERT_CPE(k2==0,"Index 1 should be 0");
    ASSERT_CPE(k1>=0,"Index 2 should be >= 0");
    ASSERT_CPE(k1<4,"Index 2 should be < 4");
    return data[k1];
}

float& mat4x1::operator()(int const k1,int const k2)
{
    ASSERT_CPE(k2==0,"Index 1 should be 0");
    ASSERT_CPE(k1>=0,"Index 2 should be >= 0");
    ASSERT_CPE(k1<4,"Index 2 should be < 4");
    return data[k1];
}

mat4x1& operator+=(mat4x1& lhs,mat4x1 const& rhs)
{
    for(int k=0;k<4;++k)
        lhs[k] += rhs[k];
    return lhs;
}

mat4x1& operator-=(mat4x1& lhs,mat4x1 const& rhs)
{
    for(int k=0;k<4;++k)
        lhs[k] -= rhs[k];
    return lhs;
}

mat4x1& operator*=(mat4x1& m,float const s)
{
    for(int k=0;k<4;++k)
        m[k] *= s;
    return m;
}

mat4x1& operator/=(mat4x1& m,float const s)
{
    for(int k=0;k<4;++k)
        m[k] /= s;
    return m;

}

mat4x1 operator+(mat4x1 const& lhs,mat4x1 const& rhs)
{
    mat4x1 temp=lhs;
    temp += rhs;
    return temp;
}

mat4x1 operator-(mat4x1 const& lhs,mat4x1 const& rhs)
{
    mat4x1 temp=lhs;
    temp -= rhs;
    return temp;
}

mat4x1 operator*(mat4x1 const& m,float const s)
{
    mat4x1 temp=m;
    temp *= s;
    return temp;
}
mat4x1 operator*(float s,mat4x1 const& m)
{
    return m*s;
}
mat4x1 operator/(mat4x1 const& m,float const s)
{
    mat4x1 temp=m;
    temp /= s;
    return temp;
}

mat4x1 operator*(mat4 const& lhs,mat4x1 const& rhs)
{
    return mat4x1(lhs(0,0)*rhs[0]+lhs(0,1)*rhs[1]+lhs(0,2)*rhs[2]+lhs(0,3)*rhs[3],
            lhs(1,0)*rhs[0]+lhs(1,1)*rhs[1]+lhs(1,2)*rhs[2]+lhs(1,3)*rhs[3],
            lhs(2,0)*rhs[0]+lhs(2,1)*rhs[1]+lhs(2,2)*rhs[2]+lhs(2,3)*rhs[3],
            lhs(3,0)*rhs[0]+lhs(3,1)*rhs[1]+lhs(3,2)*rhs[2]+lhs(3,3)*rhs[3]);
}

float operator*(mat4x1 const& lhs,mat4x1 const& rhs)
{
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+lhs[3]*rhs[3];
}

mat4x1 operator-(mat4x1 const& m)
{
    return mat4x1(-m[0],-m[1],-m[2],-m[3]);
}


std::ostream& operator<<(std::ostream& stream,mat4x1 const& m)
{
    stream<<m[0]<<" "<<m[1]<<" "<<m[2]<<" "<<m[3]<<"\n";
    return stream;
}

float const* mat4x1::pointer() const
{
    return data.pointer();
}

mat1x4 transposed(mat4x1 const& m)
{
    return mat1x4(m[0],m[1],m[2],m[3]);
}


}
