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
 * Copyright  (C) 2022  MediaTek Inc. All rights reserved.
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


#ifdef MTK_SWLA_ENABLE
#include "swla.h"
#endif /* #ifdef MTK_SWLA_ENABLE */

#include "syslog.h"

/**
 * overrade weak definition in sleep manager
 */
void os_enter_deep_sleep(void *data)
{
#ifdef MTK_SWLA_ENABLE
    SLA_EnterDeepSleep(NULL);
#endif /* #ifdef MTK_SWLA_ENABLE */

#ifdef __SYSLOG_DS_LOG_UT__
    LOG_I(common, "before syslog_enter_deep_sleep");
    syslog_enter_deep_sleep(NULL);
    LOG_I(common, "after syslog_enter_deep_sleep");
#else /* #ifdef __SYSLOG_DS_LOG_UT__ */
    syslog_enter_deep_sleep(NULL);
#endif /* #ifdef __SYSLOG_DS_LOG_UT__ */
}

/**
 * overrade weak definition in sleep manager
 */
void os_exit_deep_sleep(void *data)
{
#ifdef MTK_SWLA_ENABLE
    SLA_ExitDeepSleep(NULL);
#endif /* #ifdef MTK_SWLA_ENABLE */

#ifdef __SYSLOG_DS_LOG_UT__
    LOG_I(common, "before syslog_exit_deep_sleep");
    syslog_exit_deep_sleep(NULL);
    LOG_I(common, "after syslog_exit_deep_sleep");
#else /* #ifdef __SYSLOG_DS_LOG_UT__ */
    syslog_exit_deep_sleep(NULL);
#endif /* #ifdef __SYSLOG_DS_LOG_UT__ */
}

