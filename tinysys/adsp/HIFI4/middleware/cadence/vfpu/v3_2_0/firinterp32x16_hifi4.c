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
    Interpolating block real FIR filter, 32x16-bit
    C code optimized for HiFi4
  IntegrIT, 2006-2014
*/



/* Portable data types. */
#include "NatureDSP_types.h"
/* Signal Processing Library API. */
#include "NatureDSP_Signal.h"
/* Common utility and macros declarations. */
#include "common.h"

#include "firinterp32x16_common.h"
/*-------------------------------------------------------------------------
  Interpolating Block Real FIR Filter
  Computes a real FIR filter (direct-form) with interpolation using IR stored 
  in vector h. The real data input is stored in vector x. The filter output 
  result is stored in vector y. The filter calculates N*D output samples 
  using M*D coefficients and requires last N+M*D-1 samples on the delay line.
  NOTE:
  user application is not responsible for management of delay lines

  Precision: 
  32x16    32-bit data, 16-bit coefficients, 32-bit outputs
  32x32    32-bit data, 32-bit coefficients, 32-bit outputs
  32x32ep  the same as above but using 72-bit accumulator for intermediate 
           computations
  f        floating point

  Input:
  h[M*D]        filter coefficients; h[0] is to be multiplied with the 
                newest sample,Q31, Q15, floating point
  D             interpolation ratio
  N             length of input sample block
  M             length of subfilter. Total length of filter is M*D
  x[N]          input samples,Q31, floating point
  Output:
  y[N*D]        output samples,Q31, floating point

  Restrictions:
  x,h,y should not overlap
  x,h - aligned on an 8-bytes boundary
  N   - multiple of 8
  M   - multiple of 4
  D should be >1

  PERFORMANCE NOTE:
  for optimum performance follow rules:
  D   - 2, 3 or 4

-------------------------------------------------------------------------*/
/* Instance pointer validation number. */
#define MAGIC     0x228b7d2c

/* Reserve memory for alignment. */
#define ALIGNED_SIZE( size, align ) \
      ( (size_t)(size) + (align) - 1 )

/* Align address on a specified boundary. */
#define ALIGNED_ADDR( addr, align ) \
      (void*)( ( (uintptr_t)(addr) + ( (align) - 1 ) ) & ~( (align) - 1 ) )

#define sz_i16    sizeof(int16_t)
#define sz_i32    sizeof(int32_t)

/* Interpolator instance structure. */
typedef struct tag_firinterp32x16_t
{
  uint32_t        magic;     // Instance pointer validation number
  int             D;         // Interpolation factor
  int             M;         // Number of filter coefficients
  const int16_t * coef;      // Filter coefficients
  int32_t *       delayLine; // Delay line for complex samples
  proc_fxn_t *    procFxn;   // Filter data processing function
  int             delayLen;  // Delay line length, in complex samples
  int             wrIx;      // Index of the oldest sample

} firinterp32x16_t, *firinterp32x16_ptr_t;

/* Allocation routine for interpolator. returns: size of memory in bytes to be allocated */
size_t firinterp32x16_alloc( int D, int M )
{
  int delayLen, coefNum;
  NASSERT( D > 1 &&  M > 0 );

  NASSERT(  !( M & 3 ) );

  delayLen = ( M + 4 )+2;
  coefNum  = ( M + 4 +4)*D;
  return ( ALIGNED_SIZE( sizeof( firinterp32x16_t ), 4 )
           + // Delay line
           ALIGNED_SIZE( delayLen*sz_i32, 8 )
           + // Coefficients
           ALIGNED_SIZE( coefNum*sz_i16, 8 ) ); 

} // firinterp32x16_alloc()

