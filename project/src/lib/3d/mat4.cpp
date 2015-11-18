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


#include "mat4.hpp"

#include "mat3.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "../common/error_handling.hpp"

#include <cmath>


namespace cpe
{

mat4::mat4()
    :data( {{ 1.0f , 0.0f , 0.0f , 0.0f ,
              0.0f , 1.0f , 0.0f , 0.0f ,
              0.0f , 0.0f , 1.0f , 0.0f ,
              0.0f , 0.0f , 0.0f , 1.0f }} )
{}

mat4::mat4(float const x00,float const x01,float const x02,float const x03,
           float const x10,float const x11,float const x12,float const x13,
           float const x20,float const x21,float const x22,float const x23,
           float const x30,float const x31,float const x32,float const x33)
{
    data[0]=x00;data[4]=x01;data[8]=x02;data[12]=x03;
    data[1]=x10;data[5]=x11;data[9]=x12;data[13]=x13;
    data[2]=x20;data[6]=x21;data[10]=x22;data[14]=x23;
    data[3]=x30;data[7]=x31;data[11]=x32;data[15]=x33;
}

mat4::mat4(mat3 const& m3)
{
    data[0]=m3(0,0);data[4]=m3(0,1);data[8]=m3(0,2);data[12]=0.0f;
    data[1]=m3(1,0);data[5]=m3(1,1);data[9]=m3(1,2);data[13]=0.0f;
    data[2]=m3(2,0);data[6]=m3(2,1);data[10]=m3(2,2);data[14]=0.0f;
    data[3]=0.0f;data[7]=0.0f;data[11]=0.0f;data[15]=1.0f;
}

void mat4::set_identity()
{
    data[0]=1.0f; data[4]=0.0f;  data[8]=0.0f; data[12]=0.0f;
    data[1]=0.0f; data[5]=1.0f;  data[9]=0.0f; data[13]=0.0f;
    data[2]=0.0f; data[6]=0.0f; data[10]=1.0f; data[14]=0.0f;
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=1.0f;
}

void mat4::set_rotation(vec3 const& axis,float const angle)
{
    vec3 const n=normalized(axis);

    float const cos_t=std::cos(angle);
    float const sin_t=std::sin(angle);

    data[0]=cos_t+n[0]*n[0]*(1.0f-cos_t);       data[4]=n[0]*n[1]*(1.0f-cos_t)-n[2]*sin_t;    data[8]=n[1]*sin_t+n[0]*n[2]*(1.0f-cos_t);   data[12]=0.0f;
    data[1]=n[2]*sin_t+n[0]*n[1]*(1.0f-cos_t);  data[5]=cos_t+n[1]*n[1]*(1.0f-cos_t);         data[9]=-n[0]*sin_t+n[1]*n[2]*(1.0f-cos_t);  data[13]=0.0f;
    data[2]=-n[1]*sin_t+n[0]*n[2]*(1.0f-cos_t); data[6]=n[0]*sin_t+n[1]*n[2]*(1.0f-cos_t);    data[10]=cos_t+n[2]*n[2]*(1.0f-cos_t);       data[14]=0.0f;
    data[3]=0.0f;                               data[7]=0.0f;                                 data[11]=0.0f;                               data[15]=1.0f;
}

void mat4::set_scaling(float const s)
{
    data[0]=s;    data[4]=0.0f;  data[8]=0.0f; data[12]=0.0f;
    data[1]=0.0f; data[5]=s;     data[9]=0.0f; data[13]=0.0f;
    data[2]=0.0f; data[6]=0.0f; data[10]=s;    data[14]=0.0f;
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=1.0f;
}

void mat4::set_scaling(float const s_x,float const s_y,float const s_z,float const s_w)
{
    data[0]=s_x;  data[4]=0.0f;  data[8]=0.0f; data[12]=0.0f;
    data[1]=0.0f; data[5]=s_y;   data[9]=0.0f; data[13]=0.0f;
    data[2]=0.0f; data[6]=0.0f; data[10]=s_z;  data[14]=0.0f;
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=s_w;
}

void mat4::set_translation(vec3 const& translation)
{
    data[0]=1.0f;  data[4]=0.0f;  data[8]=0.0f; data[12]=translation.x();
    data[1]=0.0f; data[5]=1.0f;   data[9]=0.0f; data[13]=translation.y();
    data[2]=0.0f; data[6]=0.0f; data[10]=1.0f;  data[14]=translation.z();
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=1.0f;
}

void mat4::set_transformation(mat3 const& m,vec3 const& translation)
{
    data[0]=m[0]; data[4]=m[3]; data[8]=m[6];  data[12]=translation.x();
    data[1]=m[1]; data[5]=m[4]; data[9]=m[7];  data[13]=translation.y();
    data[2]=m[2]; data[6]=m[5]; data[10]=m[8]; data[14]=translation.z();
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=1.0f;
}


float mat4::operator[](int k) const
{
    ASSERT_CPE(k>=0,"Index must be positive");
    ASSERT_CPE(k<16,"Index must be < 16");
    return data[k];
}
float& mat4::operator[](int k)
{
    ASSERT_CPE(k>=0,"Index must be positive");
    ASSERT_CPE(k<16,"Index must be < 16");
    return data[k];
}


float mat4::operator()(int k1,int k2) const
{
    ASSERT_CPE(k1>=0,"Index must be positive");
    ASSERT_CPE(k1<4,"Index must be < 4");
    ASSERT_CPE(k2>=0,"Index must be positive");
    ASSERT_CPE(k2<4,"Index must be < 4");
    return data[4*k2+k1];
}

float& mat4::operator()(int k1,int k2)
{
    ASSERT_CPE(k1>=0,"Index must be positive");
    ASSERT_CPE(k1<4,"Index must be < 4");
    ASSERT_CPE(k2>=0,"Index must be positive");
    ASSERT_CPE(k2<4,"Index must be < 4");
    return data[4*k2+k1];
}




std::ostream& operator<<(std::ostream& stream,mat4 const& m)
{
    stream<<m[0]<<","<<m[4]<<","<<m[8]<<","<<m[12]<<"\n"<<
            m[1]<<","<<m[5]<<","<<m[9]<<","<<m[13]<<"\n"<<
            m[2]<<","<<m[6]<<","<<m[10]<<","<<m[14]<<"\n"<<
            m[3]<<","<<m[7]<<","<<m[11]<<","<<m[15]<<"\n";
    return stream;
}

float const* mat4::pointer() const
{
    return &data[0];
}


void mat4::set_projection_perspective(float const fovy,float const aspect,float const z_near,float const z_far)
{
    const float f=1.0f/std::tan(fovy/2.0f);
    const float fp=f/aspect;

    const float L=z_near-z_far;
    const float epsilon=1e-6f;

    ASSERT_CPE(std::abs(L)>epsilon,"z_far-z_near too small");

    const float C=(z_far+z_near)/L;
    const float D=(2.0f*z_far*z_near)/L;

    data[0]=fp;   data[4]=0.0f; data[8]=0.0f; data[12]=0.0f;
    data[1]=0.0f; data[5]=f;    data[9]=0.0f; data[13]=0.0f;
    data[2]=0.0f; data[6]=0.0f; data[10]=C;   data[14]=D;
    data[3]=0.0f; data[7]=0.0f; data[11]=-1;  data[15]=0.0f;
}

void mat4::set_projection_frustum(float const left,float const right,float const bottom,float const top,float const near,float const far)
{
    const float width=right-left;
    const float height=top-bottom;
    const float L=far-near;

    const float epsilon=1e-6f;

    ASSERT_CPE(std::abs(width)>epsilon,"Bad camera projection");
    ASSERT_CPE(std::abs(height)>epsilon,"Bad camera projection");
    ASSERT_CPE(std::abs(L)>epsilon,"Bad camera projection");

    const float fw=2.0f*near/width;
    const float fh=2.0f*near/height;
    const float A=(right+left)/width;
    const float B=(top+bottom)/height;
    const float C=-(far+near)/L;
    const float D=-2.0f*far*near/L;

    data[0]=fw;   data[4]=0.0f; data[8]=A;   data[12]=0.0f;
    data[1]=0.0f; data[5]=fh;   data[9]=B;   data[13]=0.0f;
    data[2]=0.0f; data[6]=0.0f; data[10]=C;  data[14]=D;
    data[3]=0.0f; data[7]=0.0f; data[11]=-1; data[15]=0.0f;

}

void mat4::set_projection_orthographic(float const left,float const right,float const bottom,float const top,float const near,float const far)
{
    const float width=right-left;
    const float height=top-bottom;
    const float L=far-near;

    const float epsilon=1e-6f;
    ASSERT_CPE(std::abs(width)>epsilon,"Bad camera projection");
    ASSERT_CPE(std::abs(height)>epsilon,"Bad camera projection");
    ASSERT_CPE(std::abs(L)>epsilon,"Bad camera projection");

    const float sx= 2.0f/width;
    const float sy= 2.0f/height;
    const float sz=-2.0f/L;
    const float tx=-(right+left)/width;
    const float ty=-(top+bottom)/height;
    const float tz=-(far+near)/L;


    data[0]=sx;   data[4]=0.0f; data[8]=0.0f;  data[12]=tx;
    data[1]=0.0f; data[5]=sy;   data[9]=0.0f;  data[13]=ty;
    data[2]=0.0f; data[6]=0.0f; data[10]=sz;   data[14]=tz;
    data[3]=0.0f; data[7]=0.0f; data[11]=0.0f; data[15]=1.0f;

}

void mat4::set_projection_look_at(mat4 const& current_matrix,vec3 const& eye,vec3 const& center,vec3 const& up)
{
    vec3 f=normalized(center-eye);
    vec3 s=cross(f,up);
    vec3 u=cross(s,f);

    mat4 M(    s.x(), s.y(), s.z(), 0.0f,
               u.x(), u.y(), u.z(), 0.0f,
              -f.x(),-f.y(),-f.z(), 0.0f,
                0.0f,  0.0f,  0.0f, 1.0f);

    mat4 T;T.set_translation(-eye);
    M=M*T;
    M=current_matrix*M;

    *this=M;
}




mat4& operator+=(mat4& lhs,mat4 const& rhs)
{
    for(int k=0;k<16;++k)
        lhs[k] += rhs[k];
    return lhs;
}

mat4& operator-=(mat4& lhs,mat4 const& rhs)
{
    for(int k=0;k<16;++k)
        lhs[k] -= rhs[k];
    return lhs;
}

mat4& operator*=(mat4& lhs,mat4 const& rhs)
{
    mat4 temp=lhs*rhs;
    lhs=temp;
    return lhs;
}

mat4& operator*=(mat4& m,float const s)
{
    for(int k=0;k<16;++k)
        m[k]*=s;
    return m;
}

mat4& operator/=(mat4& m,float const s)
{
    for(int k=0;k<16;++k)
        m[k]/=s;
    return m;
}

mat4 operator+(mat4 const& lhs,mat4 const& rhs)
{
    mat4 temp=lhs;
    temp+=rhs;
    return temp;
}

mat4 operator-(mat4 const& lhs,mat4 const& rhs)
{
    mat4 temp=lhs;
    temp-=rhs;
    return temp;
}

mat4 operator*(mat4 const& lhs,mat4 const& rhs)
{
    mat4 res(0.0f,0.0f,0.0f,0.0f,
             0.0f,0.0f,0.0f,0.0f,
             0.0f,0.0f,0.0f,0.0f,
             0.0f,0.0f,0.0f,0.0f);
    for(int k1=0;k1<4;++k1)
        for(int k2=0;k2<4;++k2)
            for(int k=0;k<4;++k)
                res(k1,k2) += lhs(k1,k)*rhs(k,k2);
    return res;
}

mat4 operator*(mat4 const& m,float const s)
{
    mat4 temp=m;
    temp*=s;
    return temp;
}

mat4 operator*(float const s,mat4 const& m)
{
    return m*s;
}

mat4 operator/(mat4 const& m,float const s)
{
    mat4 temp=m;
    temp/=s;
    return temp;
}


vec3& operator*(mat4& m,vec3 const& v);

vec4 operator*(mat4 const& lhs,vec4 const& rhs)
{
    return vec4(lhs(0,0)*rhs[0]+lhs(0,1)*rhs[1]+lhs(0,2)*rhs[2]+lhs(0,3)*rhs[3],
            lhs(1,0)*rhs[0]+lhs(1,1)*rhs[1]+lhs(1,2)*rhs[2]+lhs(1,3)*rhs[3],
            lhs(2,0)*rhs[0]+lhs(2,1)*rhs[1]+lhs(2,2)*rhs[2]+lhs(2,3)*rhs[3],
            lhs(3,0)*rhs[0]+lhs(3,1)*rhs[1]+lhs(3,2)*rhs[2]+lhs(3,3)*rhs[3]);
}
vec3 operator*(mat4 const& m,vec3 const& v)
{
    float const normalization_factor=m(3,0)*v.x()+m(3,1)*v.y()+m(3,2)*v.z()+m(3,3);
    vec3 result(m(0,0)*v.x()+m(0,1)*v.y()+m(0,2)*v.z()+m(0,3),
                m(1,0)*v.x()+m(1,1)*v.y()+m(1,2)*v.z()+m(1,3),
                m(2,0)*v.x()+m(2,1)*v.y()+m(2,2)*v.z()+m(2,3));
    result/=normalization_factor;
    return result;
}

mat4 operator-(mat4 const& m)
{
    return mat4(-m[0],-m[4],-m[8] ,-m[12],
                -m[1],-m[5],-m[9] ,-m[13],
                -m[2],-m[6],-m[10],-m[14],
                -m[3],-m[7],-m[11],-m[15]);
}

mat4 transposed(mat4 const& m)
{
    return mat4(m[0] ,m[1] ,m[2] ,m[3],
                m[4] ,m[5] ,m[6] ,m[7],
                m[8] ,m[9] ,m[10],m[11],
                m[12],m[13],m[14],m[15]);
}

float determinant(float const x00,float const x01,float const x02,
                  float const x10,float const x11,float const x12,
                  float const x20,float const x21,float const x22)
{
    return x00*(x11*x22-x21*x12)-x10*(x01*x22-x21*x02)+x20*(x01*x12-x11*x02);
}

float determinant(mat4 const& m)
{
    return m[0] * determinant(m[5],m[6],m[7] , m[9],m[10],m[11] , m[13],m[14],m[15])
            -m[4] * determinant(m[1],m[2],m[3] , m[9],m[10],m[11] , m[13],m[14],m[15])
            +m[8] * determinant(m[1],m[2],m[3] , m[5],m[6],m[7] , m[13],m[14],m[15])
            -m[12] * determinant(m[1],m[2],m[3] , m[5],m[6],m[7] , m[9],m[10],m[11]);
}

mat4 inverted(mat4 const& m)
{
    float const det = determinant(m);
    ASSERT_CPE(std::abs(det) > 1e-5 , "Non invertible matrix");

    float const x00 =  determinant(m[5],m[6],m[7] , m[9],m[10],m[11] , m[13],m[14],m[15]);
    float const x10 = -determinant(m[1],m[2],m[3] , m[9],m[10],m[11] , m[13],m[14],m[15]);
    float const x20 =  determinant(m[1],m[2],m[3] , m[5],m[6],m[7] , m[13],m[14],m[15]);
    float const x30 = -determinant(m[1],m[2],m[3] , m[5],m[6],m[7] , m[9],m[10],m[11]);

    float const x01 = -determinant(m[4],m[6],m[7] , m[8],m[10],m[11] , m[12],m[14],m[15]);
    float const x11 =  determinant(m[0],m[2],m[3] , m[8],m[10],m[11] , m[12],m[14],m[15]);
    float const x21 = -determinant(m[0],m[2],m[3] , m[4],m[6],m[7] , m[12],m[14],m[15]);
    float const x31 =  determinant(m[0],m[2],m[3] , m[4],m[6],m[7] , m[8],m[10],m[11]);

    float const x02 =  determinant(m[4],m[5],m[7] , m[8],m[9],m[11] , m[12],m[13],m[15]);
    float const x12 = -determinant(m[0],m[1],m[3] , m[8],m[9],m[11] , m[12],m[13],m[15]);
    float const x22 =  determinant(m[0],m[1],m[3] , m[4],m[5],m[7] , m[12],m[13],m[15]);
    float const x32 = -determinant(m[0],m[1],m[3] , m[4],m[5],m[7] , m[8],m[9],m[11]);

    float const x03 = -determinant(m[4],m[5],m[6] , m[8],m[9],m[10] , m[12],m[13],m[14]);
    float const x13 =  determinant(m[0],m[1],m[2] , m[8],m[9],m[10] , m[12],m[13],m[14]);
    float const x23 = -determinant(m[0],m[1],m[2] , m[4],m[5],m[6] , m[12],m[13],m[14]);
    float const x33 =  determinant(m[0],m[1],m[2] , m[4],m[5],m[6] , m[8],m[9],m[10]);

    return mat4(x00,x01,x02,x03,
                x10,x11,x12,x13,
                x20,x21,x22,x23,
                x30,x31,x32,x33)/det;

}


}
