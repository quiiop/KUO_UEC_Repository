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
  vec_shift,vec_scale  Vector Scaling with Saturation
===========================================================================*/

/*-------------------------------------------------------------------------
  Vector Scaling with Saturation
  These routines make shift with saturation of data values in the vector 
  by given scale factor (degree of 2). 
  Functions vec_scale() make multiplication of Q31 vector to Q31 coefficient 
  which is not a power of 2 forming Q31 result.
  Two versions of routines are available: regular versions (vec_shift32x32, 
  vec_shift16x16, vec_shiftf, vec_scale16x16, vec_scale32x32, vec_scalef, 
  vec_scale_sf) work with arbitrary arguments, faster versions 
  (vec_shift32x32_fast, vec_shift16x16_fast, vec_scale16x16_fast, 
  vec_scale32x32_fast) apply some additional restricitons.

  For floating point:
  Function vec_shiftf makes shift without saturation of data values in the vector
  by given scale factor (degree of 2). 
  Functions vec_scalef() and vec_scale_sf() make multiplication of input vector
  to coefficient which is not a power of 2.
  Two versions of routines are available: 
    without saturation - vec_scalef;
    with saturation - vec_scale_sf; 

Precision:
32x32 32-bit input, 32-bit output
16x16 16-bit input, 16-bit output
f     single precision floating point

  Input:
  x[N]  input data , Q31,Q15 or floating point
  t     shift count. If positive, it shifts left with saturation, if
  negative it shifts right
  s     scale factor, Q31,Q15 or floating point
  N     length of vector
  fmin  minimum output value (only for vec_scale_sf)
  fmax  maximum output value (only for vec_scale_sf)

  Output:
  y[N]  output data, Q31, Q15 or floating point

  Restrictions:
  For regular versions (vec_shift32x32, vec_shift16x16, vec_shiftf, 
  vec_scale16x16, vec_scale32x32, vec_scalef, vec_scale_sf):
  x,y should not overlap
  t   should be in range -31...31 for fixed-point functions and -129...146 
      for floating point

  For vec_scale_sf - fmin<=fmax;

  For faster versions (vec_shift32x32_fast, vec_shift16x16_fast, 
  vec_scale16x16_fast, vec_scale32x32_fast):
  x,y should not overlap
  t should be in range -31...31 
  x,y - aligned on 8-byte boundary
  N   - multiple of 4 
-------------------------------------------------------------------------*/

void vec_scale16x16 (     int16_t * restrict y,
                    const int16_t * restrict x,
                    int16_t s,
                    int N)
{
/* macros for emulation of unaligned loads via selects */
#define FIRST_LOAD(x,xnext,px,offset)          \
{                                              \
    if(offset==0) AE_L16X4_IP(x, px, 8);       \
    if(offset==2)                              \
    {                                          \
        ae_valign x_align;                     \
        x_align = AE_LA64_PP(px);              \
        AE_LA16X4_IP(x, x_align, px);          \
        x=AE_SEL16_4321(x,x);                  \
        px=(ae_int16x4*)(((int16_t*)px)-1);    \
        AE_L16X4_IP(xnext, px, 8);             \
        x=AE_SEL16_6543(x,xnext);              \
    }                                          \
    if(offset==4)                              \
    {                                          \
        ae_valign x_align;                     \
        x_align = AE_LA64_PP(px);              \
        AE_LA16X4_IP(x, x_align, px);          \
        x=AE_SEL16_5432(x,x);                  \
        px=(ae_int16x4*)(((int16_t*)px)-2);    \
        AE_L16X4_IP(xnext, px, 8);             \
        x=AE_SEL16_5432(x,xnext);              \
    }                                          \
    if(offset==6)                              \
    {                                          \
        ae_valign x_align;                     \
        x_align = AE_LA64_PP(px);              \
        AE_LA16X4_IP(x, x_align, px);          \
        x=AE_SEL16_6543(x,x);                  \
        px=(ae_int16x4*)(((int16_t*)px)-3);    \
        AE_L16X4_IP(xnext, px, 8);             \
        x=AE_SEL16_4321(x,xnext);              \
    }                                          \
}

#define NEXT_LOAD(x,xnext,px,offset)          \
{                                             \
    if(offset==0)                             \
    {                                         \
        AE_L16X4_IP(x, px, 8);                \
    }                                         \
    if(offset==2)                             \
    {                                         \
        x=xnext;                              \
        AE_L16X4_IP(xnext, px, 8);            \
        x=AE_SEL16_6543(x,xnext);             \
    }                                         \
    if(offset==4)                             \
    {                                         \
        x=xnext;                              \
        AE_L16X4_IP(xnext, px, 8);            \
        x=AE_SEL16_5432(x,xnext);             \
    }                                         \
    if(offset==6)                             \
    {                                         \
        x=xnext;                              \
        AE_L16X4_IP(xnext, px, 8);            \
        x=AE_SEL16_4321(x,xnext);             \
    }                                         \
}

    int n;
    ae_int16x4  vxh, vyh, x1;
    ae_f16x4    vcf;
    const ae_int16x4 * restrict px = (const ae_int16x4 *)x;
        ae_int16x4 * restrict py = (      ae_int16x4 *)y;
    ae_valign y_align;
    if(N<=0) return;
    y_align = AE_ZALIGN64();
    vcf = AE_MOVDA16(s);

    switch (((uintptr_t)px)&7)
    {
    case 0:
        FIRST_LOAD(vxh,x1,px,0);
        for (n=0; n<N-3; n+=4)
        {
            vyh = AE_MULFP16X4RAS(vxh, vcf);
            AE_SA16X4_IP(vyh, y_align, py);
            NEXT_LOAD(vxh,x1,px,0);
        }
        break;
    case 2:
        FIRST_LOAD(vxh,x1,px,2);
        for (n=0; n<N-3; n+=4)
        {
            vyh = AE_MULFP16X4RAS(vxh, vcf);
            AE_SA16X4_IP(vyh, y_align, py);
            NEXT_LOAD(vxh,x1,px,2);
        }
        break;
    case 4:
        FIRST_LOAD(vxh,x1,px,4);
        for (n=0; n<N-3; n+=4)
        {
            vyh = AE_MULFP16X4RAS(vxh, vcf);
            AE_SA16X4_IP(vyh, y_align, py);
            NEXT_LOAD(vxh,x1,px,4);
        }
        break;
    case 6:
        FIRST_LOAD(vxh,x1,px,6);
        for (n=0; n<N-3; n+=4)
        {
            vyh = AE_MULFP16X4RAS(vxh, vcf);
            AE_SA16X4_IP(vyh, y_align, py);
            NEXT_LOAD(vxh,x1,px,6);
        }
        break;
    }
    vyh = AE_MULFP16X4RAS(vxh, vcf);
    AE_SA64POS_FP(y_align, py);
    N&=3;
    if (N>=1) ((int16_t*)py)[0]=AE_MOVAD16_3(vyh);
    if (N>=2) ((int16_t*)py)[1]=AE_MOVAD16_2(vyh);
    if (N>=3) ((int16_t*)py)[2]=AE_MOVAD16_1(vyh);
}