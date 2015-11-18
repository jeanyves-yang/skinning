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

#ifndef TRIANGLE_INDEX_HPP
#define TRIANGLE_INDEX_HPP

#include <ostream>

namespace cpe
{

/** The 3 index of a triangle (u0,u1,u2) */
class triangle_index
{
public:

    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //

    /** Empty constructor */
    triangle_index();
    /** Direct constructor */
    triangle_index(int u0,int u1,int u2);

    // ********************************************* //
    //  Get/set
    // ********************************************* //

    /** Get u0 index */
    int u0() const;
    /** Get u1 index */
    int u1() const;
    /** Get u2 index */
    int u2() const;

    /** Get/set u0 index */
    int& u0();
    /** Get/set u1 index */
    int& u1();
    /** Get/set u2 index */
    int& u2();

    /** Access to the k_th entry (k in [0,2]) */
    int operator[](int index) const;
    /** Access to the k_th entry (k in [0,2]) */
    int& operator[](int index) ;
    /** Access to the k_th entry (k in [0,2]) */
    int operator()(int index) const;
    /** Access to the k_th entry (k in [0,2]) */
    int& operator()(int index) ;

    /** Fast pointer access
        \warning unprotected access */
    const int *pointer() const;

    // ********************************************* //
    //  For-range compatibility
    // ********************************************* //

    /** Returns 3 */
    static constexpr int size();

    /** STL compatible first element */
    int* begin();
    /** STL compatible end element */
    int* end();
    /** STL compatible first element */
    const int* begin() const;
    /** STL compatible end element */
    const int* end() const;
    /** STL compatible first element */
    const int* cbegin() const;
    /** STL compatible end element */
    const int* cend() const;

private:

    // ********************************************* //
    //  Internal parameters
    // ********************************************* //

    /** u0 index */
    int u0_data;
    /** u1 index */
    int u1_data;
    /** u2 index */
    int u2_data;
};

std::ostream& operator<<(std::ostream& stream,triangle_index const& tri);

}

#endif
