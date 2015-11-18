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

#ifndef MAT2_HPP
#define MAT2_HPP

#include <ostream>
#include <array>

namespace cpe
{
class vec2;

/** Matrix 2x2 */
class mat2
{

public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor (identity) */
    mat2();
    /** Direct constructor with every value */
    mat2(float x00,float x01,
         float x10,float x11);

    // ********************************************* //
    //  Special initialization
    // ********************************************* //

    /** Build identity matrix */
    void set_identity();
    /** Build zero matrix */
    void set_zeros();
    /** Build rotation matrix */
    void set_rotation(float angle);
    /** Build uniform scaling matrix */
    void set_scaling(float s);
    /** Build scaling matrix */
    void set_scaling(float s_x,float s_y);


    // ********************************************* //
    //  Element access
    // ********************************************* //

    /** Access to the k_th entry (k in [0,1]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,1]) */
    float& operator[](int k);

    /** Access to the k_th entry (k1,k2 in [0,1]) */
    float operator()(int k1,int k2) const;
    /** Access to the k_th entry (k1,k2 in [0,1]) */
    float& operator()(int k1,int k2);

    /** Fast pointer access
        \warning unprotected access */
    float const* pointer() const;


private:

    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** Internal storage of the matrix */
    std::array<float,4> data;

};



// ********************************************* //
//  Math function
// ********************************************* //

/** Matrix transpose */
mat2 transposed(mat2 const& m);

/** Matrix determinant */
float determinant(mat2 const& m);

/** Matrix inverse */
mat2 inverted(mat2 const& m);


// ********************************************* //
//  Math operator
// ********************************************* //

/** Matrix addition */
mat2& operator+=(mat2& lhs,mat2 const& rhs);
/** Matrix substraction */
mat2& operator-=(mat2& lhs,mat2 const& rhs);
/** Matrix multiplication */
mat2& operator*=(mat2& lhs,mat2 const& rhs);
/** Matrix multiplication by a scalar */
mat2& operator*=(mat2& lhs,float s);
/** Matrix division by a scalar */
mat2& operator/=(mat2& lhs,float s);


/** Matrix addition */
mat2 operator+(mat2 const& lhs,mat2 const& rhs);
/** Matrix substraction */
mat2 operator-(mat2 const& lhs,mat2 const& rhs);

/** Matrix multiplication with a scalar */
mat2 operator*(mat2 const& m,float s);
/** Matrix multiplication with a scalar */
mat2 operator*(float s,mat2 const& m);
/** Matrix division with a scalar */
mat2 operator/(mat2 const& m,float s);

/** Matrix multiplication */
mat2 operator*(mat2 const& lhs,mat2 const& rhs);

/** Matrix multiplication */
vec2 operator*(mat2 const& lhs,vec2 const& rhs);

/** Unary negation */
mat2 operator-(mat2 const& m);


// ********************************************* //
//  Output
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const mat2& m);






}

#endif
