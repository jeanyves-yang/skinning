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

#include "mat2.hpp"
#include "vec2.hpp"
#include "../common/error_handling.hpp"
#include <cmath>


namespace cpe
{

mat2::mat2()
{
    data[0]=1.0f; data[2]=0.0f;
    data[1]=0.0f; data[3]=1.0f;
}

mat2::mat2(float const x00,float const x01,
           float const x10,float const x11)
{
    data[0]=x00;data[2]=x01;
    data[1]=x10;data[3]=x11;
}

void mat2::set_identity()
{
    data[0]=1.0f; data[2]=0.0f;
    data[1]=0.0f; data[3]=1.0f;
}

void mat2::set_zeros()
{
    data[0]=0.0f; data[2]=0.0f;
    data[1]=0.0f; data[3]=0.0f;
}

void mat2::set_rotation(float const angle)
{
    float const cos_angle=std::cos(angle);
    float const sin_angle=std::sin(angle);

    data[0]=cos_angle; data[2]=-sin_angle;
    data[1]=sin_angle; data[3]=cos_angle;
}

void mat2::set_scaling(float const s)
{
    data[0]=s;   data[2]=0.0f;
    data[1]=0.0f;data[3]=s;
}

void mat2::set_scaling(float const s_x,float const s_y)
{
    data[0]=s_x; data[2]=0.0f;
    data[1]=0.0f;data[3]=s_y;
}


float mat2::operator()(int const k1,int const k2) const
{
    ASSERT_CPE(k1>=0,"index should be positive");
    ASSERT_CPE(k1<2,"index should be < 2");
    ASSERT_CPE(k2>=0,"index should be positive");
    ASSERT_CPE(k2<2,"index should be < 2");

    return data[2*k2+k1];
}
float& mat2::operator()(int const k1,int const k2)
{
    ASSERT_CPE(k1>=0,"index should be positive");
    ASSERT_CPE(k1<2,"index should be < 2");
    ASSERT_CPE(k2>=0,"index should be positive");
    ASSERT_CPE(k2<2,"index should be < 2");

    return data[2*k2+k1];
}

float mat2::operator[](int const k) const
{
    ASSERT_CPE(k>=0,"index should be positive");
    ASSERT_CPE(k<4,"index should be < 4");

    return data[k];
}
float& mat2::operator[](int const k)
{
    ASSERT_CPE(k>=0,"index should be positive");
    ASSERT_CPE(k<4,"index should be < 4");

    return data[k];
}


std::ostream& operator<<(std::ostream& stream,mat2 const& m)
{
    stream<<m(0,0)<<","<<m(0,1)<<std::endl;
    stream<<m(1,0)<<","<<m(1,1)<<std::endl;
    return stream;
}


float const* mat2::pointer() const
{
    return &data[0];
}


mat2& operator+=(mat2& lhs,mat2 const& rhs)
{
    for(int k=0;k<4;++k)
        lhs[k]+=rhs[k];
    return lhs;
}

mat2& operator-=(mat2& lhs,mat2 const& rhs)
{
    for(int k=0;k<4;++k)
        lhs[k]-=rhs[k];
    return lhs;
}

mat2& operator*=(mat2& lhs,mat2 const& rhs)
{
    mat2 temp=lhs*rhs;
    lhs=temp;
    return lhs;
}
mat2& operator*=(mat2& lhs,float s)
{
    for(int k=0;k<4;++k)
        lhs[k]*=s;
    return lhs;
}

mat2& operator/=(mat2& lhs,float s)
{
    for(int k=0;k<4;++k)
        lhs[k]/=s;
    return lhs;
}

mat2 operator+(mat2 const& lhs,mat2 const& rhs)
{
    mat2 temp=lhs;
    temp+=rhs;
    return temp;
}

mat2 operator-(mat2 const& lhs,mat2 const& rhs)
{
    mat2 temp=lhs;
    temp-=rhs;
    return temp;
}

mat2 operator*(mat2 const& m,float s)
{
    mat2 temp=m;
    temp*=s;
    return temp;
}

mat2 operator*(float s,mat2 const& m)
{
    return m*s;
}

mat2 operator/(mat2 const& m,float s)
{
    mat2 temp=m;
    temp/=s;
    return temp;
}

mat2 operator-(mat2 const& m)
{
    return mat2(-m(0,0) , -m(0,1),
                -m(1,0) , -m(1,1));
}

mat2 operator*(mat2 const& lhs,mat2 const& rhs)
{
    mat2 res(0.0f,0.0f,
             0.0f,0.0f);

    for(int k1=0;k1<2;++k1)
        for(int k2=0;k2<2;++k2)
            for(int k=0;k<2;++k)
                res(k1,k2) += lhs(k1,k)*rhs(k,k2);

    return res;
}

vec2 operator*(mat2 const& lhs,vec2 const& rhs)
{
    return vec2(lhs(0,0)*rhs(0)+lhs(0,1)*rhs(1),
                lhs(1,0)*rhs(0)+lhs(1,1)*rhs(1));
}

mat2 transposed(mat2 const& m)
{
    return mat2(m(0,0),m(1,0),
                m(0,1),m(1,1));
}

float determinant(mat2 const& m)
{
    return m(0,0)*m(1,1)-m(0,1)*m(1,0);
}

mat2 inverted(mat2 const& m)
{
    float const d = determinant(m);
    ASSERT_CPE(std::abs(d) > 1e-5,"Non invertible matrix");

    return mat2(m(1,1),-m(1,0),
                -m(0,1),m(0,0));
}

}
