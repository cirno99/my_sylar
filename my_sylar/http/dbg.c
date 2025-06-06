/**
 *
 * Copyright (c) 2010, Zed A. Shaw and Mongrel2 Project Contributors.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 * 
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 *     * Neither the name of the Mongrel2 Project, Zed A. Shaw, nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "dbg.h"
//#include "bstring.h"

FILE *LOG_FILE = NULL;

void dbg_set_log(FILE *log_file)
{
    LOG_FILE = log_file;
}


FILE *dbg_get_log()
{
    return LOG_FILE != NULL ? LOG_FILE : stderr;
}

void fprintf_with_timestamp(FILE *log_file, const char *format, ...)
{
  /*
  va_list args;
  time_t now = time(NULL);
  bstring time_stamp = bStrfTime("%a, %d %b %Y %H:%M:%S GMT", gmtime(&now));
  va_start(args, format);
  fprintf(log_file, "%s ", time_stamp->data);
  vfprintf(log_file, format, args);
  bdestroy(time_stamp);
  va_end(args);
  */
}
// [ 57%] Building C object CMakeFiles/my_sylar.dir/http/dbg.c.o
///usr/bin/cc -Dmy_sylar_EXPORTS -I/root/CLionProjects/my_sylar/. -I/root/CLionProjects/my_sylar/./tests  -g -fPIC   -std=gnu11 -o CMakeFiles/my_sylar.dir/http/dbg.c.o   -c /root/CLionProjects/my_sylar/http/dbg.c
