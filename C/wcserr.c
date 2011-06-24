/*============================================================================

  WCSLIB 4.7 - an implementation of the FITS WCS standard.
  Copyright (C) 1995-2011, Mark Calabretta

  This file is part of WCSLIB.

  WCSLIB is free software: you can redistribute it and/or modify it under the
  terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  WCSLIB is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
  more details.

  You should have received a copy of the GNU Lesser General Public License
  along with WCSLIB.  If not, see <http://www.gnu.org/licenses/>.

  Correspondence concerning WCSLIB may be directed to:
    Internet email: mcalabre@atnf.csiro.au
    Postal address: Dr. Mark Calabretta
                    Australia Telescope National Facility, CSIRO
                    PO Box 76
                    Epping NSW 1710
                    AUSTRALIA

  Author: Mark Calabretta, Australia Telescope National Facility
  Module author: Michael Droettboom
  http://www.atnf.csiro.au/~mcalabre/index.html
  $Id:  $
*===========================================================================*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "wcserr.h"

void wcserr_ini(
  struct wcserr *err)

{
  memset(err, 0, sizeof(struct wcserr));
}

int wcserr_copy(
  struct wcserr* dst,
  struct wcserr* src)

{
  memcpy(dst, src, sizeof(struct wcserr));
  return dst->status;
}

int wcserr_set(
  struct wcserr *err,
  int status,
  const char *source_file,
  int line_no,
  const char *format,
  ...)

{
  va_list argp;

  if (err == 0x0) {
    return status;
  }
  
  err->status = status;

  va_start(argp, format);
  vsnprintf(err->msg, WCSERR_MESSAGE_LENGTH, format, argp);
  va_end(argp);

  strncpy(err->source_file, source_file, 80);
  err->line_no = line_no;

  return status;
}
