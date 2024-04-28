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

#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "nvdm.h"
#include "bt_system.h"
#include "hal_trng.h"
#include "project_config.h"
#include <string.h>
#include <stdlib.h>
#include "task_def.h"
#include "bt_callback_manager.h"
#include "bt_init.h"
#include "bt_task.h"
#include "bt_gap.h"
#include "nvdm.h"
#include "hal_sys.h"
#include "hal_cache.h"
#ifdef HAL_EFUSE_MODULE_ENABLED
#include "hal_efuse.h"
#endif /* #ifdef HAL_EFUSE_MODULE_ENABLED */
#ifdef MTK_BLE_DM_SUPPORT
#include "bt_device_manager.h"
#endif /* #ifdef MTK_BLE_DM_SUPPORT */

BT_ALIGNMENT4(
    static char timer_cb_buf[BT_TIMER_BUF_SIZE]//one timer control block is 20 bytes
);
BT_ALIGNMENT4(
    static char le_connection_cb_buf[BT_LE_CONNECTION_BUF_SIZE]
);
BT_ALIGNMENT4(
    static char adv_set_cb_buf[BT_LE_ADV_SET_BUF_SIZE]
);

BT_ALIGNMENT4(
    static char tx_buf[BT_TX_BUF_SIZE]
);

BT_ALIGNMENT4(
    static char rx_buf[BT_RX_BUF_SIZE]
);
#ifdef BT_LE_AUDIO_ENABLE
BT_ALIGNMENT4(
    static char le_cis_conn_cb_buf[BT_LE_CIS_CONN_CTRL_BLK_SIZE]
);
#endif /* #ifdef BT_LE_AUDIO_ENABLE */

bt_bd_addr_t g_local_public_addr = {0};
bt_bd_addr_t g_local_random_addr = {0};
uint8_t g_btstack_is_running = false;
static uint8_t g_bt_boot_init_mode = BT_BOOT_INIT_MODE_NONE;

