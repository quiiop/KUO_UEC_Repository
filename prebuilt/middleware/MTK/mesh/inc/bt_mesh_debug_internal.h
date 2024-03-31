/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifndef __BT_MESH_DEBUG_INTERNAL_H__
#define __BT_MESH_DEBUG_INTERNAL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "bt_mesh_debug.h"

#ifdef MESH_DEBUG
#define bt_mesh_os_layer_assert(...) assert(__VA_ARGS__)
#define ASSERT(...) assert(__VA_ARGS__)
#else
#define bt_mesh_os_layer_assert(...) do {} while (0)
#define ASSERT(...) do {} while (0)
#endif

#define MESH_UNUSED(x) (void)(x)


/*!
     @brief Debug log group bit filter
     @{
 */
typedef enum {
    BT_MESH_DEBUG_LEVEL_ERROR          = 0x08000000,  /**< debug level for error*/
    BT_MESH_DEBUG_LEVEL_WARNING        = 0x18000000,  /**< debug level for warning*/
    BT_MESH_DEBUG_LEVEL_NOTIFICATION   = 0x38000000,  /**< debug level for notification*/
    BT_MESH_DEBUG_LEVEL_INFORMATION    = 0x78000000,  /**< debug level for information*/
    BT_MESH_DEBUG_LEVEL_VERBOSE        = 0xF8000000   /**< debug level for verbose*/
} bt_mesh_debug_level_t;
/*!  @} */

/*!
     @name Debug log direction
     @{
 */
typedef enum {
    bt_mesh_log_dir_tx = 0,                /**< Transmit direction*/
    bt_mesh_log_dir_rx = 1,                /**< Received direction*/
    bt_mesh_log_dir_no = 2,                /**< Non-direction*/
} bt_mesh_log_direction_t;
/*!  @} */

/*!
   @brief compiler time's assert
*/
#define MACRO_ASSERT(condition) ((void)sizeof(char[1 - 2*!(condition)]))

/*!
    @brief centrolized return
*/
#define MESH_ASSIGN_RETURN(x,y,z) do {x=y;goto z; }while(0)


#define AB_ASSERT ASSERT
/*!
    @breif log macro
*/
#define MESH_DEBUG_MSG_DIR_NOHEAD(dir, level, group, ...) \
    do {\
        MESH_DEBUG_MSG_HEAD_NH(dir, level, group, __VA_ARGS__);\
    }while(0)

#define MESH_DEBUG_MSG_DIR_NONEWLINE(dir, level, group, ...) \
    do {\
        MESH_DEBUG_MSG_HEAD_NN(dir, level, group, __VA_ARGS__);\
    }while(0)

#define MESH_DEBUG_MSG_DIR(dir, level, group, ...) \
        do {\
            MESH_DEBUG_MSG_HEAD(dir, level, group, __VA_ARGS__);\
           }while(0)


/***************************************************************************************************************/
/*!
    @brief No direction log
*/
/***************************************************************************************************************/
//level, group generic
#define MESH_DEBUG_MSG(level, group, ...)   MESH_DEBUG_MSG_DIR(2, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_NN(level, group, ...)  MESH_DEBUG_MSG_DIR_NONEWLINE(2, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_NH(level, group, ...)  MESH_DEBUG_MSG_DIR_NOHEAD(2, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_MUST(level, ...)     MESH_DEBUG_MSG(level, BT_MESH_DEBUG_MUST, __VA_ARGS__)
#define MESH_DEBUG_MSG_MUST_ERROR(...)      MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_MUST, __VA_ARGS__)
#define MESH_DEBUG_MSG_MUST_WARNING(...)    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_MUST, __VA_ARGS__)
#define MESH_DEBUG_MSG_MUST_INFO(...)     MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_MUST, __VA_ARGS__)
#define MESH_DEBUG_MSG_MUST_VERBOSE(...)     MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_MUST, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_MUST_INFO(name, len, buf) MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_MUST, name, buf, len);

//config group
#define MESH_DEBUG_MSG_CONFIG_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_WARNING(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_NOTIFY_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_CONFIG_NOTIFY_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_CONFIG_NOTIFY(name, buf, len)\
           MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, name, buf, len)
#define MESH_DEBUG_MSGHEX_CONFIG_VERBOSE(name, buf, len)\
           MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_CONFIG, name, buf, len)

