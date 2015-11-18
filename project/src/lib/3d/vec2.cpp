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



#include "vec2.hpp"
#include "../common/error_handling.hpp"

#include <cmath>


namespace cpe
{

vec2::vec2()
    :x_data(0.0f),y_data(0.0f)
{}

vec2::vec2(float const x_param,float const y_param)
    :x_data(x_param),y_data(y_param)
{}

float vec2::x() const
{
    return x_data;
}

float& vec2::x()
{
    return x_data;
}

float vec2::y() const
{
    return y_data;
}

float& vec2::y()
{
    return y_data;
}



float vec2::operator[](int const k) const
{
    ASSERT_CPE(k<2,"Index should be <2");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float& vec2::operator[](int const k)
{
    ASSERT_CPE(k<2,"Index should be <2");
    ASSERT_CPE(k>=0,"Negative index");
    switch (k)
    {
    case 0:
        return x_data;
    case 1:
        return y_data;
    default:
        throw cpe::exception_cpe("Problem",EXCEPTION_PARAMETERS_CPE);
    };
}

float vec2::operator()(int const k) const
{
    return (*this)[k];
}
float& vec2::operator()(int const k)
{
    return (*this)[k];
}



vec2& operator+=(vec2& lhs,vec2 const& rhs)
{
    lhs.x() += rhs.x();
    lhs.y() += rhs.y();
    return lhs;

}

vec2& operator-=(vec2& lhs,vec2 const& rhs)
{
    lhs.x() -= rhs.x();
    lhs.y() -= rhs.y();
    return lhs;
}

vec2& operator*=(vec2& v,float const s)
{
    v.x() *= s;
    v.y() *= s;
    return v;
}

vec2& operator/=(vec2& v,float const s)
{
    v.x() /= s;
    v.y() /= s;
    return v;
}

vec2 operator+(vec2 const& lhs,vec2 const& rhs)
{
    vec2 temp=lhs;
    temp+=rhs;
    return temp;
}

vec2 operator-(vec2 const& lhs,vec2 const& rhs)
{
    vec2 temp=lhs;
    temp-=rhs;
    return temp;
}

vec2 operator*(vec2 const& v,float const s)
{
    vec2 temp=v;
    temp*=s;
    return temp;
}

vec2 operator*(float s,vec2 const& v)
{
    return v*s;
}

vec2 operator/(vec2 const& v,float const s)
{
    vec2 temp=v;
    temp*=s;
    return temp;
}

vec2 operator-(vec2 const& v)
{
    return vec2(-v.x(),-v.y());
}


std::ostream& operator<<(std::ostream& stream,vec2 const& p)
{
    stream<<p.x()<<" "<<p.y();
    return stream;
}

const float *vec2::pointer() const
{
    return &x_data;
}




float dot(vec2 const& lhs,vec2 const& rhs)
{
    return lhs.x()*rhs.x()+lhs.y()*rhs.y();
}

float norm(vec2 const& v)
{
    return std::sqrt(v.x()*v.x()+v.y()*v.y());
}

vec2 normalized(vec2 const& v)
{
    float const n=norm(v);
    if(n>1e-6)
        return v/n;
    else
        return vec2(1.0f,0.0f); //default case
}


constexpr int vec2::size(){return 2;}
float* vec2::begin() {return &x_data;}
float* vec2::end() {return &y_data+1;}
const float* vec2::begin() const {return &x_data;}
const float* vec2::end() const {return &y_data+1;}
const float* vec2::cbegin() const {return &x_data;}
const float* vec2::cend() const {return &y_data+1;}


}