static void bt_store_address_to_nvdm(bt_bd_addr_t addr, const char *item_name)
{
    nvdm_status_t status;
    int8_t i;
    uint8_t buffer[18] = {0};

    for (i = 0; i < 6; ++i) {
        int icn = 0;
        icn = snprintf((char *)buffer + 2 * i, 3, "%02X", addr[i]);
        if (icn < 0 || icn > 3) {
            LOG_E(common, "[BT]address write to buffer error\n");
            return;
        }
    }
    LOG_I(common, "[BT]address to write:%s len:%d\n", buffer, strlen((char *)buffer));
    status = nvdm_write_data_item("BT", item_name, NVDM_DATA_ITEM_TYPE_STRING, buffer, strlen((char *)buffer));
    if (NVDM_STATUS_OK != status) {
        LOG_E(common, "[BT]Failed to store address.\n");
    } else {
        LOG_I(common, "[BT]Successfully store %s to NVDM [%02X:%02X:%02X:%02X:%02X:%02X]\n", item_name,
              addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
    }
}

static void bt_generate_address(bt_bd_addr_t addr, const char *item_name)
{
    nvdm_status_t status;
    int8_t i;
    uint32_t size = 12;
    uint8_t buffer[18] = {0};
    uint8_t tmp_buf[3] = {0};
    uint32_t random_seed;
#ifndef MTK_TFM_ENABLE
    hal_trng_status_t ret = HAL_TRNG_STATUS_OK;
#else /* #ifndef MTK_TFM_ENABLE */
    int ret;
#endif /* #ifndef MTK_TFM_ENABLE */

    status = nvdm_read_data_item("BT", item_name, buffer, &size);
    if (NVDM_STATUS_OK == status) {
        //LOG_I(common, "[BT]Read from NVDM:%s\n", buffer);
        for (i = 0; i < 6; ++i) {
            tmp_buf[0] = buffer[2 * i];
            tmp_buf[1] = buffer[2 * i + 1];
            addr[i] = (uint8_t)strtoul((char *)tmp_buf, NULL, 16);
        }

        LOG_I(common, "[BT]Read %s from NVDM [%02X:%02X:%02X:%02X:%02X:%02X]\n", item_name,
              addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
    } else {
        LOG_I(common, "[BT]Failed to Read from NVDM:%d.\n", status);
#ifndef MTK_TFM_ENABLE
        ret = hal_trng_init();
        if (HAL_TRNG_STATUS_OK != ret) {
            LOG_E(common, "[BT]HAL trng init FAIL\n");
        }
        for (i = 0; i <= 30; ++i) {
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_E(common, "[BT]HAL generate random addr (%d) FAIL\n", i);
            }
        }

        LOG_I(common, "[BT]HAL generate random addr : 0x%x\n", random_seed);
        addr[0] = random_seed & 0xFF;
        addr[1] = (random_seed >> 8) & 0xFF;
        addr[2] = (random_seed >> 16) & 0xFF;
        addr[3] = (random_seed >> 24) & 0xFF;
        ret = hal_trng_get_generated_random_number(&random_seed);
        if (HAL_TRNG_STATUS_OK != ret) {
            LOG_E(common, "[BT]HAL generate random addr FAIL\n");
        }

        addr[4] = random_seed & 0xFF;
        addr[5] = (random_seed >> 8) & 0xCF;
        hal_trng_deinit();
#else /* #ifndef MTK_TFM_ENABLE */
        for (i = 0; i <= 30; ++i) {
            ret = tfm_generate_random(&random_seed, (unsigned char *)&random_seed, sizeof(random_seed));
            if (0 != ret) {
                LOG_E(common, "[BT]TFM generate random addr (%d) FAIL\n", i);
            }
        }
        LOG_I(common, "[BT]TFM generate random addr : 0x%x\n", random_seed);

        addr[0] = random_seed & 0xFF;
        addr[1] = (random_seed >> 8) & 0xFF;
        addr[2] = (random_seed >> 16) & 0xFF;
        addr[3] = (random_seed >> 24) & 0xFF;
        ret = tfm_generate_random(&random_seed, (unsigned char *)&random_seed, sizeof(random_seed));
        if (0 != ret) {
            LOG_E(common, "[BT]TFM generate random addr FAIL\n");
        }
        addr[4] = random_seed & 0xFF;
        addr[5] = (random_seed >> 8) | 0xC0;
#endif /* #ifndef MTK_TFM_ENABLE */

        /* save address to NVDM */
        bt_store_address_to_nvdm(addr, item_name);
    }
}

static void bt_preread_local_random_address(bt_bd_addr_t addr)
{
    bt_generate_address(addr, "randomaddr");
}

static void bt_preread_local_address(bt_bd_addr_t addr)
{
    bt_bd_addr_t tempaddr = {0};

    //1. Check in efuse first
#ifdef HAL_EFUSE_MODULE_ENABLED
    char efuse_buf[16] = {0};
    bt_bd_addr_t efuse_bt_addr = {0};
    hal_efuse_status_t efuse_ret = HAL_EFUSE_OK;

    efuse_ret = hal_efuse_logical_read(2, 0, (uint32_t *)efuse_buf);
    if (efuse_ret == HAL_EFUSE_OK)
        memcpy(&efuse_bt_addr, &efuse_buf[3], sizeof(bt_bd_addr_t));

    if ((memcmp(&efuse_bt_addr, tempaddr, sizeof(bt_bd_addr_t)) == 0) ||
        (efuse_bt_addr[0] == 0xFF && efuse_bt_addr[1] == 0xFF &&
         efuse_bt_addr[2] == 0xFF && efuse_bt_addr[3] == 0xFF &&
         efuse_bt_addr[4] == 0xFF && efuse_bt_addr[5] == 0xFF)) {
        LOG_I(common, "[BT] efuse bt addr not valid, use auto gen\n");
    } else {
        LOG_I(common, "[BT] efuse bt addr = %02X-%02X-%02X-%02X-%02X-%02X\n",
              efuse_bt_addr[0], efuse_bt_addr[1], efuse_bt_addr[2], efuse_bt_addr[3], efuse_bt_addr[4], efuse_bt_addr[5]);
        //return efuse address and no need save to nvdm
        addr[0] = efuse_bt_addr[5];
        addr[1] = efuse_bt_addr[4];
        addr[2] = efuse_bt_addr[3];
        addr[3] = efuse_bt_addr[2];
        addr[4] = efuse_bt_addr[1];
        addr[5] = efuse_bt_addr[0];
        return;
    }
#endif /* #ifdef HAL_EFUSE_MODULE_ENABLED */

    //2. check in NVDM for previous generated address. If no data in NVDM, do the auto generator.
    if (memcmp(addr, &tempaddr, sizeof(bt_bd_addr_t)) == 0) {
        LOG_I(common, "[BT]Empty bt addr after bt_gap_le_get_local_address()\n");
        bt_generate_address(addr, "address");
    }
}

void bt_mm_init(void)
{
    LOG_I(common, "bt init TX_Buf:%d, RX_Buf:%d\n", BT_TX_BUF_SIZE, BT_RX_BUF_SIZE);

    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_TIMER, timer_cb_buf, BT_TIMER_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION, le_connection_cb_buf,
                                 BT_LE_CONNECTION_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_ADV_SET, adv_set_cb_buf,
                                 BT_LE_ADV_SET_BUF_SIZE);
#ifdef BT_LE_AUDIO_ENABLE
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_CIS_CONNECTION, le_cis_conn_cb_buf, BT_LE_CIS_CONN_CTRL_BLK_SIZE);
#endif /* #ifdef BT_LE_AUDIO_ENABLE */
}

