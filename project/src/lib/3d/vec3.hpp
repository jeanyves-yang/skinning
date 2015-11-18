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

#ifndef VEC3_HPP
#define VEC3_HPP

#include <ostream>

namespace cpe
{

/** Vectors/Points 3D */
class vec3
{
public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor */
    vec3();
    /** Direct constructor */
    vec3(float x,float y,float z);

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
    /** Get z coordinate */
    float z() const;
    /** Get/Set z coordinate */
    float& z();

    /** Access to the k_th entry (k in [0,2]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,2]) */
    float& operator[](int k);
    /** Access to the k_th entry (k in [0,2]) */
    float operator()(int k) const;
    /** Access to the k_th entry (k in [0,2]) */
    float& operator()(int k);

    /** Fast pointer access
        \warning unprotected access */
    const float *pointer() const;


    // ********************************************* //
    //  For-range compatibility
    // ********************************************* //

    /** Returns 3 */
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
    /** z coordinate */
    float z_data;

};



// ********************************************* //
//  Operator +-*/
// ********************************************* //

/** Vector addition */
vec3& operator+=(vec3& lhs,vec3 const& rhs);
/** Vector substraction */
vec3& operator-=(vec3& lhs,vec3 const& rhs);
/** Multiplication by a scalar */
vec3& operator*=(vec3& v,float s);
/** Division by a scalar */
vec3& operator/=(vec3& v,float s);


/** Vector addition */
vec3 operator+(vec3 const& lhs,vec3 const& rhs);
/** Vector substraction */
vec3 operator-(vec3 const& lhs,vec3 const& rhs);

/** Multiplication by a scalar operator */
vec3 operator*(vec3 const& v,float s);
/** Multiplication by a scalar operator */
vec3 operator*(float s,vec3 const& v);
/** Division by a scalar operator */
vec3 operator/(vec3 const& v,float s);

/** \brief unary negation */
vec3 operator-(vec3 const& v);


// ********************************************* //
//  Math operation
// ********************************************* //

/** Compute dot product between two vec3 */
float dot(vec3 const& lhs,vec3 const& rhs);

/** Compute the norm of a vec3 */
float norm(vec3 const& v);
/** Compute the vector of unit norm */
vec3 normalized(vec3 const& v);

/** Compute cross product between two vec3 */
vec3 cross(vec3 const& lhs,vec3 const& rhs);

/** Compute the reflected vector with respect to the given axis */
vec3 reflected(vec3 const& vec,vec3 const& axis);

// ********************************************* //
//  Output
// ********************************************* //

/** \brief output the vector in ostream as "x y z" */
std::ostream& operator<<(std::ostream& stream,const vec3& p);


}



#endif