//provision group
#define MESH_DEBUG_MSG_PROV_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROV_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROV_WARNING(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROV_INFO(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROV_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_PROV_NOTIFY(name, buf, len)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, name, buf, len)
#define MESH_DEBUG_MSGHEX_PROV_INFO(name, buf, len)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, name, buf, len)
#define MESH_DEBUG_MSGHEX_PROV_VERBOSE(name, buf, len)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, name, buf, len)

//proxy group
#define MESH_DEBUG_MSG_PROXY_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROXY, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROXY_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROXY, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROXY_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_PROXY, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROXY_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROXY, __VA_ARGS__)
#define MESH_DEBUG_MSG_PROXY_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROXY, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_PROXY_VERBOSE(name, len, buf)\
    do {\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROXY, name, buf, len);\
    }while(0)


//gatt group
#define MESH_DEBUG_MSG_GATT_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_GATT_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_GATT_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_GATT_NOTIFY_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_GATT_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_GATT_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_GATT_VERBOSE(name, len, buf)\
    do {\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, name, buf, len);\
    }while(0)

//bearer group
#define MESH_DEBUG_MSG_BEARER_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER, __VA_ARGS__)
#define MESH_DEBUG_MSG_BEARER_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER, __VA_ARGS__)
#define MESH_DEBUG_MSG_BEARER_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_BEARER, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_BEARER_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER, name, buf, len)

//network group
#define MESH_DEBUG_MSG_NETWORK_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_NETWORK_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_NETWORK_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_NETWORK_NOTIFY(...)\
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_NETWORK_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_NETWORK_VERBOSE(name, buf, len)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, name, buf, len)

//middleware group
#define MESH_DEBUG_MSG_MIDDLEWARE_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)
#define MESH_DEBUG_MSG_MIDDLEWARE_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)
#define MESH_DEBUG_MSG_MIDDLEWARE_NOTIFY_NN(...) \
        MESH_DEBUG_MSG_DIR_NONEWLINE(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)
#define MESH_DEBUG_MSG_MIDDLEWARE_NOTIFY_NH(...) \
            MESH_DEBUG_MSG_DIR_NOHEAD(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)
//model group
#define MESH_DEBUG_MSG_MODEL_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
#define MESH_DEBUG_MSG_MODEL_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
#define MESH_DEBUG_MSG_MODEL_ERROR(...) \
        MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
