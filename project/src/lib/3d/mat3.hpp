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

#pragma once


#ifndef MAT3_HPP
#define MAT3_HPP

#include <ostream>
#include <array>

namespace cpe
{
class vec3;

/** Matrix 3x3 */
class mat3
{

public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor (identity) */
    mat3();
    /** Direct constructor with every value */
    mat3(float x00,float x01,float x02,
         float x10,float x11,float x12,
         float x20,float x21,float x22);

    // ********************************************* //
    //  Special initialization
    // ********************************************* //

    /** Build identity matrix */
    void set_identity();
    /** Build zero matrix */
    void set_zeros();
    /** Build rotation matrix */
    void set_rotation(const vec3& axis,float angle);
    /** Build scaling matrix */
    void set_scaling(float s);
    /** Build scaling matrix */
    void set_scaling(float s_x,float s_y,float s_z);


    // ********************************************* //
    //  Element access
    // ********************************************* //

    /** Access to the k_th entry (k in [0,9]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,9]) */
    float& operator[](int k);

    /** Access to the (k1,k2) entry (k1,k2 in [0,3]) */
    float operator()(int k1,int k2) const;
    /** Access to the (k1,k2) entry (k1,k2 in [0,3]) */
    float& operator()(int k1,int k2);

    /** Fast pointer access
       \warning unprotected access */
    float const* pointer() const;


private:

    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** Internal storage of the matrix */
    std::array<float,9> data;


};

// ********************************************* //
//  Math function
// ********************************************* //

/** Matrix transpose */
mat3 transposed(mat3 const& m);

/** Matrix determinant */
float determinant(mat3 const& m);

/** Matrix inverse */
mat3 inverted(mat3 const& m);

// ********************************************* //
//  Math operator
// ********************************************* //

/** Matrix addition */
mat3& operator+=(mat3& lhs,mat3 const& rhs);
/** Matrix substraction */
mat3& operator-=(mat3& lhs,mat3 const& rhs);
/** Matrix operator */
mat3& operator*=(mat3& lhs,mat3 const& rhs);
/** Matrix operator */
mat3& operator*=(mat3& m,float s);
/** Matrix division */
mat3& operator/=(mat3& m,float s);


/** Matrix addition */
mat3 operator+(mat3 const& lhs,mat3 const& rhs);
/** Matrix substraction */
mat3 operator-(mat3 const& lhs,mat3 const& rhs);
/** Matrix operator */
mat3 operator*(mat3 const& lhs,mat3 const& rhs);
/** Matrix operator */
mat3 operator*(mat3 const& m,float s);
/** Matrix operator */
mat3 operator*(float s,mat3 const& m);
/** Matrix division */
mat3 operator/(mat3 const& m,float s);

/** Matrix multiplication */
vec3 operator*(mat3 const& lhs,vec3 const& rhs);

/** \brief unary negation */
mat3 operator-(mat3 const& m);


// ********************************************* //
//  Output
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const mat3& m);





}

#endif
