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

/*
  NatureDSP Signal Processing Library. FIR part
    Real data circular convolution, floating point
    C code optimized for HiFi4
  IntegrIT, 2006-2015
*/


/* Portable data types. */
#include "NatureDSP_types.h"
/* Signal Processing Library API. */
#include "NatureDSP_Signal.h"
/* Common utility and macros declarations. */
#include "common.h"
#if !(XCHAL_HAVE_HIFI4_VFPU)
DISCARD_FUN(void,fir_convolf,(     float32_t * restrict r,
                const float32_t * restrict x,
                const float32_t * restrict y,
                int N, int M ))
#else

/*-------------------------------------------------------------------------
  Circular Convolution
  Performs circular convolution between vectors x (of length N) and y (of 
  length M)  resulting in vector r of length N.

  Precision: 
  32x16    32x16-bit data, 32-bit outputs
  32x32    32x32-bit data, 32-bit outputs
  32x32ep  the same as above but using 72-bit accumulator for intermediate 
           computations
  f         floating point

  Input:
  x[N]          input data (Q31 or floating point)
  y[M]          input data (Q31,Q15 or floating point)
  N             length of x
  M             length of y
  Output:
  r[N]          output data,Q31 or floating point

  Restriction:
  x,y,r should not overlap
  x,y,r - aligned on an 8-bytes boundary
  N,M   - multiples of 4 and >0
-------------------------------------------------------------------------*/
void fir_convolf(     float32_t * restrict r,
                const float32_t * restrict x,
                const float32_t * restrict y,
                int N, int M )
{
    //
    // Circular convolution algorithm:
    //
    //   r[n] = sum( x[mod(n-m,N)]*y[m] )
    //        m=0..M-1
    //
    //   where n = 0..N-1
    //
    xtfloatx2 Y01, Y23,
              X32, X21, X10, X0_1, X_12, X_23, X_34;
    xtfloatx2 R0, R1, R2, R3,
              r0, r1, r2, r3,
              R01, R23;
    const xtfloatx2 * restrict pX;
    const xtfloatx2 * restrict pY;
          xtfloatx2 * restrict pR;
    int n, m;

    NASSERT(r);
    NASSERT(x);
    NASSERT(y);
    NASSERT_ALIGN(r,8);
    NASSERT_ALIGN(x,8);
    NASSERT_ALIGN(y,8);
    NASSERT(M>0 && M%4==0);
    NASSERT(N>0 && N%4==0);

    pR = (xtfloatx2 *)r;
    /* set circular buffer boundaries */
    WUR_AE_CBEGIN0((uintptr_t)(x));
    WUR_AE_CEND0  ((uintptr_t)(x+N));
    __Pragma("loop_count min=1");
    for ( n = 0; n < N; n += 4 )
    {
        pX = (const xtfloatx2 *)(x+n+2);
        pY = (const xtfloatx2 *)(y);

        R0=R1=R2=R3=(xtfloatx2)(0.0f);
        r0=r1=r2=r3=(xtfloatx2)(0.0f);
        /* preload data from x */
        XT_LSX2RIC(X32, pX);
        XT_LSX2RIC(X10, pX);
        X21 = XT_SEL32_LH_SX2(X32, X10);

        __Pragma("loop_count min=1");
        for (m = 0; m < (M>>2); m++)
        {
            /* load data from x */
            XT_LSX2RIC(X_12, pX);
            XT_LSX2RIC(X_34, pX);
            X0_1 = XT_SEL32_LH_SX2(X10, X_12);
            X_23 = XT_SEL32_LH_SX2(X_12, X_34);
            /* load data from y */
            XT_LSX2IP(Y01, pY, 2*sizeof(float32_t));
            XT_LSX2IP(Y23, pY, 2*sizeof(float32_t));
            /* compute convolution of 4 values */
            XT_MADD_SX2(R3, X32, Y01);
            XT_MADD_SX2(R2, X21, Y01);
            XT_MADD_SX2(R1, X10, Y01);
            XT_MADD_SX2(R0, X0_1,Y01);
            
            XT_MADD_SX2(r3, X10, Y23);
            XT_MADD_SX2(r2, X0_1,Y23);
            XT_MADD_SX2(r1, X_12,Y23);
            XT_MADD_SX2(r0, X_23,Y23);
            /* shift input line for the next iteration */
            X32 = X_12;
            X21 = X_23;
            X10 = X_34;
        }
        R0 = R0 + r0;
        R1 = R1 + r1;
        R2 = R2 + r2;
        R3 = R3 + r3;
        r0 = XT_SEL32_HL_SX2(R0, R1);
        r1 = XT_SEL32_LH_SX2(R0, R1);
        r2 = XT_SEL32_HL_SX2(R2, R3);
        r3 = XT_SEL32_LH_SX2(R2, R3);
        R01 = r0 + r1;
        R23 = r2 + r3;
        /* Save computed samples */
        XT_SSX2IP(R01, pR, 2*sizeof(float32_t));
        XT_SSX2IP(R23, pR, 2*sizeof(float32_t));
    }
} // fir_convolf()
#endif