#include "bt_gap_le.h"
#include "bt_gatts.h"
extern bt_gap_le_local_config_req_ind_t *bt_ut_gap_le_get_local_config(void);
extern bt_status_t bt_ut_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind);
extern bt_status_t bt_ut_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);
extern bt_status_t bt_ut_gatts_service_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);
extern bt_status_t bt_ut_gatts_get_authorization_check_result(bt_gatts_authorization_check_req_t *req);
extern bt_gap_le_bonding_info_t *bt_ut_gap_le_get_bonding_info(const bt_addr_t remote_addr);
extern bt_gap_le_local_key_t *bt_ut_gap_le_get_local_key(void);
#ifdef __MTK_BT_MESH_ENABLE__
extern bt_status_t mesh_app_bt_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);
#endif /* #ifdef __MTK_BT_MESH_ENABLE__ */
extern bt_status_t bt_ut_gatts_get_execute_write_result(bt_gatts_execute_write_req_t *req);
extern void bt_gatts_switch_init_mode(uint8_t init_mode);
extern void bt_setting_init(void);
extern void bt_gap_set_local_configuration_name(char *name);


//get bt init mode
bt_boot_mode_t bt_get_init_mode(void)
{
    uint8_t init_mode = BT_BOOT_INIT_MODE_NONE;
    uint32_t size = sizeof(init_mode);
    nvdm_status_t status;

    //return saved mode directly to prevent frequently access flash.
    if (g_bt_boot_init_mode != BT_BOOT_INIT_MODE_NONE)
        return g_bt_boot_init_mode;

    status = nvdm_read_data_item("BT_MODE", "initmode", &init_mode, &size);
    BT_LOGI("APP", "boot init_mode = %d, read status = %d", init_mode, status);
    if ((NVDM_STATUS_OK != status) ||
        (init_mode == BT_BOOT_INIT_MODE_NONE) ||
        (init_mode >= BT_BOOT_INIT_MODE_MAX)) {
#if (defined(MTK_BT_BAS_SERVICE_ENABLE) || defined(MTK_BLE_SMTCN_ENABLE))
        init_mode = BT_BOOT_INIT_MODE_GATTS;
#elif defined(__MTK_BT_MESH_ENABLE__)
        init_mode = BT_BOOT_INIT_MODE_MESH;
#else /* #if (defined(MTK_BT_BAS_SERVICE_ENABLE) || defined(MTK_BLE_SMTCN_ENABLE)) */
        init_mode = BT_BOOT_INIT_MODE_DEFAULT;
#endif /* #if (defined(MTK_BT_BAS_SERVICE_ENABLE) || defined(MTK_BLE_SMTCN_ENABLE)) */
        bt_save_init_mode(init_mode);//if save not sucess, also go on
    } else
        g_bt_boot_init_mode = init_mode;

    return (bt_boot_mode_t)init_mode;
}

//save bt init mode
bool bt_save_init_mode(uint8_t init_mode)
{
    nvdm_status_t result = nvdm_write_data_item("BT_MODE",
                                                "initmode",
                                                NVDM_DATA_ITEM_TYPE_RAW_DATA,
                                                (const uint8_t *)(&init_mode),
                                                sizeof(init_mode));
    BT_LOGI("APP", "bt mode save, init_mode = %d, save_result = %d", init_mode, result);

    g_bt_boot_init_mode = init_mode;

    return (NVDM_STATUS_OK == result) ? true : false;
}

void bt_reboot_system(void)
{
    //reboot
    hal_cache_disable();
    hal_cache_deinit();
    hal_sys_reboot(HAL_SYS_REBOOT_MAGIC, WHOLE_SYSTEM_REBOOT_COMMAND);
    return;
}

void bt_create_task(void)
{
    bt_boot_mode_t bt_mode;

    bt_setting_init();

    g_btstack_is_running = true;
    bt_mm_init();

#ifndef MTK_BLE_DM_SUPPORT
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_local_cofig,
                                          0,
                                          (void *)bt_ut_gap_le_get_local_config);
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_pairing_config,
                                          0,
                                          (void *)bt_ut_gap_le_get_pairing_config);
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_bonding_info,
                                          0,
                                          (void *)bt_ut_gap_le_get_bonding_info);
