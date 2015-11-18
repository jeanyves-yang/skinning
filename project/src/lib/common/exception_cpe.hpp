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


#ifndef EXCEPTION_CPE_HPP
#define EXCEPTION_CPE_HPP

#include <iostream>
#include <string>
#include "backtrace.hpp"

#define EXCEPTION_PARAMETERS_CPE __FILE__,__FUNCTION__,__LINE__,cpe::get_backtrace()
#define MACRO_EXCEPTION_PARAMETER __FILE__,__FUNCTION__,__LINE__,cpe::get_backtrace()


/** \brief Namespace for CPE classes */
namespace cpe
{


    /** \brief General exception class */
    class exception_cpe
    {
    public:

        /** \brief empty constructor */
        exception_cpe();
        /** \brief constructor with error information */
        exception_cpe(const std::string& msg,const std::string& file,const std::string& caller,const int& line,const std::string& backtrace_arg);

        /** \brief return error message */
        std::string info() const;

        /** \brief get backtrace */
        std::string info_backtrace() const;

        /** \brief export exception informations */
        std::string report_exception() const;

    private:

        /** \brief error message storage */
        std::string message;
        /** \brief caller name storage */
        std::string caller;
        /** \brief file name storage */
        std::string file;
        /** \brief error line storage */
        std::string line;
        /** \brief backtrace error message */
        std::string backtrace_msg;

    };
}

#endif
