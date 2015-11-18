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

#ifndef   	TRACKBALL_HPP
# define   	TRACKBALL_HPP


#include "../3d/quaternion.hpp"

namespace cpe
{

    /// A container class to deal with a trackball, use ArcBall paradigm
    class trackball
    {
    public:

        // ********************************************* //
        // ********************************************* //
        //  CONSTRUCTORS
        // ********************************************* //
        // ********************************************* //

        /** \empty initial constructor */
        trackball();


        //*********************************************//
        //*********************************************//
        // Get quaternion
        //*********************************************//
        //*********************************************//

        /** \brief get the current quaternion */
        quaternion const& quat() const;
        /** \brief get the current quaternion */
        quaternion& quat();

        /** \brief get the quaternion to apply */
        quaternion const& d_quat() const;
        /** \brief get the quaternion to apply */
        quaternion& d_quat();

        //*********************************************//
        //*********************************************//
        // Disc radius
        //*********************************************//
        //*********************************************//

        /** \brief get the disc radius */
        float& radius();
        /** \brief get the disc radius */
        float radius() const;

        //*********************************************//
        //*********************************************//
        // Manipulation
        //*********************************************//
        //*********************************************//

        /** \brief return the distance to disc for the 3D coordinate */
        float project_to_disc(float x,float y) const;

        /** \brief given a set of 2d coords difference, return the corresponding quaternion */
        void set_2d_coords(float x0,float y0,float x1,float y1);

        /** \brief multiply d_q to current_q */
        void apply_rotation();

        /** \brief Set d_q to 0 */
        void no_motion();





    private:

        /** \brief the current quaternion */
        quaternion current_q;
        /** \brief the quaternion to apply */
        quaternion d_q;

        /** \brief internal parameter of the disc radius */
        float disc_radius;

    };

}

#endif
