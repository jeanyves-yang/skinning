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

#include "exception_cpe.hpp"
#include <sstream>


namespace cpe
{
    exception_cpe::exception_cpe(){}

    exception_cpe::exception_cpe(const std::string& msg_arg,const std::string& file_arg,const std::string& caller_arg,const int& line_arg,const std::string& backtrace_msg_arg)
        :message(msg_arg),caller(caller_arg),file(file_arg),backtrace_msg(backtrace_msg_arg)
    {
        //convert line (int) to string
        std::ostringstream stream;
        stream<<line_arg;
        line=stream.str();
    }

    std::string exception_cpe::info() const
    {
        return message+" in file ["+file+"] in function ["+caller+"] at line "+line+" \n";
    }


    std::string exception_cpe::info_backtrace() const
    {
        return backtrace_msg;
    }

    std::string exception_cpe::report_exception() const
    {
        std::string msg;
        msg+="Exception CPE thrown:\n";
        msg+="=================== \n";
        msg+=" [Backtrace] \n";
        msg+="=================== \n";
        msg+=info_backtrace()+"\n\n";
        msg+="=================== \n";
        msg+=" [Details] \n";
        msg+="=================== \n";
        msg+=info()+"\n";
        return msg;
    }

}
