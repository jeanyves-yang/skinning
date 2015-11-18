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

#ifndef MAT4X1_HPP
#define MAT4X1_HPP

#include "vec4.hpp"

namespace cpe
{
class mat1x4;
class mat4;

/** \brief Matrix 4x1 */
class mat4x1
{

public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor (identity) */
    mat4x1();
    /** Direct constructor with every value */
    mat4x1(float x00,float x10,float x20,float x30);

    // ********************************************* //
    //  Element access
    // ********************************************* //

    /** Access to the k_th entry (k in [0,3]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,3]) */
    float& operator[](int k);

    /** Access to the k1,k2 entry (k1 in [0,3] and k2=0 */
    float operator()(int k1,int k2) const;
    /** Access to the k1,k2 entry (k1 in [0,3] and k2=0 */
    float& operator()(int k1,int k2);

    /** Fast pointer access
        \warning unprotected access */
    const float* pointer() const;

private:

    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** Internal storage of the matrix */
    vec4 data;

};

// ********************************************* //
//  Math functions
// ********************************************* //

/** Matrix transposed */
mat1x4 transposed(mat4x1 const& m);


// ********************************************* //
//  Math operators
// ********************************************* //

/** Matrix addition */
mat4x1& operator+=(mat4x1& lhs,mat4x1 const& rhs);
/** Matrix substraction */
mat4x1& operator-=(mat4x1& lhs,mat4x1 const& rhs);
/** Multiplication by a scalar */
mat4x1& operator*=(mat4x1& m,float s);
/** Division by a scalar */
mat4x1& operator/=(mat4x1& m,float s);

/** Matrix addition */
mat4x1 operator+(mat4x1 const& lhs,mat4x1 const& rhs);
/** Matrix substraction */
mat4x1 operator-(mat4x1 const& lhs,mat4x1 const& rhs);
/** Multiplication by a scalar */
mat4x1 operator*(mat4x1 const& m,float s);
/** Multiplication by a scalar */
mat4x1 operator*(float s,mat4x1 const& m);
/** Division by a scalar */
mat4x1 operator/(mat4x1 const& m,float s);

/** Matrix multiplication */
mat4x1 operator*(mat4 const& lhs,mat4x1 const& rhs);

/** Unary negation */
mat4x1 operator-(mat4x1 const& m);


// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,mat4x1 const& m);



}

#endif
