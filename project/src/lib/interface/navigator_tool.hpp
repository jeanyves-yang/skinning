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


#ifndef NAVIGATOR_TOOL_HPP
#define NAVIGATOR_TOOL_HPP

#include "trackball.hpp"
#include "../3d/vec3.hpp"
#include "../3d/mat3.hpp"

#include <vector>

namespace cpe
{

    /** \brief Container class for camera, mouse and fps manipulation
        The camera is controled using 3 parameters:
        1/ zoom factor (dist)  = translation along local z coordinate
        2/ orientation (track) = rotation transformation in this second frame controlled by arcball
        3/ translation (tr)    = final translation in the global world space
    */
    class navigator_tool
    {
    public:

        // ********************************************* //
        // ********************************************* //
        //  CONSTRUCTORS
        // ********************************************* //
        // ********************************************* //

        /** \brief empty constructor */
        navigator_tool();


        // ********************************************* //
        // ********************************************* //
        //  Screen parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief Window size x */
        unsigned int& screen_size_x();
        /** \brief Window size x */
        unsigned int screen_size_x() const;

        /** \brief Window size y */
        unsigned int& screen_size_y();
        /** \brief Window size y */
        unsigned int screen_size_y() const;


        // ********************************************* //
        // ********************************************* //
        //  Camera manipulation
        // ********************************************* //
        // ********************************************* //

        /** \brief zoom factor */
        float& dist_cam();
        /** \brief zoom factor */
        float dist_cam() const;

        /** \brief move the camera forward by a distance dL */
        void go_forward(float dL);
        /** \brief move the camera to the right by a distance dL */
        void go_right  (float dL);
        /** \brief move the camera up by a distance dL */
        void go_up     (float dL);


        /** \brief camera rotation using on-screen coordinates */
        void trackball_rotate(int x,int y);
        /** \brief camera zoom using on-screen coordinates */
        void trackball_zoom(int y);


        // ********************************************* //
        // ********************************************* //
        //  Mouse record
        // ********************************************* //
        // ********************************************* //

        /** \brief previous position of the mouse in screen x-coordinate */
        int& x_previous();
        /** \brief previous position of the mouse in screen x-coordinate */
        int x_previous() const;

        /** \brief previous position of the mouse in screen y-coordinate */
        int& y_previous();
        /** \brief previous position of the mouse in screen y-coordinate */
        int y_previous() const;

        /** \brief is left button clicked */
        bool& left_button();
        /** \brief is left button clicked */
        bool left_button() const;

        /** \brief is right button clicked */
        bool& right_button();
        /** \brief is right button clicked */
        bool right_button() const;




        // ********************************************* //
        // ********************************************* //
        // Projection parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief Projection camera parameters: left/top/znear/zfar/aspect */
        std::vector<float> projection_param() const;


        // ********************************************* //
        // ********************************************* //
        //  Camera orientation
        // ********************************************* //
        // ********************************************* //

        /** \brief get the camera orientation (matrix of the quaternion) */
        mat3 camera_orientation() const;
        /** \brief get the camera absolute translation */
        vec3 camera_translation() const;

        /** \brief get the current position of the camera */
        vec3 camera_position() const;


        // ********************************************* //
        // ********************************************* //
        //  FPS
        // ********************************************* //
        // ********************************************* //

        /** \brief increase the frame number by 1 */
        void increase_frame_number();

        /** \brief get the current elapsed time */
        unsigned int time() const;
        /** \brief get the current elapsed time */
        unsigned int& time();

        /** \brief update the fps counter and set frame to 0*/
        float update_fps();
        /** \brief elapsed time since old_time record */
        float delta_time();

        /** \brief get the current fps */
        float fps();

        // ********************************************* //
        // ********************************************* //
        //  Picking
        // ********************************************* //
        // ********************************************* //
        /** \brief give the (x,y) coordinate in screen space and return the center and the ray pointed in world space
            \return center,ray
            */
        std::pair<vec3,vec3> ray_world_space_cam1(int x_screen,int y_screen) const;


        float field_of_view() const;

   // private:


        // ********************************************* //
        // ********************************************* //
        //  Internal Camera Parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief internal rotation quaternion controled using ArcBall */
        trackball track;
        /** \brief internal camera world space translation */
        vec3 tr;
        /** \brief internal zoom magnitude (z-translation in local coordinate frame) */
        float dist;

        /** \brief internal camera FOV storage */
        float fov;
        /** \brief internal camera Znear storage */
        float znear;
        /** \brief internal camera Zfar storage */
        float zfar;

        // ********************************************* //
        // ********************************************* //
        //  Window and mouse parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief internal storage of window width */
        unsigned int x_size;
        /** \brief internal storage of window height */
        unsigned int y_size;

        /** \brief internal storage of previous clicked position of the mouse (x) */
        int mouse_x_previous;
        /** \brief internal storage of previous clicked position of the mouse (y) */
        int mouse_y_previous;


        /** \brief internal storage when left button is clicked */
        bool is_left_button;
        /** \brief internal storage when right button is clicked */
        bool is_right_button;

        // ********************************************* //
        // ********************************************* //
        //  Time parameter
        // ********************************************* //
        // ********************************************* //

        /** \brief internal storage of current fps */
        float current_fps;
        /** \brief internal storage of current time */
        unsigned int current_time;
        /** \brief internal storage of previously recorded time */
        unsigned int old_time;
        /** \brief internal storage of current frame number */
        unsigned int frame;

    };
}

#endif
