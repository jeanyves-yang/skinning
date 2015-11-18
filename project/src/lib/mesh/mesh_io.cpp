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


#include "mesh_io.hpp"

#include "mesh.hpp"
#include "../common/error_handling.hpp"

#include "format/mesh_io_obj.hpp"
#include "format/mesh_io_off.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <cassert>

#include <map>

namespace cpe
{

mesh load_mesh_file(std::string const& filename)
{
    if(filename.find(".obj")!=std::string::npos || filename.find(".OBJ")!=std::string::npos)
        return load_mesh_file_obj(filename);
    else if(filename.find(".off")!=std::string::npos || filename.find(".OFF")!=std::string::npos)
        return load_mesh_file_off(filename);
    else
        throw cpe::exception_cpe("Unknown extension for mesh file "+filename,EXCEPTION_PARAMETERS_CPE);
}



}
