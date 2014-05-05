/*============================================================================

  WCSLIB 4.22 - an implementation of the FITS WCS standard.
  Copyright (C) 1995-2014, Mark Calabretta

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
  along with WCSLIB.  If not, see http://www.gnu.org/licenses.

  Direct correspondence concerning WCSLIB to mark@calabretta.id.au

  Author: Mark Calabretta, Australia Telescope National Facility, CSIRO,
     and: Michael Droetboom, Space Telescope Science Institute
  http://www.atnf.csiro.au/people/Mark.Calabretta
  $Id: twcs.c,v 4.22 2014/04/12 15:03:53 mcalabre Exp $
*=============================================================================
*
* Test wcscompare()
*
*---------------------------------------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <wcslib.h>
#include <wcsconfig_tests.h>


int main()

{
  int status;
  struct wcsprm a;
  struct wcsprm b;
  int equal;

  a.flag = -1;
  b.flag = -1;
  wcsini(1, 2, &a);
  wcsini(1, 2, &b);

  if (wcscompare(0, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (!equal) {
    printf("wcscompare: FAILED: Not equal.\n");
    return 1;
  }

  strncpy(b.dateobs, "2014-01-01T00:00:00", 72);

  if (wcscompare(0, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (equal) {
    printf("wcscompare: FAILED: Equal, unexpected.\n");
    return 1;
  }

  if (wcscompare(WCSCOMPARE_IGNORE_ANCILLARY, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (!equal) {
    printf("wcscompare: FAILED: Ancillary keyword not ignored.\n");
    return 1;
  }

  strncpy(b.dateobs, a.dateobs, 72);
  b.crpix[0] = 12.5;
  b.crpix[1] = 12.5;

  if (wcscompare(0, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (equal) {
    printf("wcscompare: FAILED: Equal, unexpected.\n");
    return 1;
  }

  if (wcscompare(WCSCOMPARE_INTEGER_TRANSLATION, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (equal) {
    printf("wcscompare: FAILED: Non-integral translation treated as equal.\n");
    return 1;
  }

  if (wcscompare(WCSCOMPARE_TRANSLATION, &a, &b, &equal)) {
    printf("wcscompare: FAILED: Null pointer passed.\n");
    return 1;
  }

  if (!equal) {
    printf("wcscompare: FAILED: Translation not ignored.\n");
    return 1;
  }

  printf("wcscompare: PASSED\n");

  wcsfree(&a);
  wcsfree(&b);

  return 0;
}
