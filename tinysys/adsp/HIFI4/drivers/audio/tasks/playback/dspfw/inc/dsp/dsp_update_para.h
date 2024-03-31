/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2019. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */


#ifndef _DSP_UPDATEPARA_H_
#define _DSP_UPDATEPARA_H_


#include "audio_types.h"
#include "dsp_sdk.h"



////////////////////////////////////////////////////////////////////////////////
// CONSTANT DEFINITIONS ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef BOOL (*UPDATE_PARA_ENTRY)(VOID* FuncMemPtr, VOID* dataBeginPtr, U32 dataLength);

typedef enum
{
    DSP_UPDATE_DRC_GAIN         = 0,
    DSP_UPDATE_PEQ_FILTER,
    DSP_UPDATE_JOINT_CHANNEL,

    DSP_UPDATE_MAX_NUM,
} DSP_UPDATE_TYPE_t;

typedef struct DSP_UPDATE_PARA_s
{
    DSP_UPDATE_TYPE_t type;
    U32 sequence;
    VOID* transform;
    U32 dataLength;
    U32 dataBegin;
} DSP_UPDATE_PARA, *DSP_UPDATE_PARA_PTR;



////////////////////////////////////////////////////////////////////////////////
// External Variables //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
extern UPDATE_PARA_ENTRY DSP_UpdateParaEntryTable[DSP_UPDATE_MAX_NUM];
extern stream_feature_type_t  DSP_UpdateCheckFeatureTypeTable[DSP_UPDATE_MAX_NUM];





////////////////////////////////////////////////////////////////////////////////
// Macro ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// DSPMEM FUNCTION DECLARATIONS /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
extern VOID DSP_UpdateStreamingPara(DSP_UPDATE_PARA_PTR UpdateParaPtr);



#endif /* _DSP_UPDATEPARA_H_ */

