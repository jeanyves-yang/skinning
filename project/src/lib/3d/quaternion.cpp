#include "quaternion.hpp"

#include "vec3.hpp"
#include "mat3.hpp"
#include <cmath>

namespace cpe
{


quaternion::quaternion()
    :data(0.0f,0.0f,0.0f,1.0f)
{}
quaternion::quaternion(float const x,float const y,float const z,float const w)
    :data(x,y,z,w)
{}


float quaternion::x() const
{
    return data.x();
}
float& quaternion::x()
{
    return data.x();
}

float quaternion::y() const
{
    return data.y();
}
float& quaternion::y()
{
    return data.y();
}

float quaternion::z() const
{
    return data.z();
}
float& quaternion::z()
{
    return data.z();
}

float quaternion::w() const
{
    return data.w();
}
float& quaternion::w()
{
    return data.w();
}

float quaternion::operator[](int const k) const
{
    return data[k];
}
float& quaternion::operator[](int const k)
{
    return data[k];
}

float quaternion::operator()(int const k) const
{
    return data(k);
}
float& quaternion::operator()(int const k)
{
    return data(k);
}

void quaternion::set_axis_angle(vec3 const& axis,float const angle)
{
    float const sin_phi=std::sin(angle/2.0f);
    float const cos_phi=std::cos(angle/2.0f);
    vec3 const n_axis = cpe::normalized(axis);

    x() = n_axis.x()*sin_phi;
    y() = n_axis.y()*sin_phi;
    z() = n_axis.z()*sin_phi;
    w() =            cos_phi;
}


float dot(quaternion const& q0,quaternion const& q1)
{
    return q0.x()*q1.x()+q0.y()*q1.y()+q0.z()*q1.z()+q0.w()*q1.w();
}

quaternion slerp(quaternion const& q0,quaternion const& q1_param,float const alpha)
{
    if(alpha <= 0)
        return q0;
    if(alpha >= 1)
        return q1_param;

    float cos_omega=dot(q0,q1_param);
    quaternion q1=q1_param;

    if(cos_omega < 0)
    {
        q1=-q1;
        cos_omega=-cos_omega;
    }

    if(cos_omega>0.9999f)
        return (1.0f-alpha)*q0+alpha*q1;

    float const sin_omega=std::sqrt(1.0f-cos_omega*cos_omega);
    float const omega=std::atan2(sin_omega,cos_omega);
    float const one_over_sin_omega=1.0f/sin_omega;

    float const k0 = sin((1.0f-alpha)*omega)*one_over_sin_omega;
    float const k1 = sin(alpha*omega)*one_over_sin_omega;

    return k0*q0+k1*q1;
}

quaternion& operator+=(quaternion& lhs,quaternion const& rhs)
{
    lhs.x() += rhs.x();
    lhs.y() += rhs.y();
    lhs.z() += rhs.z();
    lhs.w() += rhs.w();
    return lhs;
}

quaternion& operator-=(quaternion& lhs,quaternion const& rhs)
{
    lhs.x() -= rhs.x();
    lhs.y() -= rhs.y();
    lhs.z() -= rhs.z();
    lhs.w() -= rhs.w();
    return lhs;
}

quaternion& operator*=(quaternion& q,float s)
{
    q.x() *= s;
    q.y() *= s;
    q.z() *= s;
    q.w() *= s;
    return q;
}

quaternion& operator/=(quaternion& q,float s)
{
    q.x() /= s;
    q.y() /= s;
    q.z() /= s;
    q.w() /= s;
    return q;
}

quaternion operator+(quaternion const& lhs,quaternion const& rhs)
{
    quaternion temp=lhs;
    temp += rhs;
    return temp;
}

quaternion operator-(quaternion const& lhs,quaternion const& rhs)
{
    quaternion temp=lhs;
    temp -= rhs;
    return temp;
}

quaternion operator*(quaternion const& q,float s)
{
    quaternion temp=q;
    temp *= s;
    return temp;
}

quaternion operator*(float const s,quaternion const& q)
{
    return q*s;
}

quaternion operator/(quaternion const& q,float s)
{
    quaternion temp=q;
    temp /= s;
    return temp;
}

float norm(quaternion const& q)
{
    return std::sqrt(q.x()*q.x()+q.y()*q.y()+q.z()*q.z()+q.w()*q.w());
}

quaternion normalized(quaternion const& q)
{
    float const n=norm(q);
    if(std::abs(n)<1e-6f)
        return quaternion(0.0f,0.0f,0.0f,1.0f);
    else
        return q/n;
}

quaternion conjugated(quaternion const& q)
{
    return quaternion(-q.x(),-q.y(),-q.z(),q.w());
}

quaternion& operator*=(quaternion& lhs,quaternion const& rhs)
{
    quaternion temp=lhs*rhs;
    lhs=temp;
    return lhs;
}

quaternion operator*(quaternion const& lhs,quaternion const& rhs)
{
    return quaternion(lhs.x()*rhs.w() + lhs.w()*rhs.x() + lhs.y()*rhs.z() - lhs.z()*rhs.y(),
                      lhs.y()*rhs.w() + lhs.w()*rhs.y() + lhs.z()*rhs.x() - lhs.x()*rhs.z(),
                      lhs.z()*rhs.w() + lhs.w()*rhs.z() + lhs.x()*rhs.y() - lhs.y()*rhs.x(),
                      lhs.w()*rhs.w() - lhs.x()*rhs.x() - lhs.y()*rhs.y() - lhs.z()*rhs.z());
}

quaternion operator-(quaternion const& q)
{
    return quaternion(-q.x(),-q.y(),-q.z(),-q.w());
}

vec3 operator*(quaternion const& lhs,vec3 const& rhs)
{
    quaternion const z = quaternion(rhs.x(),rhs.y(),rhs.z(),0.0f);
    quaternion q = lhs*z*conjugated(lhs);

    return vec3(q.x(),q.y(),q.z());
}

mat3 quaternion::to_mat3() const
{
    float const x2=x()*x();
    float const y2=y()*y();
    float const z2=z()*z();
    float const xy=x()*y();
    float const xz=x()*z();
    float const yz=y()*z();
    float const wx=w()*x();
    float const wy=w()*y();
    float const wz=w()*z();

    return mat3(1.0f-2.0f*(y2+z2),     2.0f*(xy-wz),     2.0f*(xz+wy),
                     2.0f*(xy+wz),1.0f-2.0f*(x2+z2),     2.0f*(yz-wx),
                     2.0f*(xz-wy),     2.0f*(yz+wx),1.0f-2.0f*(x2+y2));
}

std::ostream& operator<<(std::ostream& stream,quaternion const& q)
{
    stream<<q.x()<<" "<<q.y()<<" "<<q.z()<<" "<<q.w();
    return stream;
}

}
