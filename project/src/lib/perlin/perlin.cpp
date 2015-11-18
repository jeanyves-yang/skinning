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

#include "perlin.hpp"
#include "../../external/perlin/simplexnoise1234.hpp"

#include "../common/error_handling.hpp"
#include "../3d/vec2.hpp"
#include "../3d/vec3.hpp"
#include "../3d/vec4.hpp"


#include <cmath>

namespace cpe
{

perlin::perlin()
    :octave_data(5),persistency_data(0.3f)
{}
perlin::perlin(int octave_param,float persistency_param)
    :octave_data(octave_param),persistency_data(persistency_param)
{
    ASSERT_CPE(octave_param>0,"Octave should be >0");
    ASSERT_CPE(persistency_param>0,"Persistency should be > 0");
    ASSERT_CPE(persistency_param<1,"Persistency should be < 1");
}

float perlin::operator()(float const p) const
{
    float value=0.0f;
    double frequency=1.0f;
    double persistency=1.0;

    for(int k=0;k<octave_data;k++)
    {
        value += persistency*(0.5f+0.5f*snoise1(p*frequency));
        frequency *= 2.0f;
        persistency *= persistency_data;
    }

    return value;
}

float perlin::operator()(vec2 const& p) const
{
    float value=0.0f;
    double frequency=1.0f;
    double persistency=1.0;

    for(int k=0;k<octave_data;k++)
    {
        value += persistency*(0.5f+0.5f*snoise2(p.x()*frequency,
                                                p.y()*frequency));
        frequency *= 2.0f;
        persistency *= persistency_data;
    }

    return value;
}

float perlin::operator()(vec3 const& p) const
{
    float value=0.0f;
    double frequency=1.0f;
    double persistency=1.0;

    for(int k=0;k<octave_data;k++)
    {
        value += persistency*(0.5f+0.5f*snoise3(p.x()*frequency,
                                                p.y()*frequency,
                                                p.z()*frequency));
        frequency *= 2.0f;
        persistency *= persistency_data;
    }

    return value;
}

float perlin::operator()(vec4 const& p) const
{
    float value=0.0f;
    double frequency=1.0f;
    double persistency=1.0;

    for(int k=0;k<octave_data;k++)
    {
        value += persistency*(0.5f+0.5f*snoise4(p.x()*frequency,
                                                p.y()*frequency,
                                                p.z()*frequency,
                                                p.w()*frequency));
        frequency *= 2.0f;
        persistency *= persistency_data;
    }

    return value;
}


}
