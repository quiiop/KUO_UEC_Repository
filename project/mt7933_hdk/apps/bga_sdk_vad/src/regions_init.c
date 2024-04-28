/* Copyright Statement:
 *
 * (C) 2020-2021  MediaTek Inc. All rights reserved.
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


/****************************************************************************
 *
 * HEADER FILES
 *
 ****************************************************************************/


#include "exception_handler.h"
#include "memory_map.h"


/****************************************************************************
 *
 * FORWARD DECLARATIONS
 *
 ****************************************************************************/


#if defined(__GNUC__)

#define COREDUMP_EXTRA_INFO_SIZE    (128)
extern char g_coredump_info[COREDUMP_EXTRA_INFO_SIZE];

#endif /* #if defined(__GNUC__) */


/****************************************************************************
 *
 * GLOBAL VARIABLES
 *
 ****************************************************************************/

#if defined(__GNUC__)

#define REGION(a, b, c, d)   { a, (void *)b, (void *)c, d },

const memory_region_type memory_regions[] = {
    REGION("text",                  TEXT_BASE,                   TEXT_END,         0)
    REGION("sysram_text",           SYSRAM_CODE_START,           SYSRAM_CODE_END,  0)
    REGION("cached_sysram_data",    SYSRAM_DATA_START,           SYSRAM_DATA_END,  1)
    REGION("bss",                   SYSRAM_BSS_START,            SYSRAM_BSS_END,   1)
#ifdef MTK_NON_INIT_HEAP
    REGION("non_init_sysram_bss",   SYSRAM_NON_INIT_BSS_START,   SYSRAM_NON_INIT_BSS_END,   1)
#endif /* #ifdef MTK_NON_INIT_HEAP */
    REGION("noncached_sysram_text", NONCACHED_SYSRAM_CODE_START, NONCACHED_SYSRAM_CODE_END, 1)
    REGION("noncached_sysram_data", NONCACHED_SYSRAM_DATA_START, NONCACHED_SYSRAM_DATA_END, 1)

    REGION("cached_ram_text",       RAM_CODE_START,              RAM_CODE_END,     0)
    REGION("cached_ram_data",       RAM_DATA_START,              RAM_DATA_END,     1)
    REGION("cached_ram_bss",        RAM_BSS_START,               RAM_BSS_END,            1)
#ifdef MTK_NON_INIT_HEAP
    REGION("non_init_ram_bss",      RAM_NON_INIT_BSS_START,      RAM_NON_INIT_BSS_END,   1)
#endif /* #ifdef MTK_NON_INIT_HEAP */
    REGION("noncached_ram_text",    NONCACHED_RAM_CODE_START,    NONCACHED_RAM_CODE_END, 0)
    REGION("noncached_ram_data",    NONCACHED_RAM_DATA_START,    NONCACHED_RAM_DATA_END, 1)
    REGION("noncached_ram_bss",     NONCACHED_RAM_BSS_START,     NONCACHED_RAM_BSS_END,  1)

    REGION("tcm_text",              TCM_CODE_START,              TCM_CODE_END,     0)
    REGION("tcm_data",              TCM_DATA_START,              TCM_DATA_END,     1)
    REGION("tcm_bss",               TCM_BSS_START,               TCM_BSS_END,      1)
    REGION("stack",                 STACK_START,                 STACK_END,        1)
    REGION("scs",                   SCS_BASE,                    SCS_BASE + 0x1000, 1)
    {
        0
    }
};

#endif /* #if defined(__GNUC__) */

#if defined (__CC_ARM)

