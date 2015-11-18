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

#pragma once


#ifndef VEC2_HPP
#define VEC2_HPP

#include <ostream>

namespace cpe
{

/** Vectors/Points 2D */
class vec2
{
public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor */
    vec2();
    /** Direct constructor */
    vec2(float x,float y);

    // ********************************************* //
    //  Get/set
    // ********************************************* //

    /** Get x coordinate */
    float x() const;
    /** Get/Set x coordinate */
    float& x();
    /** Get y coordinate */
    float y() const;
    /** Get/Set y coordinate */
    float& y();


    /** Access to the k_th entry (k in [0,1]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,1]) */
    float& operator[](int k);
    /** Access to the k_th entry (k in [0,1]) */
    float operator()(int k) const;
    /** Access to the k_th entry (k in [0,1]) */
    float& operator()(int k);

    /** Fast pointer access
        \warning Unprotected access */
    const float *pointer() const;

    // ********************************************* //
    //  For-range compatibility
    // ********************************************* //

    /** Returns 2 */
    static constexpr int size();

    /** STL compatible first element */
    float* begin();
    /** STL compatible end element */
    float* end();
    /** STL compatible first element */
    const float* begin() const;
    /** STL compatible end element */
    const float* end() const;
    /** STL compatible first element */
    const float* cbegin() const;
    /** STL compatible end element */
    const float* cend() const;


private:


    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** x coordinate */
    float x_data;
    /** y coordinate */
    float y_data;

};


// ********************************************* //
//  Operator +-*/
// ********************************************* //

/** Vector addition */
vec2& operator+=(vec2& lhs,const vec2& rhs);
/** Vector substraction */
vec2& operator-=(vec2& lhs,const vec2& rhs);
/** Multiplication by a scalar */
vec2& operator*=(vec2& v,float s);
/** Division by a scalar */
vec2& operator/=(vec2& v,float s);

/** Vector addition */
vec2 operator+(vec2 const& lhs,vec2 const& rhs);
/** Vector substraction */
vec2 operator-(vec2 const& lhs,vec2 const& rhs);

/** Multiplication by a scalar */
vec2 operator*(vec2 const& v,float s);
/** Multiplication by a scalar */
vec2 operator*(float s,vec2 const& v);
/** Division by a scalar */
vec2 operator/(vec2 const& v,float s);

/** Unary negation */
vec2 operator-(vec2 const& v);


// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** Output the vector in ostream as (x,y,z) */
std::ostream& operator<<(std::ostream& stream,vec2 const& p);



// ********************************************* //
// ********************************************* //
//  Math operation
// ********************************************* //
// ********************************************* //

/** Perform dot product between two v2 */
float dot(vec2 const& lhs,vec2 const& rhs);

/** Get the norm of the vector */
float norm(vec2 const& v);
/** Return a normalized vector of unit length */
vec2 normalized(vec2 const& v);



}



#endif
