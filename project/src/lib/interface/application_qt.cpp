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


#include "application_qt.hpp"
#include "../common/error_handling.hpp"

#include <iostream>

application_qt::application_qt(int& argc,char *argv[])
    :QApplication(argc,argv)
{}

bool application_qt::notify(QObject * receiver, QEvent * event)
{
    try
    {
        return QApplication::notify(receiver, event);
    }
    catch(std::string& s)
    {
        std::cout<<std::endl;
        std::cout<< "Exception thrown (string):" << s<<std::endl;
    }
    catch(std::exception& e)
    {
        std::cout<<std::endl;
        std::cout<< "Exception thrown (std):" << e.what()<<std::endl;
    }
    catch(cpe::exception_cpe& e)
    {
        std::cout<<std::endl;
        std::cout<<e.report_exception()<<std::endl;
    }

    std::cout<<"Abort program"<<std::endl;
    abort();
    return false;

}
