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
  http://www.atnf.csiro.au/~mcalabre/index.html
  $Id: wcsunits.h,v 4.7 2011/02/07 07:03:42 cal103 Exp $
*=============================================================================
*
* WCSLIB 4.7 - C routines that implement the FITS World Coordinate System
* (WCS) standard.  Refer to
*
*   "Representations of world coordinates in FITS",
*   Greisen, E.W., & Calabretta, M.R. 2002, A&A, 395, 1061 (Paper I)
*
* The Flexible Image Transport System (FITS), a data format widely used in
* astronomy for data interchange and archive, is described in
*
*   "Definition of The Flexible Image Transport System (FITS)",
*   Hanisch, R.J., Farris, A., Greisen, E.W., et al. 2001, A&A, 376, 359
*
* which formalizes NOST 100-2.0, a document produced by the NASA/Science
* Office of Standards and Technology, see http://fits.gsfc.nasa.gov.
*
* Refer to the README file provided with WCSLIB for an overview of the
* library.
*
*
* Summary of the wcsunits routines
* --------------------------------
* Routines in this suite deal with units specifications and conversions:
*
*   - wcsunits(): given two unit specifications, derive the conversion from
*     one to the other.
*
*   - wcsutrn(): translates certain commonly used but non-standard unit
*     strings.  It is intended to be called before wcsulex() which only
*     handles standard FITS units specifications.
*
*   - wcsulex(): parses a standard FITS units specification of arbitrary
*     complexity, deriving the conversion to canonical units.
*
*
* wcsunits() - FITS units specification conversion
* ------------------------------------------------
* wcsunits() derives the conversion from one system of units to another.
*
* Given:
*   have      const char []
*                       FITS units specification to convert from (null-
*                       terminated), with or without surrounding square
*                       brackets (for inline specifications); text following
*                       the closing bracket is ignored.
*
*   want      const char []
*                       FITS units specification to convert to (null-
*                       terminated), with or without surrounding square
*                       brackets (for inline specifications); text following
*                       the closing bracket is ignored.
*
* Returned:
*   scale,
*   offset,
*   power     double*   Convert units using
*
=                         pow(scale*value + offset, power);

