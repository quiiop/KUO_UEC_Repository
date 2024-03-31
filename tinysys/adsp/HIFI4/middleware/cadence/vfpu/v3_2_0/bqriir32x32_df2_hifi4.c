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
    NatureDSP Signal Processing Library. IIR part
    Biquad Real Block IIR, 32x32-bit, Direct Form II
    C code optimized for HiFi4
    IntegrIT, 2006-2014
*/


/* Portable data types. */
#include "NatureDSP_types.h"
/* Signal Processing Library API. */
#include "NatureDSP_Signal.h"
/* Common utility and macros declarations. */
#include "common.h"
/* Filter instance structure. */
#include "bqriir32x32_df2_common.h"
/*-------------------------------------------------------------------------
  Biquad Real IIR
  Computes a IIR filter (cascaded IIR direct form I or II using 5 
  coefficients per biquad + gain term). Real input data are stored
  in vector x. The filter output result is stored in vector r. The filter 
  calculates N output samples using SOS and G matrices.
  NOTES:
  1. Biquad coefficients may be derived from standard SOS and G matrices 
  generated by MATLAB. However, typically biquad stages have big peaks 
  in their step response which may cause undesirable overflows at the 
  intermediate outputs. To avoid that the additional scale factors 
  coef_g[M] may be applied. These per-section scale factors may require 
  some tuning to find a compromise between quantization noise and possible 
  overflows. Output of the last section is directed to an additional 
  multiplier, with the gain factor being a power of two, either negative 
  or non-negative. It is specified through the gain parameter of filter
  initialization function.

  Precision: 
  32x16 32-bit data, 16-bit coefficients, 32-bit intermediate stage outputs
  32x32 32-bit data, 32-bit coefficients, 32-bit intermediate stage outputs 
  f     floating point (DF I, DF II and DF IIt)

  Input:
  N             length of input sample block
  M             number of biquad sections
  coef_sos[M*5] filter coefficients stored in blocks of 5 numbers: 
                b0 b1 b2 a1 a2. 
                For fixed-point funcions, fixed point format of filter 
                coefficients is Q1.14 for 32x16, or Q1.30 for 32x16 and 
                32x32 
  coef_g[M]     scale factor for each section, Q15 (for fixed-point 
                functions only). 
  gain          total gain shift amount applied to output signal of the
                last section, -48..15
  x[N]          input samples, Q31 or floating point 
  Output:
  r[N]          output data, Q31 or floating point 

  Restriction:
  x,r,coef_g,coef_sos  must not overlap
  x,r                  must be aligned on 8-byte boundary 
  N                    must be a multiple of 2
-------------------------------------------------------------------------*/
/* Reserve memory for alignment. */
#define ALIGNED_SIZE( size, align ) ( (size_t)(size) + (align) - 1 )

/* Align address on a specified boundary. */
#define ALIGNED_ADDR( addr, align ) (void*)( ( (uintptr_t)(addr) + ( (align) - 1 ) ) & ~( (align) - 1 ) )

#define sz_i16  sizeof(int16_t)
#define sz_i32  sizeof(int32_t)

/* Allocation routine for iir filters. Returns: size of memory in bytes to be allocated */
size_t bqriir32x32_df2_alloc(int M )
{
  NASSERT( M > 0 );
  return ( ALIGNED_SIZE( sizeof(bqriir32x32_df2_t), 4 )
           + // 4 state elements for each of M DFII sections
           ALIGNED_SIZE( 4*M*sz_i32, 8 )
           + // 1 gain + 5 SOS coefficients for each of M sections
           ALIGNED_SIZE( 8*M*sz_i32, 8 ));

} // bqriir32x32_df2_alloc()

/* Initialization routine for iir filters. Returns: handle to the object */
bqriir32x32_df2_handle_t bqriir32x32_df2_init( void * objmem, int M, 
                                               const int32_t * restrict coef_sos,
                                               const int16_t * restrict coef_g,
                                               int16_t         gain )
{
  bqriir32x32_df2_ptr_t bqriir;

  ae_int32x2 * restrict sectState;
  int32_t * restrict sectCoef_gsos;
  void *    ptr;

  int m;

  NASSERT( objmem &&  M >= 0 && coef_sos && coef_g );
  // Partition the memory block
  ptr = objmem;
  bqriir       = (bqriir32x32_df2_ptr_t)ALIGNED_ADDR( ptr, 4 );
  ptr          = bqriir + 1;
  sectState    = (ae_int32x2 *)ALIGNED_ADDR( ptr, 8 );
  ptr          = sectState + 2*M;
  sectCoef_gsos = (int32_t *)ALIGNED_ADDR( ptr, 8 );
  ptr          = sectCoef_gsos + 6*M;

  NASSERT( (int8_t*)ptr - (int8_t*)objmem <= (int)bqriir32x32_df2_alloc(M ) );
  NASSERT( -48 <= gain && gain <= 15 );
  // Initialize the filter instance.
  bqriir->magic    = MAGIC;
  bqriir->M        = M;
  bqriir->gain     = gain;
  bqriir->coef_gsos= sectCoef_gsos;
  bqriir->state    = (int32_t*)sectState;
  // Copy filter coefficients for M sections, zero the state elements.
  __Pragma("loop_count min=1")
  for ( m=0; m<M; m++ )
  {
    sectCoef_gsos[8*m+0] = ((int32_t)coef_g[m])<<15; // gain,Q30
    sectCoef_gsos[8*m+1] = coef_sos[5*m+2]; // b2,Q30
    sectCoef_gsos[8*m+2] = 0;
    sectCoef_gsos[8*m+3] = coef_sos[5*m+0]; // b0,Q30
    sectCoef_gsos[8*m+4] = coef_sos[5*m+2]; // b2,Q30
    sectCoef_gsos[8*m+5] = coef_sos[5*m+1]; // b1,Q30
    sectCoef_gsos[8*m+6] = coef_sos[5*m+4]; // a2,Q30
    sectCoef_gsos[8*m+7] = coef_sos[5*m+3]; // a1,Q30

    AE_S32X2_IP(AE_ZERO32(),sectState,8);
    AE_S32X2_IP(AE_ZERO32(),sectState,8);
  }

  return (bqriir);

} // bqriir32x32_df2_init()
