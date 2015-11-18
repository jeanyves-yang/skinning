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

/**
  The original method of the backtrace extraction comes from https://gist.github.com/fmela/591333
  */

#pragma once


#ifndef BACKTRACE_HPP
#define BACKTRACE_HPP


#define WITH_BACKTRACE


#include <string>

namespace cpe
{
  std::string get_backtrace(int skip=0);
}


#endif