//transport group
#define MESH_DEBUG_MSG_TRANSPORT_VERBOSE(...) \
    MESH_DEBUG_MSG_HEAD(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TRANSPORT_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TRANSPORT_INFO(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TRANSPORT_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TRANSPORT_WARNING(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TRANSPORT_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, name, buf, len)
#define MESH_DEBUG_MSGHEX_TRANSPORT_NOTIFY(name, len, buf)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_TRANSPORT, name, buf, len)

//friend group
#define MESH_DEBUG_MSG_FRIEND_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_FRIEND_INFO(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_FRIEND_INFO_NN(...) \
    MESH_DEBUG_MSG_NN(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_FRIEND_INFO_NH(...) \
    MESH_DEBUG_MSG_NH(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_FRIEND_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)

//beacon group
#define MESH_DEBUG_MSG_BEACON_NOTIFY(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSG_BEACON_INFO(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSG_BEACON_VERBOSE(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSG_BEACON_ERROR(...) \
    MESH_DEBUG_MSG(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_BEACON_NOTIFY(name, len, buf)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, name, buf, len)
#define MESH_DEBUG_MSGHEX_BEACON_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, name, buf, len)


/***************************************************************************************************************/
/*!
    @brief RX direction log
*/
/***************************************************************************************************************/
//level, group generic form
#define MESH_DEBUG_MSG_RX(level, group, ...)  \
    MESH_DEBUG_MSG_DIR(1, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NN(level, group, ...)  MESH_DEBUG_MSG_DIR_NONEWLINE(1, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NH(level, group, ...)  MESH_DEBUG_MSG_DIR_NOHEAD(1, level, group, __VA_ARGS__)
#define MESH_DEBUG_EVT_SRC_RX(level, group, evt_str, src_addr) \
    MESH_DEBUG_MSG_DIR(1, level, group, "%s (0x%x)", evt_str, src_addr)

//access group
#define MESH_DEBUG_MSG_RX_ACCESS_ERROR(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_ACCESS_NOTIFY(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_ACCESS_INFO(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_ACCESS_VERBOSE(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_RX_ACCESS_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_ACCESS, name, buf, len)
#define MESH_DEBUG_MSGHEX_RX_ACCESS_NOTIFY(name, show_len, buf, len)\
    MESH_DEBUG_MSGHEX_EX(1, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_ACCESS, name, buf, len, show_len)



//model group
#define MESH_DEBUG_MSG_RX_MODEL_VERBOSE(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
#define MESH_DEBUG_EVT_SRC_RX_MODEL_NOTIFY(evt_str, src_addr) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MODEL, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_EVT_SRC_RX_MODEL_INFO(evt_str, src_addr) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_MODEL, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_MSG_TX_MODEL_VERBOSE(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_MODEL, __VA_ARGS__)

//config group
#define MESH_DEBUG_MSG_RX_CONFIG_NOTIFY(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_EVT_SRC_RX_CONFIG_NOTIFY(evt_str, src_addr) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_MSG_RX_CONFIG_ERROR(...) \
            MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_RX_CONFIG_NOTIFY(name, buf, len)\
        do {\
        MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, name, buf, len);\
        }while(0)

//provision group
#define MESH_DEBUG_MSG_RX_PROV_NOTIFY(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_PROV_ERROR(...) \
                MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_PROV_WARNING(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_PROV_INFO(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_INFORMATION,  BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_PROV_VERBOSE(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE,  BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_EVT_SRC_RX_PROV_NOTIFY(evt_str, src_addr) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_EVT_SRC_RX_PROV_INFO(evt_str, src_addr) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_EVT_SRC_RX_PROV_VERBOSE(evt_str, src_addr) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, "%s (0x%x)", evt_str, src_addr)
#define MESH_DEBUG_MSGHEX_RX_PROV_NOTIFY(name, buf, len)\
        do {\
            MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, name, buf, len);\
        }while(0)
#define MESH_DEBUG_MSGHEX_RX_PROV_INFO(name, buf, len)\
        do {\
            MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, name, buf, len);\
        }while(0)
#define MESH_DEBUG_MSGHEX_RX_PROV_VERBOSE(name, buf, len)\
        do {\
            MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, name, buf, len);\
        }while(0)

//bearer group
#define MESH_DEBUG_MSG_RX_GATT_VERBOSE(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)

#define MESH_DEBUG_MSGHEX_RX_GATT_VERBOSE(name, len, buf)\
        do {\
            MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, name, buf, len);\
        }while(0)

//network group
#define MESH_DEBUG_MSG_RX_NETWORK_VERBOSE(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NETWORK_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_RX_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NETWORK_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_RX_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NETWORK_NOTIFY(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_NETWORK_ERROR(...) \
                MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_RX_NETWORK_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, name, buf, len);
#define MESH_DEBUG_MSGHEX_RX_NETWORK_ERROR(name, len, buf)\
    MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_NETWORK, name, buf, len);

//middleware group
#define MESH_DEBUG_MSG_RX_MIDDLEWARE_NOTIFY(...) \
           MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)
//model group
#define MESH_DEBUG_MSG_RX_MODEL_NOTIFY(...) \
           MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
//transport group
#define MESH_DEBUG_MSG_RX_TRANSPORT_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_RX_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_TRANSPORT_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_RX_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_TRANSPORT_VERBOSE(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_TRANSPORT_NOTIFY(...) \
    MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_TRANSPORT_INFO(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_RX_TRANSPORT_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, name, buf, len);

//friend group
#define MESH_DEBUG_MSG_RX_FRIEND_NOTIFY(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_FRIEND_INFO_NN(...) \
        MESH_DEBUG_MSG_RX_NN(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_FRIEND_INFO_NH(...) \
        MESH_DEBUG_MSG_RX_NH(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)
#define MESH_DEBUG_MSG_RX_FRIEND_VERBOSE(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)

//beacon group
#define MESH_DEBUG_MSGHEX_RX_BEACON_NOTIFY(name, len, buf)\
    MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, name, buf, len)
#define MESH_DEBUG_MSG_RX_BEACON_NOTIFY(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_RX_BEACON_VERBOSE(name, len, buf)\
    MESH_DEBUG_MSGHEX(1, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, name, buf, len)
