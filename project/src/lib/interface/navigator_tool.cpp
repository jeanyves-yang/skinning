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



#include "navigator_tool.hpp"

#include "../3d/mat3.hpp"
#include "../3d/quaternion.hpp"

#include <cmath>
#include <iostream>

namespace cpe
{

    navigator_tool::navigator_tool()
        :x_size(800),
          y_size(800),mouse_x_previous(0),mouse_y_previous(0),is_left_button(false),is_right_button(false)
    {
        fov=55.0f*M_PI/180.0;
        znear=1e-5f;
        zfar=1.0f;
        dist=-100.0f;
        tr=vec3(0.0f,0.0f,0.0f);
    }

    unsigned int& navigator_tool::screen_size_x(){return x_size;}
    unsigned int navigator_tool::screen_size_x() const{return x_size;}

    unsigned int& navigator_tool::screen_size_y(){return y_size;}
    unsigned int navigator_tool::screen_size_y() const{return y_size;}

    float& navigator_tool::dist_cam() {return dist;}
    float navigator_tool::dist_cam() const {return dist;}

    float navigator_tool::field_of_view() const
    {
        return fov;
    }

    void navigator_tool::go_forward(float const d_L)
    {
        vec3 const z(0,0,1);
        tr += d_L*(conjugated(track.quat())*z);
    }

    void navigator_tool::go_right  (float const d_L)
    {
        vec3 const x(-1,0,0);
        tr += d_L*(conjugated(track.quat())*x);
    }

    void navigator_tool::go_up     (float const d_L)
    {
        vec3 const y(0,-1,0);
        tr += d_L*(conjugated(track.quat())*y);
    }

    int& navigator_tool::x_previous() {return mouse_x_previous;}
    int navigator_tool::x_previous() const {return mouse_x_previous;}

    int& navigator_tool::y_previous() {return mouse_y_previous;}
    int navigator_tool::y_previous() const {return mouse_y_previous;}


    bool& navigator_tool::left_button() {return is_left_button;}
    bool navigator_tool::left_button() const {return is_left_button;}

    bool& navigator_tool::right_button() {return is_right_button;}
    bool navigator_tool::right_button() const {return is_right_button;}

    void navigator_tool::trackball_rotate(int const x,int const y)
    {
        float const x_old=mouse_x_previous;
        float const y_old=mouse_y_previous;
        float const h=y_size;
        float const w=x_size;

        float const x0=(2.0f*x_old-w)/w;
        float const y0=(h-2.0f*y_old)/h;
        float const x1=(2.0f*x-w)/w;
        float const y1=(h-2.0f*y)/h;
        if(std::sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1))>1e-4)
        {
            track.set_2d_coords(x0,y0,x1,y1);
            track.apply_rotation();
        }
        mouse_x_previous=x;
        mouse_y_previous=y;
    }

    void navigator_tool::trackball_zoom(int const y)
    {
        //magnification factor
        float const F0=500.0f;

        float const y_old=mouse_y_previous;

        float const u = y-y_old;
        float const fu= u/F0;

        dist += (std::fabs(dist)+1.0f)*fu;
        dist = std::min(dist,0.0f);
        mouse_y_previous=y;

    }

    std::vector<float> navigator_tool::projection_param() const
    {
        float const aspect=static_cast<float>(x_size)/static_cast<float>(y_size);
        float const top=std::tan(fov*0.5f)*znear;
        float left= aspect*top;
        std::vector<float> param;
        param.push_back(left);
        param.push_back(top);
        param.push_back(znear);
        param.push_back(zfar);
        param.push_back(aspect);


        return param;
    }

    mat3 navigator_tool::camera_orientation() const
    {
        return track.quat().to_mat3();
    }
    vec3 navigator_tool::camera_translation() const
    {
        return tr;
    }
    vec3 navigator_tool::camera_position() const
    {
        vec3 const p0(0.0f,0.0f,dist_cam());
        vec3 p=transposed(camera_orientation())*p0;
        p+=tr;
        return -p;
    }

    void navigator_tool::increase_frame_number() {++frame;}

    unsigned int navigator_tool::time() const {return current_time;}
    unsigned int& navigator_tool::time() {return current_time;}

    float navigator_tool::update_fps()
    {
        current_fps=static_cast<float>(frame*1000.0f)/static_cast<float>(current_time-old_time);
        old_time=current_time;
        frame=0;
        return current_fps;
    }
    float navigator_tool::delta_time()
    {
        return current_time-old_time;
    }

    float navigator_tool::fps()
    {
        return current_fps;
    }


    std::pair<vec3,vec3> navigator_tool::ray_world_space_cam1(int const x_screen,int const y_screen) const
    {
//        float const h=y_size;
//        float const w=x_size;

//        float const loc_x=(2.0f*x-w)/w;
//        float const loc_y=(h-2.0f*y)/h;

//        vec3 const local(loc_x,loc_y,0.0f);
//        vec3 const proj_ray=(local[0]*Lh*aspect,local[1]*Lh,-znear);




        //normalized screen coordinates
        float const local_x=(static_cast<int>(screen_size_x())-2.0f*x_screen)/static_cast<float>(screen_size_x());
        float const local_y=(2.0f*y_screen-static_cast<int>(screen_size_y()))/static_cast<float>(screen_size_y());

       // std::cout<<local_x<<","<<local_y<<std::endl;

        vec3 const local(local_x,local_y,0.0f);
        std::vector<float> const proj_param=projection_param();
        float const Lh=-proj_param[1];
        float const aspect=proj_param[4];


        vec3 const proj_ray(local[0]*Lh*aspect,local[1]*Lh,-znear);

        mat3 const mod=camera_orientation();
        mat3 const mod_inv=transposed(mod);

        vec3 const ray=normalized(mod_inv*proj_ray);
        vec3 const center=camera_position();

        return std::make_pair(center,ray);
    }


}