*                       Normally offset is zero except for log() or ln()
*                       conversions, e.g. "log(MHz)" to "ln(Hz)".  Likewise,
*                       power is normally unity except for exp() conversions,
*                       e.g. "exp(ms)" to "exp(/Hz)".  Thus conversions
*                       ordinarily consist of
*
=                         value *= scale;
*
* Function return value:
*             int       Status return value:
*                          0: Success.
*                        1-9: Status return from wcsulex().
*                         10: Non-conformant unit specifications.
*                         11: Non-conformant functions.
*
*                       scale is zeroed on return if an error occurs.
*
*
* wcsutrn() - Translation of non-standard unit specifications
* -----------------------------------------------------------
* wcsutrn() translates certain commonly used but non-standard unit strings,
* e.g. "DEG", "MHZ", "KELVIN", that are not recognized by wcsulex(), refer to
* the notes below for a full list.  Compounds are also recognized, e.g.
* "JY/BEAM" and "KM/SEC/SEC".  Extraneous embedded blanks are removed.
*
* Given:
*   ctrl      int       Although "S" is commonly used to represent seconds,
*                       its translation to "s" is potentially unsafe since the
*                       standard recognizes "S" formally as Siemens, however
*                       rarely that may be used.  The same applies to "H" for
*                       hours (Henry), and "D" for days (Debye).  This
*                       bit-flag controls what to do in such cases:
*                         1: Translate "S" to "s".
*                         2: Translate "H" to "h".
*                         4: Translate "D" to "d".
*                       Thus ctrl == 0 doesn't do any unsafe translations,
*                       whereas ctrl == 7 does all of them.
*
* Given and returned:
*   unitstr   char []   Null-terminated character array containing the units
*                       specification to be translated.
*
*                       Inline units specifications in the a FITS header
*                       keycomment are also handled.  If the first non-blank
*                       character in unitstr is '[' then the unit string is
*                       delimited by its matching ']'.  Blanks preceding '['
*                       will be stripped off, but text following the closing
*                       bracket will be preserved without modification.
*
* Function return value:
*             int       Status return value:
*                        -1: No change was made, other than stripping blanks
*                            (not an error).
*                         0: Success.
*                         9: Internal parser error.
*                        12: Potentially unsafe translation, whether applied
*                             or not (see notes).
*
* Notes:
*   Translation of non-standard unit specifications: apart from leading and
*   trailing blanks, a case-sensitive match is required for the aliases listed
*   below, in particular the only recognized aliases with metric prefixes are
*   "KM", "KHZ", "MHZ", and "GHZ".  Potentially unsafe translations of "D",
*   "H", and "S", shown in parentheses, are optional.
*
=     Unit       Recognized aliases
=     ----       -------------------------------------------------------------
=     Angstrom   angstrom
=     arcmin     arcmins, ARCMIN, ARCMINS
=     arcsec     arcsecs, ARCSEC, ARCSECS
=     beam       BEAM
=     byte       Byte
=     d          day, days, (D), DAY, DAYS
=     deg        degree, degrees, DEG, DEGREE, DEGREES
=     GHz        GHZ
=     h          hr, (H), HR
=     Hz         hz, HZ
=     kHz        KHZ
=     Jy         JY
=     K          kelvin, kelvins, Kelvin, Kelvins, KELVIN, KELVINS
=     km         KM
=     m          metre, meter, metres, meters, M, METRE, METER, METRES, METERS
=     min        MIN
=     MHz        MHZ
=     Ohm        ohm
=     Pa         pascal, pascals, Pascal, Pascals, PASCAL, PASCALS
=     pixel      pixels, PIXEL, PIXELS
=     rad        radian, radians, RAD, RADIAN, RADIANS
=     s          sec, second, seconds, (S), SEC, SECOND, SECONDS
=     V          volt, volts, Volt, Volts, VOLT, VOLTS
=     yr         year, years, YR, YEAR, YEARS
*
*   The aliases "angstrom", "ohm", and "Byte" for (Angstrom, Ohm, and byte)
*   are recognized by wcsulex() itself as an unofficial extension of the
*   standard, but they are converted to the standard form here.
*
*
* wcsulex() - FITS units specification parser
* -------------------------------------------
* wcsulex() parses a standard FITS units specification of arbitrary
* complexity, deriving the scale factor required to convert to canonical
* units - basically SI with degrees and "dimensionless" additions such as
* byte, pixel and count.
*
* Given:
*   unitstr   const char []
*                       Null-terminated character array containing the units
*                       specification, with or without surrounding square
*                       brackets (for inline specifications); text following
*                       the closing bracket is ignored.
*
* Returned:
*   func      int*      Special function type, see note 4:
*                         0: None
*                         1: log()  ...base 10
*                         2: ln()   ...base e
*                         3: exp()
*
*   scale     double*   Scale factor for the unit specification; multiply a
*                       value expressed in the given units by this factor to
*                       convert it to canonical units.
*
*   units     double[WCSUNITS_NTYPE]
*                       A units specification is decomposed into powers of 16
*                       fundamental unit types: angle, mass, length, time,
*                       count, pixel, etc.  Preprocessor macro WCSUNITS_NTYPE
*                       is defined to dimension this vector, and others such
*                       WCSUNITS_PLANE_ANGLE, WCSUNITS_LENGTH, etc. to access
*                       its elements.
*
*                       Corresponding character strings, wcsunits_types[] and
*                       wcsunits_units[], are predefined to describe each
*                       quantity and its canonical units.
*
* Function return value:
*             int       Status return value:
*                         0: Success.
*                         1: Invalid numeric multiplier.
*                         2: Dangling binary operator.
*                         3: Invalid symbol in INITIAL context.
*                         4: Function in invalid context.
*                         5: Invalid symbol in EXPON context.
*                         6: Unbalanced bracket.
*                         7: Unbalanced parenthesis.
*                         8: Consecutive binary operators.
*                         9: Internal parser error.
*
*                       scale and units[] are zeroed on return if an error
*                       occurs.
*
* Notes:
*   1: wcsulex() is permissive in accepting whitespace in all contexts in a
*      units specification where it does not create ambiguity (e.g. not
*      between a metric prefix and a basic unit string), including in strings
*      like "log (m ** 2)" which is formally disallowed.
*
*   2: Supported extensions:
*      - "angstrom" (OGIP usage) is allowed in addition to "Angstrom".
*      - "ohm"      (OGIP usage) is allowed in addition to "Ohm".
*      - "Byte"   (common usage) is allowed in addition to "byte".
*
*   3: Table 6 of WCS Paper I lists eleven units for which metric prefixes are
*      allowed.  However, in this implementation only prefixes greater than
*      unity are allowed for "a" (annum), "yr" (year), "pc" (parsec), "bit",
*      and "byte", and only prefixes less than unity are allowed for "mag"
*      (stellar magnitude).
*
*      Metric prefix "P" (peta) is specifically forbidden for "a" (annum) to
*      avoid confusion with "Pa" (Pascal, not peta-annum).  Note that metric
*      prefixes are specifically disallowed for "h" (hour) and "d" (day) so
*      that "ph" (photons) cannot be interpreted as pico-hours, nor "cd"
*      (candela) as centi-days.
*
*   4: Function types log(), ln() and exp() may only occur at the start of the
*      units specification.  The scale and units[] returned for these refers
*      to the string inside the function "argument", e.g. to "MHz" in log(MHz)
*      for which a scale of 1e6 will be returned.
*
*
* Global variable: const char *wcsunits_errmsg[] - Status return messages
* -----------------------------------------------------------------------
* Error messages to match the status value returned from each function.
*
*
* Global variable: const char *wcsunits_types[] - Names of physical quantities
* ----------------------------------------------------------------------------
* Names for physical quantities to match the units vector returned by
* wcsulex():
*   -  0: plane angle
*   -  1: solid angle
*   -  2: charge
*   -  3: mole
*   -  4: temperature
*   -  5: luminous intensity
*   -  6: mass
*   -  7: length
*   -  8: time
*   -  9: beam
*   - 10: bin
*   - 11: bit
*   - 12: count
*   - 13: stellar magnitude
*   - 14: pixel
*   - 15: solar ratio
*   - 16: voxel
*
*
* Global variable: const char *wcsunits_units[] - Names of units
* --------------------------------------------------------------
* Names for the units (SI) to match the units vector returned by wcsulex():
*   -  0: degree
*   -  1: steradian
*   -  2: Coulomb
*   -  3: mole
*   -  4: Kelvin
*   -  5: candela
*   -  6: kilogram
*   -  7: metre
*   -  8: second
*
* The remainder are dimensionless.
*===========================================================================*/

