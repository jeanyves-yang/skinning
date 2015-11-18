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


#include "mat3.hpp"
#include "vec3.hpp"

#include "../common/error_handling.hpp"

#include <cmath>
#include <iostream>
#include <sstream>


namespace cpe
{

mat3::mat3()
{
    data[0]=1.0f; data[3]=0.0f; data[6]=0.0f;
    data[1]=0.0f; data[4]=1.0f; data[7]=0.0f;
    data[2]=0.0f; data[5]=0.0f; data[8]=1.0f;
}

mat3::mat3(float const x00,float const x01,float const x02,
           float const x10,float const x11,float const x12,
           float const x20,float const x21,float const x22)
{
    data[0]=x00;data[3]=x01;data[6]=x02;
    data[1]=x10;data[4]=x11;data[7]=x12;
    data[2]=x20;data[5]=x21;data[8]=x22;
}


void mat3::set_identity()
{
    data[0]=1.0f; data[3]=0.0f; data[6]=0.0f;
    data[1]=0.0f; data[4]=1.0f; data[7]=0.0f;
    data[2]=0.0f; data[5]=0.0f; data[8]=1.0f;
}

void mat3::set_zeros()
{
    for(int k=0;k<9;++k)
        data[k]=0.0f;
}

void mat3::set_rotation(const vec3& axis,float const angle)
{
    vec3 const n=normalized(axis);

    float const cos_t=std::cos(angle);
    float const sin_t=std::sin(angle);

    data[0]=cos_t+n[0]*n[0]*(1.0f-cos_t);       data[3]=n[0]*n[1]*(1.0f-cos_t)-n[2]*sin_t;    data[6]=n[1]*sin_t+n[0]*n[2]*(1.0f-cos_t);
    data[1]=n[2]*sin_t+n[0]*n[1]*(1.0f-cos_t);  data[4]=cos_t+n[1]*n[1]*(1.0f-cos_t);         data[7]=-n[0]*sin_t+n[1]*n[2]*(1.0f-cos_t);
    data[2]=-n[1]*sin_t+n[0]*n[2]*(1.0f-cos_t); data[5]=n[0]*sin_t+n[1]*n[2]*(1.0f-cos_t);    data[8]=cos_t+n[2]*n[2]*(1.0f-cos_t);

}

void mat3::set_scaling(float const s)
{
    data[0]=s;    data[3]=0.0f; data[6]=0.0f;
    data[1]=0.0f; data[4]=s;    data[7]=0.0f;
    data[2]=0.0f; data[5]=0.0f; data[8]=s;
}

void mat3::set_scaling(float const s_x,float const s_y,float const s_z)
{
    data[0]=s_x;  data[3]=0.0f; data[6]=0.0f;
    data[1]=0.0f; data[4]=s_y;  data[7]=0.0f;
    data[2]=0.0f; data[5]=0.0f; data[8]=s_z;
}


float mat3::operator[](int const k) const
{
    ASSERT_CPE(k>=0,"Index should be positive");
    ASSERT_CPE(k<9,"Index should be < 9");

    return data[k];
}

float& mat3::operator[](int const k)
{
    ASSERT_CPE(k>=0,"Index should be positive");
    ASSERT_CPE(k<9,"Index should be < 9");

    return data[k];
}


float mat3::operator()(int const k1,int const k2) const
{
    ASSERT_CPE(k1>=0,"Index should be positive");
    ASSERT_CPE(k1<3,"Index should be < 3");
    ASSERT_CPE(k2>=0,"Index should be positive");
    ASSERT_CPE(k2<3,"Index should be < 3");
    return data[3*k2+k1];
}
float& mat3::operator()(int const k1,int const k2)
{
    ASSERT_CPE(k1>=0,"Index should be positive");
    ASSERT_CPE(k1<3,"Index should be < 3");
    ASSERT_CPE(k2>=0,"Index should be positive");
    ASSERT_CPE(k2<3,"Index should be < 3");
    return data[3*k2+k1];
}


mat3& operator+=(mat3& lhs,mat3 const& rhs)
{
    for(int k=0;k<9;++k)
        lhs[k]+=rhs[k];
    return lhs;
}

mat3& operator-=(mat3& lhs,mat3 const& rhs)
{
    for(int k=0;k<9;++k)
        lhs[k]-=rhs[k];
    return lhs;
}

mat3& operator*=(mat3& lhs,mat3 const& rhs)
{
    mat3 temp=lhs*rhs;
    lhs=temp;
    return lhs;
}

mat3& operator*=(mat3& m,float const s)
{
    for(int k=0;k<9;++k)
        m[k]*=s;
    return m;
}

mat3& operator/=(mat3& m,float const s)
{
    for(int k=0;k<9;++k)
        m[k]/=s;
    return m;
}

mat3 operator+(mat3 const& lhs,mat3 const& rhs)
{
    mat3 temp=lhs;
    temp += rhs;
    return temp;
}

mat3 operator-(mat3 const& lhs,mat3 const& rhs)
{
    mat3 temp=lhs;
    temp -= rhs;
    return temp;
}

mat3 operator*(mat3 const& lhs,mat3 const& rhs)
{
    mat3 res(0.0f,0.0f,0.0f,
             0.0f,0.0f,0.0f,
             0.0f,0.0f,0.0f);
    for(int kx=0;kx<3;++kx)
        for(int ky=0;ky<3;++ky)
            for(int k=0;k<3;++k)
                res(kx,ky) += lhs(kx,k)*rhs(k,ky);
    return res;
}

mat3 operator*(mat3 const& m,float const s)
{
    mat3 temp=m;
    temp*=s;
    return temp;
}

mat3 operator*(float const s,mat3 const& m)
{
    return m*s;
}

mat3 operator/(mat3 const& m,float const s)
{
    mat3 temp=m;
    temp/=s;
    return temp;
}

vec3 operator*(mat3 const& lhs,vec3 const& rhs)
{
    return vec3(lhs(0,0)*rhs[0]+lhs(0,1)*rhs[1]+lhs(0,2)*rhs[2],
                lhs(1,0)*rhs[0]+lhs(1,1)*rhs[1]+lhs(1,2)*rhs[2],
                lhs(2,0)*rhs[0]+lhs(2,1)*rhs[1]+lhs(2,2)*rhs[2]);
}

mat3 operator-(mat3 const& m)
{
    return mat3(-m(0,0),-m(0,1),-m(0,2),
                -m(1,0),-m(1,1),-m(1,2),
                -m(2,0),-m(2,1),-m(2,2));
}






std::ostream& operator<<(std::ostream& stream,const mat3& m)
{
    stream<<m[0]<<","<<m[3]<<","<<m[6]<<"\n"<<
            m[1]<<","<<m[4]<<","<<m[7]<<"\n"<<
            m[2]<<","<<m[5]<<","<<m[8]<<"\n";
    return stream;
}



float const* mat3::pointer() const
{
    return &data[0];
}


mat3 transposed(mat3 const& m)
{
    return mat3(m[0],m[1],m[2],
            m[3],m[4],m[5],
            m[6],m[7],m[8]);
}

float determinant(mat3 const& m)
{
    return m[0]*(m[4]*m[8]-m[5]*m[7])-m[1]*(m[3]*m[8]-m[5]*m[6])+m[2]*(m[3]*m[7]-m[4]*m[6]);
}

mat3 inverted(mat3 const& m)
{
    float const det = determinant(m);
    ASSERT_CPE(std::abs(det)>1e-5 , "Non invertible matrix");

    float const x00 =   m[4]*m[8]-m[7]*m[5];
    float const x10 = -(m[1]*m[8]-m[7]*m[2]);
    float const x20 =   m[1]*m[5]-m[4]*m[2];

    float const x01 = -(m[3]*m[8]-m[6]*m[5]);
    float const x11 =   m[0]*m[8]-m[6]*m[2];
    float const x21 = -(m[0]*m[5]-m[3]*m[2]);

    float const x02 =   m[3]*m[7]-m[6]*m[4];
    float const x12 = -(m[0]*m[7]-m[6]*m[1]);
    float const x22 =   m[0]*m[4]-m[3]*m[1];

    return mat3(x00,x01,x02,
                x10,x11,x12,
                x20,x21,x22)/det;
}



}
