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
*=============================================================================
*
* Summary of the wcserr routines
* -------------------------------
* This header defines utility functions to manage error messages in
* wcslib.
*
* For most functions in wcslib that return a numeric error status
* code, a detailed error message is also set on an associated wcserr
* struct.  For example:
*
*     int status;
*     struct wcsprm wcs;
*     if ((status = wcsini(&wcs))) {
*         // Print the error message to the console
*         printf(wcs.err.msg);
*     }
*
*     
* wcserr struct - Error message handling
* --------------------------------------
* The wcserr struct contains the numeric error code, a textual
* description of the error, and information about the source of the
* error.
* 
*   int status
*     The numeric status code associated with the error.  See the
*     documentation for the function that generated the error for the
*     meaning of these codes -- it differs according to context.
*
*   char msg[WCSERR_MESSAGE_LENGTH]
*     The detailed error message.
*
*   char source_file[80]
*     The name of the source file where the error was thrown.
*
*   int line_no
*     The line number where the error was thrown.
*
*     
* The remainder of the functions defined in this header are for
* internal use.
*
* 
* wcserr_ini() - Default constructor for the wcserr struct
* --------------------------------------------------------
* Initializes the memory in a wcserr struct.  If the struct has
* already been initialized, calling wcserr_ini() is not harmful, but
* will merely clear the error information.
*
* Given and returned:
*   err       struct wcserr*
*                       The error object.
*
*                       
* wcserr_copy() - Copy an error object
* ------------------------------------
* Copies an error object from src to dst.
*
* Returned:
*   dst       struct wcserr*
*                       The destination error object.
*
* Given:
*   src       const struct wcserr*
*                       The source error object.
*
* Function return value:
*             int
*                       The numeric status code of the source error
*                       object.
*
*                       
* wcserr_set() - Fill in the contents of an error object
* ------------------------------------------------------
* Fills in an error object with information about an error.  For
* convenience, consider using the WCSERR_SET macro which will fill in
* the source file and line number information automatically.
*
* Given and returned:
*   err       struct wcserr*
*                       The destination error object.  If err is NULL,
*                       the function will return without setting an
*                       error message.
*
* Given:                       
*   status    int
*                       The numeric status code to set
*
*   source_file    const char *
*                       The name of the source file generating the
*                       error
*
*   line_no   int
*                       The line number in the source file generating
*                       the error
*
*   format    const char *
*                       The format string of the error message.  May contain
*                       printf-style %-formatting codes.
*
*   ...
*                       The remaining variable arguments are applied
*                       (like printf) to the format string to generate
*                       the error message.
*
* Function return value:
*             int       The status return code passed in.
*
*             
* WCSERR_SET() - Macro to fill in the contents of an error object
* ---------------------------------------------------------------
* Fills in an error object with information about an error.  Fills in
* the source file and line number where WCSERR_SET was called
* automatically.
*
* Given/returned:
*   err       struct wcserr*
*                       The destination error object
*
* Given:                       
*   status    int
*                       The numeric status code to set
*
*   format    const char *
*                       The format string of the error message.  May contain
*                       printf-style %-formatting codes.
*
*   ...
*                       The remaining variable arguments are applied
*                       (like printf) to the format string to generate
*                       the error message.
*
* Function return value:
*             int       The status return code passed in.
*     
*===========================================================================*/

#ifndef WCSLIB_WCSERR
#define WCSLIB_WCSERR

#define WCSERR_MESSAGE_LENGTH 160

struct wcserr {
  int  status;                     /* Integral status code for the error */
  char msg[WCSERR_MESSAGE_LENGTH]; /* String message for the error */

  char source_file[80];            /* The source file of the error */
  int  line_no;                    /* The line number where the error occurred */
};

void wcserr_ini(struct wcserr *err);

int wcserr_copy(struct wcserr* dst, const struct wcserr* src);

int wcserr_set(
  struct wcserr *err,
  int status,
  const char *source_file,
  int line_no,
  const char *format,
  ...);

#define WCSERR_SET(err, status, format, ...) \
  wcserr_set((err), (status), __FILE__, __LINE__, (format), ##__VA_ARGS__)

#endif /* WSCLIB_WCSERR */
