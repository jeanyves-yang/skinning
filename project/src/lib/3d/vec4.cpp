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



#include "vec4.hpp"
#include "../common/error_handling.hpp"

#include <cmath>

namespace cpe
{

vec4::vec4()
    :x_data(0.0f),y_data(0.0f),z_data(0.0f),w_data(0.0f)
{}

vec4::vec4(float const x_param,float const y_param,float const z_param,float const w_param)
    :x_data(x_param),y_data(y_param),z_data(z_param),w_data(w_param)
{}

float vec4::x() const
{
    return x_data;
}

float& vec4::x()
{
    return x_data;
}

float vec4::y() const
{
    return y_data;
}

float& vec4::y()
{
    return y_data;
}

float vec4::z() const
{
    return z_data;
}

float& vec4::z()
{
    return z_data;
}
float vec4::w() const
{
    return w_data;
}

float& vec4::w()
{
    return w_data;
}

float vec4::operator[](int const k) const
{
    ASSERT_CPE(k<4,"Index should be <4");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    case 2:
        return z_data;
    case 3:
        return w_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float& vec4::operator[](int const k)
{
    ASSERT_CPE(k<4,"Index should be <4");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    case 2:
        return z_data;
    case 3:
        return w_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float vec4::operator()(int const k) const
{
    return (*this)[k];
}

float& vec4::operator()(int const k)
{
    return (*this)[k];
}





vec4& operator+=(vec4& lhs,vec4 const& rhs)
{
    lhs.x()+=rhs.x();
    lhs.y()+=rhs.y();
    lhs.z()+=rhs.z();
    lhs.w()+=rhs.w();
    return lhs;
}

vec4& operator-=(vec4& lhs,vec4 const& rhs)
{
    lhs.x()-=rhs.x();
    lhs.y()-=rhs.y();
    lhs.z()-=rhs.z();
    lhs.w()-=rhs.w();
    return lhs;
}

vec4& operator*=(vec4& v,float const s)
{
    v.x()*=s;
    v.y()*=s;
    v.z()*=s;
    v.w()*=s;
    return v;
}

vec4& operator/=(vec4& v,float const s)
{
    v.x()/=s;
    v.y()/=s;
    v.z()/=s;
    v.w()/=s;
    return v;
}

vec4 operator+(vec4 const& lhs,vec4 const& rhs)
{
    vec4 temp=lhs;
    temp+=rhs;
    return temp;
}

vec4 operator-(vec4 const& lhs,vec4 const& rhs)
{
    vec4 temp=lhs;
    temp-=rhs;
    return temp;
}
vec4 operator*(vec4 const& v,float const s)
{
    vec4 temp=v;
    temp*=s;
    return temp;
}

vec4 operator*(float const s,vec4 const& v)
{
    return v*s;
}

vec4 operator/(vec4 const& v,float const s)
{
    vec4 temp=v;
    temp/=s;
    return temp;
}

vec4 operator-(vec4 const& v)
{
    return vec4(-v.x(),-v.y(),-v.z(),-v.w());
}


std::ostream& operator<<(std::ostream& stream,vec4 const& v)
{
    stream<<v.x()<<" "<<v.y()<<" "<<v.z()<<" "<<v.w();
    return stream;
}


const float *vec4::pointer() const
{return &x_data;}


float dot(vec4 const& lhs,vec4 const& rhs)
{
    return lhs.x()*rhs.x()+lhs.y()*rhs.y()+lhs.z()*rhs.z()+lhs.w()*rhs.w();
}

float norm(vec4 const& v)
{
    return std::sqrt(v.x()*v.x()+v.y()*v.y()+v.z()*v.z());
}

vec4 normalized(vec4 const& v)
{
    float const n=norm(v);
    if(n>1e-6)
        return v/n;
    else
        return vec4(1.0f,0.0f,0.0f,0.0f); //default case
}


}
