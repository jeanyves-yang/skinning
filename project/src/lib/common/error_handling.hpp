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

#ifndef ERROR_HANDLING_HPP
#define ERROR_HANDLING_HPP

#include "exception_cpe.hpp"

#ifndef NDEBUG
#define ASSERT_CPE(condition,msg) \
    if(!(condition)){ \
        throw cpe::exception_cpe(\
                "ASSERT FAILED: ["+std::string(#condition)+"] with message: "+std::string(msg),EXCEPTION_PARAMETERS_CPE);}
#else
#define ASSERT_CPE(condition,msg)
#endif

#endif
