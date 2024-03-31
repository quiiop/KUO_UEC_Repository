/*
 *    Mediatek HiFi 4 Redistribution Version  <0.0.1>
 */

/* ------------------------------------------------------------------------ */
/* Copyright (c) 2016 by Cadence Design Systems, Inc. ALL RIGHTS RESERVED.  */
/* These coded instructions, statements, and computer programs (�Cadence    */
/* Libraries�) are the copyrighted works of Cadence Design Systems Inc.	    */
/* Cadence IP is licensed for use with Cadence processor cores only and     */
/* must not be used for any other processors and platforms. Your use of the */
/* Cadence Libraries is subject to the terms of the license agreement you   */
/* have entered into with Cadence Design Systems, or a sublicense granted   */
/* to you by a direct Cadence licensee.                                     */
/* ------------------------------------------------------------------------ */
/*  IntegrIT, Ltd.   www.integrIT.com, info@integrIT.com                    */
/*                                                                          */
/* DSP Library                                                              */
/*                                                                          */
/* This library contains copyrighted materials, trade secrets and other     */
/* proprietary information of IntegrIT, Ltd. This software is licensed for  */
/* use with Cadence processor cores only and must not be used for any other */
/* processors and platforms. The license to use these sources was given to  */
/* Cadence, Inc. under Terms and Condition of a Software License Agreement  */
/* between Cadence, Inc. and IntegrIT, Ltd.                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015-2016 IntegrIT, Limited.                      */
/*                      All Rights Reserved.                                */
/* ------------------------------------------------------------------------ */
#include "NatureDSP_Signal.h"
#include "common.h"


/*===========================================================================
  Vector matematics:
  vec_power            Power of a Vector
===========================================================================*/

/*-------------------------------------------------------------------------
  Power of a Vector
  This routine computes power of vector with scaling output result by rsh 
  bits. Accumulation is done in 64-bit wide accumulator and output may 
  scaled down with saturation by rsh bits. So, if representation of x 
  input is Qx, result will be represented in Q(2x-rsh) format.
  Two versions of routines are available: regular versions (vec_power32x32, 
  vec_power16x16, vec_powerf) work with arbitrary arguments, faster versions 
  (vec_power32x32_fast, vec_power16x16_fast) apply some restrictions.

  Precision: 
  32x32 32x32-bit data, 64-bit output
  16x16 16x16-bit data, 64-bit output
  f     single precision floating point

  Input:
  x[N]  input data, Q31, Q15 or floating point
  rsh   right shift of result
  N     length of vector

  Returns: Sum of squares of a vector, Q(2x-rsh)

  Restrictions:
  for vec_power32x32(): rsh in range 31...62
  for vec_power16x16(): rsh in range 0...31
  For regular versions (vec_power32x32, vec_power16x16, vec_powerf):
  none

  For faster versions (vec_power32x32_fast, vec_power16x16_fast ):
  x - aligned on 8-byte boundary
  N   - multiple of 4
-------------------------------------------------------------------------*/
int64_t vec_power32x32_fast (const int32_t * restrict x, int rsh, int N)
{
  int n;

  ae_int32x2  vxw;
  ae_int64    vai;
  ae_f64      a0, b0;

  const ae_f32x2 *    restrict  px = (const ae_f32x2 *)   x;
  NASSERT_ALIGN8(x);
  NASSERT((N&3)==0);
  NASSERT(rsh>=31 && rsh<=62);
  if (N<=0) return 0;
  a0 = b0 = AE_ZERO64();
  __Pragma("loop_count min=1")
  for (n=0; n<(N>>2); n++)
  {
    AE_L32X2_IP(vxw, px, 8);
    AE_MULAAFD32RA_HH_LL(a0, vxw, vxw);
    AE_L32X2_IP(vxw, px, 8);
    AE_MULAAFD32RA_HH_LL(b0, vxw, vxw);
  }
  vai = AE_ADD64(a0,b0);
  vai = AE_SLAA64S(vai, 15-rsh);

  return_int64(vai);
}