#ifndef WCSLIB_WCSUNITS
#define WCSLIB_WCSUNITS

#include "wcserr.h"

#ifdef __cplusplus
extern "C" {
#endif


extern const char *wcsunits_errmsg[];

enum wcsunits_errmsg_enum {
  UNITSERR_SUCCESS            = 0,
  UNITSERR_BAD_NUM_MULTIPLIER = 1,
  UNITSERR_DANGLING_BINOP     = 2,
  UNITSERR_BAD_INITIAL_SYMBOL = 3,
  UNITSERR_FUNCTION_CONTEXT   = 4,
  UNITSERR_BAD_EXPON_SYMBOL   = 5,
  UNITSERR_UNBAL_BRACKET      = 6,
  UNITSERR_UNBAL_PAREN        = 7,
  UNITSERR_CONSEC_BINOPS      = 8,
  UNITSERR_PARSER_ERROR       = 9,
  UNITSERR_BAD_UNIT_SPEC      = 10,
  UNITSERR_BAD_FUNCS          = 11,
  UNITSERR_UNSAFE_TRANS       = 12
};

extern const char *wcsunits_types[];
extern const char *wcsunits_units[];

#define WCSUNITS_PLANE_ANGLE 0
#define WCSUNITS_SOLID_ANGLE 1
#define WCSUNITS_CHARGE      2
#define WCSUNITS_MOLE        3
#define WCSUNITS_TEMPERATURE 4
#define WCSUNITS_LUMINTEN    5
#define WCSUNITS_MASS        6
#define WCSUNITS_LENGTH      7
#define WCSUNITS_TIME        8
#define WCSUNITS_BEAM        9
#define WCSUNITS_BIN        10
#define WCSUNITS_BIT        11
#define WCSUNITS_COUNT      12
#define WCSUNITS_MAGNITUDE  13
#define WCSUNITS_PIXEL      14
#define WCSUNITS_SOLRATIO   15
#define WCSUNITS_VOXEL      16

#define WCSUNITS_NTYPE      17


/* ERRTODO: Document me */
int wcsunits(const char have[], const char want[], double *scale,
             double *offset, double *power, struct wcserr *err);

/* ERRTODO: Document me */
int wcsutrn(int ctrl, char unitstr[], struct wcserr *err);

/* ERRTODO: Document me  */
int wcsulex(const char unitstr[], int *func, double *scale, double units[],
            struct wcserr *err);

#ifdef __cplusplus
}
#endif

#endif /* WCSLIB_WCSUNITS */
