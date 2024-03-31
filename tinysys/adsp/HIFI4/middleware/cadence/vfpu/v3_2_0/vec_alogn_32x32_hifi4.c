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
#include "alog_table.h"
#include "common.h"

/*===========================================================================
  Vector matematics:
  vec_antilog          Antilogarithm         
===========================================================================*/
/*-------------------------------------------------------------------------
  Antilogarithm
  These routines calculate antilogarithm (base2, natural and base10). 
  Fixed-point functions accept inputs in Q25 and form outputs in Q16.15 
  format and return 0x7FFFFFFF in case of overflow and 0 in case of 
  underflow.

  Precision:
  32x32  32-bit inputs, 32-bit outputs. Accuracy: 4*e-5*y+1LSB
  f      floating point: Accuracy: 2 ULP
  NOTE:
  1.  Floating point functions are compatible with standard ANSI C routines 
      and set errno and exception flags accordingly

  Input:
  x[N]  input data,Q25 or floating point 
  N     length of vectors
  Output:
  y[N]  output data,Q16.15 or floating point  

  Restriction:
  x,y should not overlap

  Scalar versions:
  ----------------
  fixed point functions return result in Q16.15

-------------------------------------------------------------------------*/
void vec_antilogn_32x32 (int32_t * restrict y, const int32_t* restrict x, int N)
{
    int n;
          ae_int32x2 * restrict py = (      ae_int32x2 *)y;
    const ae_int32x2 * restrict px = (const ae_int32x2 *)x;
    ae_int32x2 X,E,Y;
    ae_f32x2 t;
    ae_int64 ah,al;
    ae_valign x_align,y_align;
    x_align = AE_LA64_PP(px);
    y_align = AE_ZALIGN64();

    if (N<=0) return;

    for (n=0; n<(N&~1); n+=2)
    {
        AE_LA32X2_IP(X, x_align, px);
        al=AE_MUL32_LL(1549082005,X);
        ah=AE_MUL32_LH(1549082005,X);
        X=AE_TRUNCI32X2F64S(ah,al,2);
        E=AE_SRAI32(X,25);
        E=AE_SUB32(E,15);
        X=AE_AND32(X,AE_MOVDA32X2(0x1ffffff,0x1ffffff));
        X=AE_SUB32(X,AE_MOVDA32X2(0x2000000,0x2000000));
        X=AE_SLLI32(X,6);

        Y=AE_L32_I((const ae_int32 *)pow2poly,4*0);
        t=AE_L32_I((const ae_int32 *)pow2poly,4*1); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*2); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*3); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*4); AE_MULAFP32X2RAS(t,X,Y); Y=t;

        X = AE_SLAA32S(Y, AE_MOVAD32_H(E));
        Y = AE_SLAA32S(Y, AE_MOVAD32_L(E));
        Y = AE_SEL32_HL(X, Y);

        AE_SA32X2_IP(Y, y_align, py);
    }
    AE_SA64POS_FP(y_align, py);
    if(N&1)
    {
        X=AE_L32_I((const ae_int32*)px, 0);
        al=AE_MUL32_LL(X,1549082005);
        X=AE_TRUNCI32X2F64S(al,al,2);
        E=AE_SRAI32(X,25);
        E=AE_SUB32(E,15);
        X=AE_AND32(X,AE_MOVDA32X2(0x1ffffff,0x1ffffff));
        X=AE_SUB32(X,AE_MOVDA32X2(0x2000000,0x2000000));
        X=AE_SLLI32(X,6);

        Y=AE_L32_I((const ae_int32 *)pow2poly,4*0);
        t=AE_L32_I((const ae_int32 *)pow2poly,4*1); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*2); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*3); AE_MULAFP32X2RAS(t,X,Y); Y=t;
        t=AE_L32_I((const ae_int32 *)pow2poly,4*4); AE_MULAFP32X2RAS(t,X,Y); Y=t;

        Y = AE_SLAA32S(Y, AE_MOVAD32_L(E));

        AE_S32_L_I(Y,(ae_int32*)py,0);
    }
}
