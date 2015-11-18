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


#include "backtrace.hpp"

#ifdef WITH_BACKTRACE

namespace external_backtrace_C{
#include <execinfo.h> // for backtrace
}
#include <dlfcn.h>    // for dladdr
#include <cxxabi.h>   // for __cxa_demangle

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>


/** Method copied from https://gist.github.com/fmela/591333 */
namespace cpe
{
std::string get_backtrace(int skip)
{
    void *callstack[128];
    const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
    char buf[1024];
    int nFrames = external_backtrace_C::backtrace(callstack, nMaxFrames);
    char **symbols = external_backtrace_C::backtrace_symbols(callstack, nFrames);

    std::ostringstream trace_buf;
    for (int i = skip; i < nFrames; i++) {

        Dl_info info;
        if (dladdr(callstack[i], &info) && info.dli_sname) {
            char *demangled = NULL;
            int status = -1;
            if (info.dli_sname[0] == '_')
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
            snprintf(buf, sizeof(buf), "%-3d %*p %s + %zd\n",
                     i, int(2 + sizeof(void*) * 2), callstack[i],
                     status == 0 ? demangled :
                                   info.dli_sname == 0 ? symbols[i] : info.dli_sname,
                     static_cast<char *>(callstack[i]) - static_cast<char *>(info.dli_saddr));
            free(demangled);
        } else {
            snprintf(buf, sizeof(buf), "%-3d %*p %s\n",
                     i, int(2 + sizeof(void*) * 2), callstack[i], symbols[i]);
        }
        trace_buf << buf;
    }
    free(symbols);
    if (nFrames == nMaxFrames)
        trace_buf << "[truncated]\n";
    return trace_buf.str();
}
}

#else
namespace cpe
{
std::string backtrace(int skip) {return "backtrace not implemented";}
}

#endif
