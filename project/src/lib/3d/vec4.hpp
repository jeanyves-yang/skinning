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


#ifndef VEC4_HPP
#define VEC4_HPP

#include <ostream>



namespace cpe
{
/** Vectors/Points 4D */
class vec4
{
public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor */
    vec4();
    /** Direct constructor */
    vec4(float x,float y,float z,float w);

    // ********************************************* //
    //  Get/set
    // ********************************************* //

    /** Get x coordinate */
    float x() const;
    /** Get/set x coordinate */
    float& x();
    /** Get y coordinate */
    float y() const;
    /** Get/set y coordinate */
    float& y();
    /** Get z coordinate */
    float z() const;
    /** Get/set z coordinate */
    float& z();
    /** Get w coordinate */
    float w() const;
    /** Get/set w coordinate */
    float& w();

    /** Access to the k_th entry (k in [0,3]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,3]) */
    float& operator[](int k);
    /** Access to the k_th entry (k in [0,3]) */
    float operator()(int k) const;
    /** Access to the k_th entry (k in [0,3]) */
    float& operator()(int k);


    /** Fast pointer access
        \warning unprotected access */
    const float *pointer() const;

private:

    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** x coordinate */
    float x_data;
    /** y coordinate */
    float y_data;
    /** z coordinate */
    float z_data;
    /** w coordinate */
    float w_data;
};






// ********************************************* //
//  Operator +-*/
// ********************************************* //

/** Vector addition */
vec4& operator+=(vec4& lhs,vec4 const& rhs);
/** Vector substraction */
vec4& operator-=(vec4& lhs,vec4 const& rhs);
/** Multiplication by a scalar */
vec4& operator*=(vec4& v,float s);
/** Division by a scalar */
vec4& operator/=(vec4& v,float s);

/** Vector addition */
vec4 operator+(vec4 const& lhs,vec4 const& rhs);
/** Vector substraction */
vec4 operator-(vec4 const& lhs,vec4 const& rhs);
/** Multiplication by a scalar operator */
vec4 operator*(vec4 const& v,float s);
/** Multiplication by a scalar operator */
vec4 operator*(float s,vec4 const& v);
/** Division by a scalar operator */
vec4 operator/(vec4 const& v,float s);

/** Unary negation */
vec4 operator-(vec4 const& v);



// ********************************************* //
//  Math operation
// ********************************************* //

/** Perform dot product between two v4 */
float dot(vec4 const& lhs,vec4 const& rhs);

/** Get the norm of the vector */
float norm(vec4 const& v);
/** Normalize the vector to unit length */
vec4 normalized(vec4 const& v);


// ********************************************* //
//  Output
// ********************************************* //

/** Output the vector in ostream as (x,y,z) */
std::ostream& operator<<(std::ostream& stream,vec4 const& p);



}



#endif