#define MESH_DEBUG_MSG_RX_BEACON_VERBOSE(...) \
        MESH_DEBUG_MSG_RX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, __VA_ARGS__)


/***************************************************************************************************************/
/*!
    @brief TX direction log
*/
/***************************************************************************************************************/
#define MESH_DEBUG_MSG_TX(level, group, ...) \
    MESH_DEBUG_MSG_DIR(0, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_MODEL(level, ...) \
    MESH_DEBUG_MSG_TX(level, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NN(level, group, ...)  MESH_DEBUG_MSG_DIR_NONEWLINE(0, level, group, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NH(level, group, ...)  MESH_DEBUG_MSG_DIR_NOHEAD(0, level, group, __VA_ARGS__)


//config group
#define MESH_DEBUG_MSG_TX_CONFIG_NOTIFY(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_CONFIG_ERROR(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_CONFIG, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_CONFIG_NOTIFY(name, buf, len)\
    MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_CONFIG, name, buf, len)

//provision group
#define MESH_DEBUG_MSG_TX_PROV_NOTIFY(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_PROV_ERROR(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_PROV_WARNING(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_WARNING, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_PROV_INFO(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_PROV_VERBOSE(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_PROV_NOTIFY(name, buf, len)\
    MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_PROVISION, name, buf, len)
#define MESH_DEBUG_MSGHEX_TX_PROV_INFO(name, buf, len)\
    MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_PROVISION, name, buf, len)
#define MESH_DEBUG_MSGHEX_TX_PROV_VERBOSE(name, buf, len)\
    MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_PROVISION, name, buf, len)
//network group
#define MESH_DEBUG_MSG_TX_NETWORK_VERBOSE(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NETWORK_VERBOSE_NN(...) \
    MESH_DEBUG_MSG_TX_NN(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NETWORK_VERBOSE_NH(...) \
    MESH_DEBUG_MSG_TX_NH(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NETWORK_NOTIFY(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_NETWORK_ERROR(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_NETWORK, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_NETWORK_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(2, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_NETWORK, name, buf, len)

//bearar group
#define MESH_DEBUG_MSG_TX_BEARER_VERBOSE(...) \
               MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_BEARER_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER, name, buf, len)
#define MESH_DEBUG_MSGHEX_TX_BEARER_NOTIFY(name, len, buf)\
            MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER, name, buf, len)

//gatt group
#define MESH_DEBUG_MSG_TX_GATT_ERROR(...) \
               MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_GATT_NOITFY(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_GATT_VERBOSE(...) \
               MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_GATT_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEARER_GATT, name, buf, len)

//middleware group
#define MESH_DEBUG_MSG_TX_MIDDLEWARE_NOTIFY(...) \
                               MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MIDDLEWARE, __VA_ARGS__)

//model group
#define MESH_DEBUG_MSG_TX_MODEL_NOTIFY(...) \
                               MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MODEL, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_MODEL_NOTIFY(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_MODEL, name, buf, len)

//access group
#define MESH_DEBUG_MSG_TX_ACCESS_VERBOSE(...) \
    MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_ACCESS_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_ACCESS, name, buf, len)
#define MESH_DEBUG_MSG_TX_ACCESS_NOTIFY(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_ACCESS_ERROR(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_ERROR, BT_MESH_DEBUG_ACCESS, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_ACCESS_NOTIFY(name, show_len, buf, len)\
        MESH_DEBUG_MSGHEX_EX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_ACCESS, name, buf, len, show_len)

//transport group
#define MESH_DEBUG_MSG_TX_TRANSPORT_VERBOSE(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_TRANSPORT_NOTIFY(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSG_TX_TRANSPORT_INFO(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_INFORMATION, BT_MESH_DEBUG_TRANSPORT, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_TRANSPORT_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_TRANSPORT, name,  buf, len)

//friend group
#define MESH_DEBUG_MSG_TX_FRIEND_NOTIFY(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_FRIEND, __VA_ARGS__)

//beacon group
#define MESH_DEBUG_MSGHEX_TX_BEACON_NOTIFY(name, len, buf)\
        MESH_DEBUG_MSGHEX_EX(0, BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, name, buf, len)