extern unsigned int Image$$TEXT$$Base[];
extern unsigned int Image$$TEXT$$Limit[];
extern unsigned int Image$$CACHED_RAM_TEXT$$Base[];
extern unsigned int Image$$CACHED_RAM_TEXT$$Limit[];
extern unsigned int Image$$CACHED_DATA$$RW$$Base[];
extern unsigned int Image$$CACHED_DATA$$ZI$$Limit[];
extern unsigned int Image$$NONCACHED_DATA$$Base[];
extern unsigned int Image$$NONCACHED_ZI$$Limit[];
extern unsigned int Image$$CACHED_SYSRAM_TEXT$$Base[];
extern unsigned int Image$$CACHED_SYSRAM_TEXT$$Limit[];
extern unsigned int Image$$CACHED_SYSRAM_DATA$$RW$$Base[];
extern unsigned int Image$$CACHED_SYSRAM_DATA$$ZI$$Limit[];
extern unsigned int Image$$NONCACHED_SYSRAM_DATA$$Base[];
extern unsigned int Image$$NONCACHED_SYSRAM_ZI$$Limit[];
extern unsigned int Image$$TCM$$RO$$Base[];
extern unsigned int Image$$TCM$$ZI$$Limit[];
extern unsigned int Image$$STACK$$ZI$$Base[];
extern unsigned int Image$$STACK$$ZI$$Limit[];

const memory_region_type memory_regions[] = {
    {"text", Image$$TEXT$$Base, Image$$TEXT$$Limit, 0},
    {"cached_ram_text", Image$$CACHED_RAM_TEXT$$Base, Image$$CACHED_RAM_TEXT$$Limit, 1},
    {"cached_ram_data", Image$$CACHED_DATA$$RW$$Base, Image$$CACHED_DATA$$ZI$$Limit, 1},
    {"noncached_ram_data", Image$$NONCACHED_DATA$$Base, Image$$NONCACHED_ZI$$Limit, 1},
    {"sysram_text", Image$$CACHED_SYSRAM_TEXT$$Base, Image$$CACHED_SYSRAM_TEXT$$Limit, 1},
    {"cached_sysram_data", Image$$CACHED_SYSRAM_DATA$$RW$$Base, Image$$CACHED_SYSRAM_DATA$$ZI$$Limit, 1},
    {"noncached_sysram_data", Image$$NONCACHED_SYSRAM_DATA$$Base, Image$$NONCACHED_SYSRAM_ZI$$Limit, 1},
    {"tcm", Image$$TCM$$RO$$Base, Image$$TCM$$ZI$$Limit, 1},
    {"stack", Image$$STACK$$ZI$$Base, Image$$STACK$$ZI$$Limit, 1},
    {"scs", (unsigned int *)SCS_BASE, (unsigned int *)(SCS_BASE + 0x1000), 1},
    {0}
};


#endif /* #if defined (__CC_ARM) */

#if defined(__ICCARM__)

extern unsigned int RAM_BLOCK$$Base[];
extern unsigned int RAM_BLOCK$$Limit[];
extern unsigned int VRAM_BLOCK$$Base[];
extern unsigned int VRAM_BLOCK$$Limit[];

extern unsigned int SYSRAM_BLOCK$$Base[];
extern unsigned int SYSRAM_BLOCK$$Limit[];
extern unsigned int VSYSRAM_BLOCK$$Base[];
extern unsigned int VSYSRAM_BLOCK$$Limit[];
extern unsigned int TCM_BLOCK$$Base[];
extern unsigned int TCM_BLOCK$$Limit[];
extern unsigned int CSTACK$$Base[];
extern unsigned int CSTACK$$Limit[];

const memory_region_type memory_regions[] = {
    {"ram", RAM_BLOCK$$Base, RAM_BLOCK$$Limit, 1},
    {"vram", VRAM_BLOCK$$Base, VRAM_BLOCK$$Limit, 1},
    {"sysram", SYSRAM_BLOCK$$Base, SYSRAM_BLOCK$$Limit, 1},
    {"vsysram", VSYSRAM_BLOCK$$Base, VSYSRAM_BLOCK$$Limit, 1},
    {"tcm", TCM_BLOCK$$Base, CSTACK$$Limit, 1},
    {"stack", CSTACK$$Base, CSTACK$$Limit, 0},
    {"scs", (unsigned int *)SCS_BASE, (unsigned int *)(SCS_BASE + 0x1000), 1},
    {0}
};


#endif /* #if defined(__ICCARM__) */


