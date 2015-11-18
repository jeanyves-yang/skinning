#pragma once

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "vec4.hpp"

namespace cpe
{
class vec3;
class mat3;

class quaternion
{
public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor */
    quaternion();
    /** Direct constructor from quaternion value */
    quaternion(float x,float y,float z,float w);

    // ********************************************* //
    //  SPECIAL INITIALIZER
    // ********************************************* //

    void set_axis_angle(vec3 const& axis,float angle);

    // ********************************************* //
    //  ACCESSOR
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

    // ********************************************* //
    //  convert to other type
    // ********************************************* //

    /** Convert the quaternion to rotation matrix */
    mat3 to_mat3() const;

private:
    vec4 data;
};

// ********************************************* //
//  Math operation
// ********************************************* //

/** Scalar product between quaternion */
float dot(quaternion const& lhs,quaternion const& rhs);
/** Quaternion interpolation */
quaternion slerp(quaternion const& q0,quaternion const& q1,float alpha);
/** Quaternion norm */
float norm(quaternion const& q);
/** Normalization of the quaternion */
quaternion normalized(quaternion const& q);
/** Conjugate of the quaternion (-v,w) */
quaternion conjugated(quaternion const& q);

// ********************************************* //
//  Math operator
// ********************************************* //

/** Quaternion addition */
quaternion& operator+=(quaternion& lhs,quaternion const& rhs);
/** Quaternion substraction */
quaternion& operator-=(quaternion& lhs,quaternion const& rhs);
/** Quaternion multiplication (v1 w2 + v2 w1 - v1xv2 , w1 w2 - v1.v2) */
quaternion& operator*=(quaternion& lhs,quaternion const& rhs);
/** Quaternion multiplication by a scalar */
quaternion& operator*=(quaternion& q,float s);
/** Quaternion division by a scalar */
quaternion& operator/=(quaternion& q,float s);

/** Quaternion addition */
quaternion operator+(quaternion const& lhs,quaternion const& rhs);
/** Quaternion substraction */
quaternion operator-(quaternion const& lhs,quaternion const& rhs);
/** Quaternion multiplication by a scalar */
quaternion operator*(quaternion const& q,float s);
/** Quaternion multiplication by a scalar */
quaternion operator*(float s,quaternion const& q);
/** Quaternion division by a scalar */
quaternion operator/(quaternion const& q,float s);

/** Unary negation */
quaternion operator-(quaternion const& q);

/** Quaternion multiplication (v1 w2 + v2 w1 - v1xv2 , w1 w2 - v1.v2) */
quaternion operator*(quaternion const& lhs,quaternion const& rhs);

/** Applying quaternion to vec3 (rotation): q v q^bar */
vec3 operator*(quaternion const& lhs,vec3 const& rhs);

/** Output the quaternion in ostream as (x,y,z,w) */
std::ostream& operator<<(std::ostream& stream,quaternion const& q);

}

#endif