#define MESH_DEBUG_MSG_TX_BEACON_NOTIFY(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_NOTIFICATION, BT_MESH_DEBUG_BEACON, __VA_ARGS__)
#define MESH_DEBUG_MSGHEX_TX_BEACON_VERBOSE(name, len, buf)\
        MESH_DEBUG_MSGHEX(0, BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, name,  buf, len)
#define MESH_DEBUG_MSG_TX_BEACON_VERBOSE(...) \
        MESH_DEBUG_MSG_TX(BT_MESH_DEBUG_LEVEL_VERBOSE, BT_MESH_DEBUG_BEACON, __VA_ARGS__)

#define MESH_DEBUG_MSG_HEAD_NN MESH_DEBUG_MSG_HEAD_NH
#define MESH_DEBUG_MSG_HEAD MESH_DEBUG_MSG_HEAD_NH

#ifdef MESH_DEBUG
bool MESH_DEBUG_MSG_HEAD_NH(int dir, bt_mesh_debug_level_t level, bt_mesh_debug_group_t group, char *format, ...);
void MESH_DEBUG_MSGHEX(int dir, bt_mesh_debug_level_t level, bt_mesh_debug_group_t group, char *name, const uint8_t *Buffer, uint16_t Len);
void MESH_DEBUG_MSGHEX_EX(int dir, bt_mesh_debug_level_t level, bt_mesh_debug_group_t group, char *name, const uint8_t *Buffer, uint16_t Len, uint16_t show_len);
#else
#define MESH_DEBUG_MSG_HEAD_NH(...)
#define MESH_DEBUG_HEX(...)
#define MESH_DEBUG_MSGHEX(...)
#define MESH_DEBUG_MSGHEX_EX(...)
#endif


/*!
   @brief compiler time's assert
*/
#define MACRO_ASSERT(condition) ((void)sizeof(char[1 - 2*!(condition)]))

/*!
    @brief centrolized return
*/
#define MESH_ASSIGN_RETURN(x,y,z) do {x=y;goto z; }while(0)

/*!
    @brief A macro to printf debug message in specified color.
*/
#define MESH_DEBUG_PRINTF MESH_LOGI

/*!
    @brief A macro to printf error message in specified color.
*/
#define MESH_ERROR_PRINTF MESH_LOGE

/*!
    @brief A macro to dump value in byte array format.
*/
#define MESH_DEBUG_DUMP_VALUE(module, value) \
    { \
        uint8_t *p = (uint8_t *)&value; \
        MESH_DUMP_HEX_LOGI(module, "%s[%d] :", p, sizeof(value), #value, sizeof(value)); \
    }

/*!
    @brief A macro to dump pdu content.
*/
#define MESH_DEBUG_DUMP_PDU(module, pdu_name, pdu_len, pdu) \
    MESH_DUMP_HEX_LOGI(module, "%s[%d] :", pdu, pdu_len, pdu_name, pdu_len);


/*!
    @brief A macro to printf debug message in specified color.
*/
#define MESH_DEBUG_COLOR_PRINTF(module, type, color) \
    MESH_LOGI(module, "%s", type)

/*!
    @brief A macro to printf error message in specified color.
*/
#define MESH_ERROR_COLOR_PRINTF(module, type, color) \
    MESH_LOGE(module, "[ERROR] %s", type)

#define MESH_DEBUG_EVT_SRC(module, evt_str, color, src_addr) \
	MESH_LOGI(module, "%s (0x%x)", evt_str,src_addr)

#define MESH_DEBUG_EVT(module, evt_str, color) \
    MESH_LOGI(module, "%s", evt_str)

#define MESH_DEBUG_EVT_SIG(module, opcode, color) \
	MESH_LOGI(module, "SigMsg[%04x]", opcode)

#define MESH_DEBUG_EVT_VENDOR(module, companyid, opcode, color) \
	MESH_LOGI(module, "VenrodMsg[%02x:%04x]", opcode, companyid)

#define MESH_DEBUG_EVT_LOG(module, log_str) \
	MESH_LOGI(module, "%s", log_str)

#define ANSI_SGR(x)


#define AB_Log_HexDisplay(num, value, len, no_use) \
    MESH_DUMP_HEX_LOGI(BT_MESH_DEBUG_MODEL, "", value, len);

bool bt_mesh_debug_is_module_enabled(uint32_t level_module);

#endif // __BT_MESH_DEBUG_INTERNAL_H__
