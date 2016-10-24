/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * from: @(#)fdlibm.h 5.1 93/09/24
 * $NetBSD: math_private.h,v 1.12 2005/07/21 12:55:58 christos Exp $
 */

#ifndef _MATH_PRIVATE_H_
#define _MATH_PRIVATE_H_

/* The original fdlibm code used statements like:
  n0 = ((*(int*)&one)>>29)^1;   * index of high word *
  ix0 = *(n0+(int*)&x);     * high word of x *
  ix1 = *((1-n0)+(int*)&x);   * low word of x *
   to dig two 32 bit words out of the 64 bit IEEE floating point
   value.  That is non-ANSI, and, moreover, the gcc instruction
   scheduler gets it wrong.  We instead use the following macros.
   Unlike the original code, we determine the endianness at compile
   time, not at run time; I don't see much benefit to selecting
   endianness at run time.  */

/* A union which permits us to convert between a double and two 32 bit
   ints.  */

/*
 * The ARM ports are little endian except for the FPA word order which is
 * big endian.
 */

#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || (defined(__arm__) && !defined(__VFP_FP__))

typedef union
{
  double value;
  struct
  {
    unsigned int msw;
    unsigned int lsw;
  } parts;
} ieee_double_shape_type;

#endif

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) && !(defined(__arm__) && !defined(__VFP_FP__))

typedef union
{
  double value;
  struct
  {
    unsigned int lsw;
    unsigned int msw;
  } parts;
} ieee_double_shape_type;

#endif

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)        \
do {                \
  ieee_double_shape_type ew_u;          \
  ew_u.value = (d);           \
  (ix0) = ew_u.parts.msw;         \
  (ix1) = ew_u.parts.lsw;         \
} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)          \
do {                \
  ieee_double_shape_type gh_u;          \
  gh_u.value = (d);           \
  (i) = gh_u.parts.msw;           \
} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)         \
do {                \
  ieee_double_shape_type gl_u;          \
  gl_u.value = (d);           \
  (i) = gl_u.parts.lsw;           \
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)         \
do {                \
  ieee_double_shape_type iw_u;          \
  iw_u.parts.msw = (ix0);         \
  iw_u.parts.lsw = (ix1);         \
  (d) = iw_u.value;           \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)          \
do {                \
  ieee_double_shape_type sh_u;          \
  sh_u.value = (d);           \
  sh_u.parts.msw = (v);           \
  (d) = sh_u.value;           \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)         \
do {                \
  ieee_double_shape_type sl_u;          \
  sl_u.value = (d);           \
  sl_u.parts.lsw = (v);           \
  (d) = sl_u.value;           \
} while (0)

/** Compute the value of the cosine of Arg, measured in radians.
    @param[in]    Arg   The value to compute the cosine of.
    @return   The computed value of the cosine of Arg.
**/
double  cos(double Arg);

/** Compute the value of the sine of Arg.
    @param[in]    Arg   The value to compute the sine of.
    @return   The computed value of the sine of Arg.
**/
double  sin(double Arg);

/** Compute the absolute value of Arg.
    @param[in]    Arg   The value to compute the absolute value of.
    @return   The absolute value of Arg.
**/
double  fabs(double Arg);

/** Compute the largest integer value not greater than Arg.
    @param[in]    Arg   The value to compute the floor of.
    @return   The largest integer value not greater than Arg, expressed as a floating-point number.
**/
double  floor(double);

/* ieee style elementary functions */
extern int    __ieee754_rem_pio2 (double,double*);

/* fdlibm kernel function */
extern double __kernel_sin (double, double, int);
extern double __kernel_cos (double, double);
extern int    __kernel_rem_pio2 (double*,double*,int,int,int,const int*);


/**@{
    C99, Posix, or NetBSD functions that are not part of the C95 specification.
**/
/*
 * Functions callable from C, intended to support IEEE arithmetic.
 */
double  scalbn(double, int);
double  copysign(double, double);

#endif /* _MATH_PRIVATE_H_ */