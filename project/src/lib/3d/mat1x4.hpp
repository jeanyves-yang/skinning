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

#ifndef MAT1X4_HPP
#define MAT1X4_HPP

#include "vec4.hpp"

namespace cpe
{
class mat4x1;
class mat4;
/** \brief Matrix 1x4 */
class mat1x4
{

public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor (identity) */
    mat1x4();
    /** Direct constructor with every value */
    mat1x4(float x00,float x01,float x02,float x03);

    // ********************************************* //
    //  Element access
    // ********************************************* //

    /** Access to the k_th entry (k in [0,3]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,3]) */
    float& operator[](int k);

    /** Access to the k1,k2 entry (k1=0 and k2 in [0,3]) */
    float operator()(int k1,int k2) const;
    /** Access to the k1,k2 entry (k1=0 and k2 in [0,3]) */
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
mat4x1 transposed(mat1x4 const& m);


// ********************************************* //
//  Math operators
// ********************************************* //

/** Matrix addition */
mat1x4& operator+=(mat1x4& lhs,mat1x4 const& rhs);
/** Matrix substraction */
mat1x4& operator-=(mat1x4& lhs,mat1x4 const& rhs);
/** Multiplication by a scalar */
mat1x4& operator*=(mat1x4& m,float s);
/** Division by a scalar */
mat1x4& operator/=(mat1x4& m,float s);
/** Multiplication by a scalar */
mat1x4& operator*=(mat1x4& lhs,mat4 const& rhs);

/** Matrix addition */
mat1x4 operator+(mat1x4 const& lhs,mat1x4 const& rhs);
/** Matrix substraction */
mat1x4 operator-(mat1x4 const& lhs,mat1x4 const& rhs);
/** Multiplication by a scalar */
mat1x4 operator*(mat1x4 const& m,float s);
/** Multiplication by a scalar */
mat1x4 operator*(float s,mat1x4 const& m);
/** Division by a scalar */
mat1x4 operator/(mat1x4 const& m,float s);

/** Matrix multiplication */
mat1x4 operator*(mat1x4 const& lhs,mat4 const& rhs);
/** Matrix multiplication */
float operator*(mat1x4 const& lhs,mat4x1 const& rhs);

/** Unary negation */
mat1x4 operator-(mat1x4 const& m);


// ********************************************* //
//  Output
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,mat1x4 const& m);







}

#endif