/* Allocation routine for interpolator. Returns: size of memory in bytes to be allocated */
firinterp32x16_handle_t firinterp32x16_init( void * objmem, 
                                             int D, int M, 
                                             const int16_t * restrict h )
{
  int inc;
  firinterp32x16_ptr_t firinterp;
  void *              ptr;
  int32_t *           delLine;
  int                 delLen;
  int16_t *           coef;
  int16_t *           coefB;
  int d, m;
  proc_fxn_t *         procFxn;
  int id=0;
  NASSERT( objmem && D > 1 && M > 0 && h );

  NASSERT(  !( M & 3 ) && IS_ALIGN( h ) );

  delLen = ( M + 4 );

  procFxn = ( D == 2 ? &firinterp32x16_D2_proc :
              D == 3 ? &firinterp32x16_D3_proc :
              D == 4 ? &firinterp32x16_D4_proc :
                       &firinterp32x16_DX_proc );

  //
  // Partition the memory block.
  //
  inc=(D&1)^((M>>2)&1);
  inc=2-2*inc;
  ptr       = objmem;
  firinterp = (firinterp32x16_ptr_t)ALIGNED_ADDR( ptr, 4 );
  ptr       = firinterp + 1;
  delLine   = (int32_t*)ALIGNED_ADDR( ptr, 8 );
  ptr       = delLine + delLen+inc;
  coef      = (int16_t*)ALIGNED_ADDR( ptr, 8 );
  ptr       = coef + M*D;

  NASSERT( (int8_t*)ptr - (int8_t*)objmem <= 
          (int)firinterp32x16_alloc( D, M ) );


  //
  // Break the impulse response into D coefficients banks and copy them in
  // reverted order.
  //
  if (D>3||(D==3&&M>8)||(D==2&&(M>32)))
  {
    id = 4;
  }
  for ( d=0; d<D; d++ )
  {
    coefB = coef + d*(M+4+id);

    // To avoid a 1-sample delay, insert a zero coefficient that will match the
    // oldest sample in the delay line. To keep the filter length a multiple of
    // 4, append 3 zeros after the last coefficient.
    for ( m=0; m<1+id; m++ )
    {
      coefB[m] = 0;
    }

    coefB[0] = coefB[M+1+id] = coefB[M+2+id] = coefB[M+3+id] = 0;

    // Copy bank's coefficients in reverted order.
    for ( m=1; m<M+1; m++ )
    {
      coefB[m+id] = h[D*(M-m)+d];
    }
  }

  //
  // Zero the delay line.
  //

  for ( m=0; m<delLen; m++ )
  {
    delLine[m] = 0;
  }

  //
  // Initialize the interpolator instance.
  //

  firinterp->magic     = MAGIC;
  firinterp->D         = D;
  firinterp->M         = M;
  firinterp->coef      = coef;
  firinterp->procFxn   = procFxn;
  firinterp->delayLine = delLine;
  firinterp->delayLen  = delLen;
  firinterp->wrIx      = 0;

  return (firinterp);  


} // firinterp32x16_init()

/*-------------------------------------------------------------------------
  Interpolating Block Real FIR Filter
  Computes a real FIR filter (direct-form) with interpolation using IR stored 
  in vector h. The real data input is stored in vector x. The filter output 
  result is stored in vector y. The filter calculates N*D output samples 
  using M*D coefficients and requires last N+M*D-1 samples on the delay line.
  NOTE:
  user application is not responsible for management of delay lines

  Precision: 
  32x16    32-bit data, 16-bit coefficients, 32-bit outputs
  32x32    32-bit data, 32-bit coefficients, 32-bit outputs
  32x32ep  the same as above but using 72-bit accumulator for intermediate 
           computations
  f        floating point

  Input:
  h[M*D]        filter coefficients; h[0] is to be multiplied with the 
                newest sample,Q31, Q15, floating point
  D             interpolation ratio
  N             length of input sample block
  M             length of subfilter. Total length of filter is M*D
  x[N]          input samples,Q31, floating point
  Output:
  y[N*D]        output samples,Q31, floating point

  Restrictions:
  x,h,y should not overlap
  x,h - aligned on an 8-bytes boundary
  N   - multiple of 8
  M   - multiple of 4
  D should be >1

  PERFORMANCE NOTE:
  for optimum performance follow rules:
  D   - 2, 3 or 4

-------------------------------------------------------------------------*/
void firinterp32x16_process( firinterp32x16_handle_t _firinterp, 
                             int32_t * restrict      y,
                       const int32_t * restrict      x, int N )
{
  firinterp32x16_ptr_t firinterp = (firinterp32x16_ptr_t)_firinterp;
  if(N<=0) return;
  NASSERT( firinterp && firinterp->magic == MAGIC && y && x );

  NASSERT(N%8==0);
  NASSERT( IS_ALIGN( x ) );
  //
  // Call filter's data processing function. It will store the block of input 
  // samples to the delay line, and compute the filter response. Returns the
  // updated next position pointer into the delay line buffer.
  //

  NASSERT( firinterp->procFxn );

  firinterp->wrIx = (*firinterp->procFxn)( 
                                   y,
                                   firinterp->delayLine,
                                   firinterp->delayLen,
                                   x,
                                   firinterp->coef,
                                   firinterp->wrIx,
                                   firinterp->D,
                                   N,
                                   firinterp->M );

} // firinterp32x16_process()
