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

#ifndef MAT4_HPP
#define MAT4_HPP

#include <iostream>
#include <array>



namespace cpe
{
class vec3;
class vec4;
class mat3;

/** Matrix 4x4 */
class mat4
{


public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor (identity) */
    mat4();
    /** Direct constructor with every value */
    mat4(float x00,float x01,float x02,float x03,
         float x10,float x11,float x12,float x13,
         float x20,float x21,float x22,float x23,
         float x30,float x31,float x32,float x33);
    /** \brief direct constructor from matrix 3 */
    mat4(mat3 const & m);

    // ********************************************* //
    //  Special initialization
    // ********************************************* //

    /** Build identity matrix */
    void set_identity();
    /** Build rotation matrix */
    void set_rotation(vec3 const& axis,float angle);
    /** Build scaling matrix */
    void set_scaling(float s);
    /** Build scaling matrix */
    void set_scaling(float s_x,float s_y,float s_z,float s_w);
    /** Build translation matrix */
    void set_translation(vec3 const& translation);
    /** Build from matrix3 and translation */
    void set_transformation(mat3 const& m3,vec3 const& translation);

    // ********************************************* //
    //  Projection matrix (emulate glu(t) functions)
    // ********************************************* //

    /** \brief build a perspective projection similar to gluPerspective
        \param float fovy: in radian
         see: http://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
    */
    void set_projection_perspective(float fovy,float aspect,float z_near,float z_far);
    /** \brief build a perspective projection (frustum) similar to glFrustum
         see: http://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml
    */
    void set_projection_frustum(float left,float right,float bottom,float top,float near,float far);
    /** \brief build an orthographic projection similar to glOrtho
         see: http://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    */
    void set_projection_orthographic(float left,float right,float bottom,float top,float near,float far);
    /** \brief build a perspective projection similar to gluLookAt
         see: http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
    */
    void set_projection_look_at(mat4 const& current_matrix,vec3 const& eye,vec3 const& center,vec3 const& up);


    // ********************************************* //
    //  Element access
    // ********************************************* //

    /** Access to the k_th entry (k in [0,15]) */
    float operator[](int k) const;
    /** Access to the k_th entry (k in [0,15]) */
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

    /** \brief internal storage of the matrix */
    std::array<float,16> data;
};



// ********************************************* //
//  Math function
// ********************************************* //

/** Matrix transpose */
mat4 transposed(mat4 const& m);

/** Matrix determinant */
float determinant(mat4 const& m);

/** Matrix inverse */
mat4 inverted(mat4 const& m);


// ********************************************* //
//  Math operator
// ********************************************* //

/** Matrix addition */
mat4& operator+=(mat4& lhs,mat4 const& rhs);
/** Matrix substraction */
mat4& operator-=(mat4& lhs,mat4 const& rhs);
/** Matrix multiplication */
mat4& operator*=(mat4& lhs,mat4 const& rhs);
/** Multiplication by a scalar */
mat4& operator*=(mat4& m,float s);
/** Division by a scalar */
mat4& operator/=(mat4& m,float s);



/** Matrix addition */
mat4 operator+(mat4 const& lhs,mat4 const& rhs);
/** Matrix substraction */
mat4 operator-(mat4 const& lhs,mat4 const& rhs);
/** Matrix multiplication */
mat4 operator*(mat4 const& lhs,mat4 const& rhs);
/** Multiplication by a scalar */
mat4 operator*(mat4 const& m,float s);
/** Multiplication by a scalar */
mat4 operator*(float s,mat4 const& m);
/** Division by a scalar */
mat4 operator/(mat4 const& m,float s);

/** Multiplication matrix vector */
vec4 operator*(mat4 const& lhs,vec4 const& rhs);
/** Multiplication matrix vector (vec3)
 *  Assume the vec3 to be a point (last coordinate is 1)
 */
vec3 operator*(mat4 const& m,vec3 const& v);


/** Unary negation */
mat4 operator-(mat4 const& m);

// ********************************************* //
//  Output
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const mat4& m);

}

#endif
