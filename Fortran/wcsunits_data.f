*=======================================================================
*
* WCSLIB 4.10 - an implementation of the FITS WCS standard.
* Copyright (C) 1995-2012, Mark Calabretta
*
* This file is part of WCSLIB.
*
* WCSLIB is free software: you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WCSLIB is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with WCSLIB.  If not, see http://www.gnu.org/licenses.
*
* Correspondence concerning WCSLIB may be directed to:
*   Internet email: mcalabre@atnf.csiro.au
*   Postal address: Dr. Mark Calabretta
*                   Australia Telescope National Facility, CSIRO
*                   PO Box 76
*                   Epping NSW 1710
*                   AUSTRALIA
*
* Author: Mark Calabretta, Australia Telescope National Facility
* http://www.atnf.csiro.au/~mcalabre/index.html
* $Id: wcsunits_data.f,v 4.10 2012/02/05 23:41:44 cal103 Exp $
*=======================================================================

      BLOCK DATA WCSUNITS_BLOCK_DATA

      INTEGER   WCSUNITS_NTYPE
      PARAMETER (WCSUNITS_NTYPE = 17)

      CHARACTER WCSUNITS_ERRMSG(0:12)*40,
     :          WCSUNITS_TYPES(WCSUNITS_NTYPE)*18,
     :          WCSUNITS_UNITS(WCSUNITS_NTYPE)*9

      COMMON /WCSUNITS_DATA/ WCSUNITS_ERRMSG, WCSUNITS_TYPES,
     :                       WCSUNITS_UNITS

      DATA WCSUNITS_ERRMSG /
     :  'Success',
     :  'Invalid numeric multiplier',
     :  'Dangling binary operator',
     :  'Invalid symbol in INITIAL context',
     :  'Function in invalid context',
     :  'Invalid symbol in EXPON context',
     :  'Unbalanced bracket',
     :  'Unbalanced parenthesis',
     :  'Consecutive binary operators',
     :  'Internal parser error',
     :  'Non-conformant unit specifications',
     :  'Non-conformant functions',
     :  'Potentially unsafe translation'/

      DATA WCSUNITS_TYPES /
     :  'plane angle', 'solid angle', 'charge', 'mole', 'temperature',
     :  'luminous intensity', 'mass', 'length', 'time', 'beam', 'bin',
     :  'bit', 'count', 'stellar magnitude', 'pixel', 'solar ratio',
     :  'voxel'/

      DATA WCSUNITS_UNITS /
     :  'degree', 'steradian', 'Coulomb', 'mole', 'Kelvin', 'candela',
     :  'kilogram', 'metre', 'second', 8*' '/

      END