#endif /* #ifndef MTK_BLE_DM_SUPPORT */
    bt_callback_manager_register_callback(bt_callback_type_gap_le_get_local_key,
                                          0,
                                          (void *)bt_ut_gap_le_get_local_key);
    bt_callback_manager_register_callback(bt_callback_type_gatts_get_authorization_check_result,
                                          0,
                                          (void *)bt_ut_gatts_get_authorization_check_result);
    bt_callback_manager_register_callback(bt_callback_type_gatts_get_execute_write_result,
                                          0,
                                          (void *)bt_ut_gatts_get_execute_write_result);
    bt_callback_manager_register_callback(bt_callback_type_app_event,
                                          (uint32_t)(MODULE_MASK_GAP | MODULE_MASK_GATT | MODULE_MASK_SYSTEM | MODULE_MASK_MM),
                                          (void *)bt_ut_app_event_callback);

    bt_mode = bt_get_init_mode();
    switch (bt_mode) {
#if (defined(MTK_BT_BAS_SERVICE_ENABLE) || defined(MTK_BLE_SMTCN_ENABLE))
        case BT_BOOT_INIT_MODE_GATTS:
            bt_gatts_switch_init_mode(BT_BOOT_INIT_MODE_GATTS);
            bt_callback_manager_register_callback(bt_callback_type_app_event,
                                                  (uint32_t)(MODULE_MASK_GAP | MODULE_MASK_GATT | MODULE_MASK_SYSTEM | MODULE_MASK_MM),
                                                  (void *)bt_ut_gatts_service_event_callback);
            break;
#endif /* #if (defined(MTK_BT_BAS_SERVICE_ENABLE) || defined(MTK_BLE_SMTCN_ENABLE)) */

#ifdef __MTK_BT_MESH_ENABLE__
        case BT_BOOT_INIT_MODE_MESH:
            bt_gatts_switch_init_mode(BT_BOOT_INIT_MODE_MESH);
            bt_callback_manager_register_callback(bt_callback_type_app_event,
                                                  (uint32_t)(MODULE_MASK_GAP | MODULE_MASK_GATT | MODULE_MASK_SYSTEM | MODULE_MASK_MM),
                                                  (void *)mesh_app_bt_event_callback);
            break;
#endif /* #ifdef __MTK_BT_MESH_ENABLE__ */

        default:
            bt_callback_manager_register_callback(bt_callback_type_app_event,
                                                  (uint32_t)(MODULE_MASK_GAP | MODULE_MASK_GATT | MODULE_MASK_SYSTEM | MODULE_MASK_MM),
                                                  (void *)bt_ut_gatts_service_event_callback);
            break;
    }

    /* Local Public Address */
    bt_preread_local_address(g_local_public_addr);
    BT_LOGI("BT", "local_public_addr [%02X:%02X:%02X:%02X:%02X:%02X]", g_local_public_addr[5],
            g_local_public_addr[4], g_local_public_addr[3], g_local_public_addr[2], g_local_public_addr[1], g_local_public_addr[0]);

    /* Local Random Address */
    bt_preread_local_random_address(g_local_random_addr);
    * (((uint8_t *)g_local_random_addr) + 5) |= 0xC0;
    BT_LOGI("BT", "local_random_addr [%02X:%02X:%02X:%02X:%02X:%02X]", g_local_random_addr[5],
            g_local_random_addr[4], g_local_random_addr[3], g_local_random_addr[2], g_local_random_addr[1], g_local_random_addr[0]);
#ifdef MTK_BLE_DM_SUPPORT
    bt_device_manager_store_local_address(&g_local_public_addr);
    bt_device_manager_store_local_random_address(&g_local_random_addr);
#else /* #ifdef MTK_BLE_DM_SUPPORT */
    bt_task_set_random_address((bt_bd_addr_ptr_t)&g_local_random_addr);
#endif /* #ifdef MTK_BLE_DM_SUPPORT */

    //rename BT name by local public address -- HB Duo dev AA-BB -> change AA-BB to addr
    char dev_name[BT_GAP_MAX_DEVICE_NAME_LENGTH];
    int ret = snprintf(dev_name, BT_GAP_MAX_DEVICE_NAME_LENGTH, "HB Duo dev %02x-%02x",
                       g_local_public_addr[1], g_local_public_addr[0]);
    BT_LOGI("BT", "Device Name %s (len %d)", dev_name, ret);
    bt_gap_set_local_configuration_name(dev_name);

    //log_config_print_switch(BT, DEBUG_LOG_OFF);
    //log_config_print_switch(BTMM, DEBUG_LOG_OFF);
    //log_config_print_switch(BTHCI, DEBUG_LOG_OFF);
    //log_config_print_switch(BTL2CAP, DEBUG_LOG_OFF);
    if (pdPASS != xTaskCreate(bt_task, BLUETOOTH_TASK_NAME, BLUETOOTH_TASK_STACKSIZE / sizeof(StackType_t),
                              (void *)g_local_public_addr, BLUETOOTH_TASK_PRIO, NULL)) {
        BT_LOGE("BT", "cannot create bt_task.");
    }
}
