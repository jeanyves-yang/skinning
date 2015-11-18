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


#include "../3d/vec3.hpp"
#include "trackball.hpp"

#include <cmath>

namespace cpe
{

    trackball::trackball()
        :disc_radius(0.8f)
    {
        quaternion q1;q1.set_axis_angle({1.0f,0.0f,0.0f},M_PI/6.0f);
        quaternion q2;q2.set_axis_angle({0.0f,1.0f,0.0f},M_PI/6.0f);

        current_q=q2*q1;
    }


    float trackball::project_to_disc(float const x,float const y) const
    {
        float const n=std::sqrt(x*x+y*y);
        if(n<disc_radius*0.707107f)
            return std::sqrt(disc_radius*disc_radius-n*n);
        else
            return disc_radius*disc_radius/(2.0f*n);
    }

    void trackball::set_2d_coords(float const x0,float const y0,float const x1,float const y1)
    {


        //security to not move if start=end
        float epsilon=1e-5f;
        if( std::pow((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1),0.5f)<epsilon)
            d_q=quaternion(1.0f,0.0f,0.0f,0.0f);
        else
        {
            vec3 const p1=vec3(x0,y0,project_to_disc(x0,y0));
            vec3 const p2=vec3(x1,y1,project_to_disc(x1,y1));
            vec3 const axis = normalized(cross(p1,p2));

            vec3 const u=p1-p2;
            float t=norm(u)/(2.0f*disc_radius);
            t=std::min(std::max(t,-1.0f),1.0f); //clamp
            float const phi = 2.0f*asin(t);

            //compute quaternion to apply
            d_q.set_axis_angle(axis,phi);
        }
    }

    void trackball::apply_rotation()
    {current_q=d_q*current_q;}
    void trackball::no_motion()
    {d_q=quaternion(1.0f,0.0f,0.0f,0.0f);}


    quaternion const& trackball::quat() const{return current_q;}
    quaternion& trackball::quat(){return current_q;}

    quaternion const& trackball::d_quat() const {return d_q;}
    quaternion& trackball::d_quat() {return d_q;}

    float& trackball::radius() {return disc_radius;}
    float trackball::radius() const {return disc_radius;}

}
