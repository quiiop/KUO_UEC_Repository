/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __UT_H__
#define __UT_H__


#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

#include "typedefs.h"
#include "common.h"
#include "hal.h"


/** @brief This enum defines the UT API return status*/
typedef enum {
    UT_STATUS_NOT_SUPPORT       = -99,     /**< UT Code Not Support */
    UT_STATUS_INVALID_PARAMETER = -2,      /**< Invalid parameter */
    UT_STATUS_ERROR = -1,                  /**< UT error */
    UT_STATUS_OK = 0                       /**< UT ok */
} ut_status_t;

void ut_main(void);

#ifdef UT_RTOS_ENABLE
ut_status_t ut_rtos(void);
#endif /* #ifdef UT_RTOS_ENABLE */

#ifdef UT_HAL_ENABLE
ut_status_t ut_hal(void);
#endif /* #ifdef UT_HAL_ENABLE */

#ifdef UT_PLATFORM_ENABLE
ut_status_t ut_platform(void);
#endif /* #ifdef UT_PLATFORM_ENABLE */

#if defined(MTK_MINICLI_ENABLE)
#include "cli.h"
extern cmd_t ut_cli[];

#define UT_CLI_ENTRY { "ut", "ut command", NULL, ut_cli },
#endif /* #if defined(MTK_MINICLI_ENABLE) */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef __UT_H__ */

