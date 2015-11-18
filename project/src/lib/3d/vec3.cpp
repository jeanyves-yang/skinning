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



#include "vec3.hpp"
#include "../common/error_handling.hpp"

#include <cmath>

namespace cpe
{

vec3::vec3()
    :x_data(0.0f),y_data(0.0f),z_data(0.0f)
{}

vec3::vec3(float const x_param,float const y_param,float const z_param)
    :x_data(x_param),y_data(y_param),z_data(z_param)
{}

float vec3::x() const
{
    return x_data;
}

float& vec3::x()
{
    return x_data;
}

float vec3::y() const
{
    return y_data;
}

float& vec3::y()
{
    return y_data;
}

float vec3::z() const
{
    return z_data;
}

float& vec3::z()
{
    return z_data;
}

float vec3::operator[](int const k) const
{
    ASSERT_CPE(k<3,"Index should be <3");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    case 2:
        return z_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float& vec3::operator[](int const k)
{
    ASSERT_CPE(k<3,"Index should be <3");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    case 2:
        return z_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float vec3::operator()(int const k) const
{
    return (*this)[k];
}
float& vec3::operator()(int const k)
{
    return (*this)[k];
}

const float *vec3::pointer() const
{return &x_data;}



vec3& operator+=(vec3& lhs,vec3 const& rhs)
{
    lhs.x()+=rhs.x();
    lhs.y()+=rhs.y();
    lhs.z()+=rhs.z();
    return lhs;
}

vec3& operator-=(vec3& lhs,vec3 const& rhs)
{
    lhs.x()-=rhs.x();
    lhs.y()-=rhs.y();
    lhs.z()-=rhs.z();
    return lhs;
}

vec3& operator*=(vec3& v,float const s)
{
    v.x()*=s;
    v.y()*=s;
    v.z()*=s;
    return v;
}

vec3& operator/=(vec3& v,float const s)
{
    v.x()/=s;
    v.y()/=s;
    v.z()/=s;
    return v;
}

vec3 operator+(vec3 const& lhs,vec3 const& rhs)
{
    vec3 temp=lhs;
    temp+=rhs;
    return temp;
}

vec3 operator-(vec3 const& lhs,vec3 const& rhs)
{
    vec3 temp=lhs;
    temp-=rhs;
    return temp;
}

vec3 operator*(vec3 const& v,float const s)
{
    vec3 temp=v;
    temp*=s;
    return temp;
}

vec3 operator*(float const s,vec3 const& v)
{
    return v*s;
}

vec3 operator/(vec3 const& v,float const s)
{
    vec3 temp=v;
    temp/=s;
    return temp;
}

vec3 operator-(vec3 const& v)
{
    return vec3(-v.x(),-v.y(),-v.z());
}




float dot(vec3 const& lhs,vec3 const& rhs)
{
    return lhs.x()*rhs.x()+lhs.y()*rhs.y()+lhs.z()*rhs.z();
}

float norm(vec3 const& v)
{
    return std::sqrt(v.x()*v.x()+v.y()*v.y()+v.z()*v.z());
}

vec3 normalized(vec3 const& v)
{
    float const n=norm(v);
    if(n>1e-6)
        return v/n;
    else
        return vec3(1.0f,0.0f,0.0f); //default case
}

vec3 cross(vec3 const& lhs,vec3 const& rhs)
{
    return vec3(lhs.y()*rhs.z()-lhs.z()*rhs.y(),
                lhs.z()*rhs.x()-lhs.x()*rhs.z(),
                lhs.x()*rhs.y()-lhs.y()*rhs.x());
}

vec3 reflected(vec3 const& vec,vec3 const& axis)
{
    ASSERT_CPE(std::abs(norm(axis)-1.0f)<1e-5f,"Axis must be of norm 1");

    float const proj = dot(vec,axis);

    return 2*proj*axis-vec;
}

std::ostream& operator<<(std::ostream& stream,const vec3& p)
{
    stream<<p.x()<<" "<<p.y()<<" "<<p.z();
    return stream;
}

constexpr int vec3::size(){return 3;}
float* vec3::begin() {return &x_data;}
float* vec3::end() {return &z_data+1;}
const float* vec3::begin() const {return &x_data;}
const float* vec3::end() const {return &z_data+1;}
const float* vec3::cbegin() const {return &x_data;}
const float* vec3::cend() const {return &z_data+1;}

}
