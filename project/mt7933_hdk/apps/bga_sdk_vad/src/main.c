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
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "sys_init.h"
#if defined(MTK_MINICLI_ENABLE)
#include "cli_def.h"
#endif /* #if defined(MTK_MINICLI_ENABLE) */

#ifdef MTK_UT_ENABLE
#include "ut.h"
#endif /* #ifdef MTK_UT_ENABLE */

#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_sleep_manager.h"
#endif /* #ifdef HAL_SLEEP_MANAGER_ENABLED */

#ifdef HAL_WDT_MODULE_ENABLED
#include "hal_wdt.h"
#endif /* #ifdef HAL_WDT_MODULE_ENABLED */
#include "common.h"
#include "mt7933_pos.h"
#include "hal_nvic.h"
#include "hal_efuse_get.h"

#ifdef MTK_MT7933_CONSYS_WIFI_ENABLE
#include "gl_init.h"
#endif /* #ifdef MTK_MT7933_CONSYS_WIFI_ENABLE */

#ifdef MTK_MT7933_BT_ENABLE
#include "bt_driver.h"
#endif /* #ifdef MTK_MT7933_BT_ENABLE */

#ifdef MTK_SSUSB_GADGET_ENABLE
#include "ssusb_gadget_export.h"
#endif /* #ifdef MTK_SSUSB_GADGET_ENABLE */

#ifdef MTK_SSUSB_HOST_ENABLE
#include "ssusb_host_export.h"
#endif /* #ifdef MTK_SSUSB_HOST_ENABLE */

#ifdef MTK_BT_ENABLE
//#include "bt_init.h"
//#include "hal_psram.h"
#endif /* #ifdef MTK_BT_ENABLE */

#ifdef MTK_TFM_ENABLE
#include "tfm_ns_interface_iotsdk_init.h"
#endif /* #ifdef MTK_TFM_ENABLE */

#ifdef HAL_GCPU_MODULE_ENABLED
#include "hal_gcpu_internal.h"
#endif /* #ifdef HAL_GCPU_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "bsp_gpio_ept_config.h"
#endif /* #ifdef HAL_GPIO_MODULE_ENABLED */

#ifdef MTK_HIFI4DSP_ENABLE
#include "mtk_hifixdsp_common.h"
#endif /* #ifdef MTK_HIFI4DSP_ENABLE */

/* WiFi auto connection. */
#include "wifi_api.h"
#ifdef MTK_NVDM_ENABLE
#include "nvdm.h"
#endif /* #ifdef MTK_NVDM_ENABLE */
#include "ping.h"
#include "wifi_netif.h"

/* Task priorities. */

#ifdef MTK_UT_ENABLE
#define utTask_PRIORITY (configMAX_PRIORITIES - 1)
#endif /* #ifdef MTK_UT_ENABLE */

#ifdef MTK_MT7933_CONSYS_ENABLE
SemaphoreHandle_t gConnsysCalLock = NULL;
SemaphoreHandle_t gConnsysRadioOnLock = NULL;
#endif /* #ifdef MTK_MT7933_CONSYS_ENABLE */
#ifdef HAL_WDT_MODULE_ENABLED
void wdt_timeout_handle(hal_wdt_reset_status_t wdt_reset_status)
{
    printf("%s: status:%u\n", __FUNCTION__, (unsigned int)wdt_reset_status);
    /* assert 0 to trigger exception hanling flow */
    configASSERT(0);
}

static void wdt_init(void)
{
    hal_wdt_config_t wdt_init;
#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_WDT_RESET_TRACE)
    /**
     * Dump SWLA trace after watch dog reset, if system hang.
     **/
    wdt_init.mode = HAL_WDT_MODE_RESET;
#else /* #if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_WDT_RESET_TRACE) */
    /**
     * WDT interrupt to trigger exception flow, if system hang.
     **/
    wdt_init.mode = HAL_WDT_MODE_INTERRUPT;
#endif /* #if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_WDT_RESET_TRACE) */
    wdt_init.seconds = 60;
    hal_wdt_init(&wdt_init);
    hal_wdt_register_callback(wdt_timeout_handle);
#ifdef MTK_SYSTEM_HANG_CHECK_ENABLE
    hal_wdt_enable(HAL_WDT_ENABLE_MAGIC);
#else /* #ifdef MTK_SYSTEM_HANG_CHECK_ENABLE */
    hal_wdt_disable(HAL_WDT_DISABLE_MAGIC); //Disable WDT when MTK_SYSTEM_HANG_CHECK_ENABLE = n
#endif /* #ifdef MTK_SYSTEM_HANG_CHECK_ENABLE */
}
#endif /* #ifdef HAL_WDT_MODULE_ENABLED */


/* for idle task feed wdt (DO NOT enter sleep mode)*/
void vApplicationIdleHook(void)
{
#ifdef HAL_WDT_MODULE_ENABLED
    hal_wdt_feed(HAL_WDT_FEED_MAGIC);
#endif /* #ifdef HAL_WDT_MODULE_ENABLED */
}

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
__attribute__((weak))
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
    *ppxTimerTaskTCBBuffer = (StaticTask_t *) pvPortMalloc(sizeof(StaticTask_t));
    if (*ppxTimerTaskTCBBuffer != NULL) {
        *ppxTimerTaskStackBuffer = (StackType_t *) pvPortMalloc((((size_t) * pulTimerTaskStackSize) * sizeof(StackType_t)));
    }
}
/*-----------------------------------------------------------*/
__attribute__((weak))
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    *ppxIdleTaskTCBBuffer = (StaticTask_t *) pvPortMalloc(sizeof(StaticTask_t));
    if (*ppxIdleTaskTCBBuffer != NULL) {
        *ppxIdleTaskStackBuffer = (StackType_t *) pvPortMalloc((((size_t) * pulIdleTaskStackSize) * sizeof(StackType_t)));
    }
}

#endif /* #if( configSUPPORT_STATIC_ALLOCATION == 1 ) */

/*******************************************************************************
 * WiFi autoConnection
 ******************************************************************************/
uint8_t wifi_init_done_handle = 0;

bool iot_IsIpReady(struct netif *netif)
{
    return ip_addr_isany_val(netif->ip_addr) ? 0 : 1;
}

int32_t wifi_init_done_handler_test(wifi_event_t event,
                                    uint8_t *payload,
                                    uint32_t length)
{
    wifi_init_done_handle = 1;
    LOG_I(common, "WiFi Init Done: port = %d", payload[6]);

    return 0;
}

#ifdef MTK_AIA_ENABLE
#include "event_groups.h"
#include "filogic_led.h"
extern EventGroupHandle_t aia_eg;
extern void vApplicationIPNetworkEventHook( bool eNetworkEvent );
int isAiaDisconnected = 0;
extern volatile int aia_va_record_flag;
extern volatile int aia_upload_done;
int32_t wifi_aia_disconnection_handler(wifi_event_t event,
                                    uint8_t *payload,
                                    uint32_t length)
{
    LOG_I(common, "[AIA]: wifi disconnect!!");
    xEventGroupSetBits( aia_eg, ( 0x1 << 1 ) );
    isAiaDisconnected = 1;
    aia_va_record_flag = 0;
    aia_upload_done = 1;
    vApplicationIPNetworkEventHook(false);
    return 0;
}

int32_t wifi_aia_connection_handler(wifi_event_t event,
                                    uint8_t *payload,
                                    uint32_t length)
{
    LOG_I(common, "[AIA]: wifi connect!!");
    vApplicationIPNetworkEventHook(true);
    filogic_led_status_color(FILOGIC_LED_R);
    filogic_led_status_toggle(1);
    return 0;
}
#endif
static bool g_wifi_init_ready = false; 

static void user_wifi_init_callback(void) { g_wifi_init_ready = true; }

static void user_wifi_init_qurey_status(void){
    while(g_wifi_init_ready == false) {
        printf("[KUO] waiting wifi init ...\n");
        vTaskDelay(20);
    }
}

void wifi_auto_init_task(void *para)
{

    struct wifi_cfg wifi_config = {0};
    if (0 != wifi_config_init(&wifi_config)) {
        LOG_E(common, "wifi config init fail");
    }
    /*  load setting NVDM setting
        //FW need known the target ssid and BGchannel table(1 channel), to do STA fast link scan before WIFI_EVENT_IOT_INIT_COMPLETE.
        uint8_t test_opmode = WIFI_MODE_STA_ONLY;
        char *  test_ssid = "TEST";
        char *  password_AP = "QAZWSXEDC";
        //char *  test_bg_ch_table = "6,1,0|";  //first_channel=6, number_of_channel=1, scan_mode=0
        wifi_config.opmode = test_opmode;
        wifi_config.sta_ssid_len = strlen(test_ssid);
        wifi_config.sta_wpa_psk_len = strlen(password_AP);

        memcpy(wifi_config.sta_ssid, test_ssid, wifi_config.sta_ssid_len);
        memcpy(wifi_config.sta_wpa_psk, password_AP, wifi_config.sta_wpa_psk_len);

    */

    wifi_config_t config = {0};
    wifi_config_ext_t config_ext = {0};
    memset(&config, 0, sizeof(config));
    memset(&config_ext, 0, sizeof(config_ext));

    config.opmode = wifi_config.opmode;

    kalMemCopy(config.sta_config.ssid, wifi_config.sta_ssid,
               WIFI_MAX_LENGTH_OF_SSID);
    config.sta_config.ssid_length = wifi_config.sta_ssid_len;
    config.sta_config.bssid_present = 0;
    config.sta_config.channel = wifi_config.sta_channel;
    kalMemCopy(config.sta_config.password, wifi_config.sta_wpa_psk,
               WIFI_LENGTH_PASSPHRASE);
    config.sta_config.password_length = wifi_config.sta_wpa_psk_len;
    if (wifi_config.sta_default_key_id == 255)
        config_ext.sta_wep_key_index_present = 0;
    else
        config_ext.sta_wep_key_index_present = 1;
    config_ext.sta_wep_key_index = wifi_config.sta_default_key_id;

    kalMemCopy(config.ap_config.ssid, wifi_config.ap_ssid,
               WIFI_MAX_LENGTH_OF_SSID);
    config.ap_config.ssid_length = wifi_config.ap_ssid_len;
    kalMemCopy(config.ap_config.password, wifi_config.ap_wpa_psk,
               WIFI_LENGTH_PASSPHRASE);
    config.ap_config.password_length = wifi_config.ap_wpa_psk_len;
    config.ap_config.auth_mode =
        (wifi_auth_mode_t)wifi_config.ap_auth_mode;
    config.ap_config.encrypt_type =
        (wifi_encrypt_type_t)wifi_config.ap_encryp_type;
    config_ext.ap_wep_key_index_present = 1;
    config_ext.ap_wep_key_index = wifi_config.ap_default_key_id;
    config_ext.ap_dtim_interval_present = 1;
    config_ext.ap_dtim_interval = wifi_config.ap_dtim_interval;

    config_ext.sta_auto_connect_present = 1;
    config_ext.sta_auto_connect = 1;

    wifi_init(&config, &config_ext);
    wifi_connection_register_event_handler(WIFI_EVENT_IOT_INIT_COMPLETE, (wifi_event_handler_t)wifi_init_done_handler_test);
#ifdef MTK_AIA_ENABLE
    wifi_connection_register_event_handler(WIFI_EVENT_IOT_IPV4_ADDR_READY, (wifi_event_handler_t)wifi_aia_connection_handler);
    wifi_connection_register_event_handler(WIFI_EVENT_IOT_DISCONNECTED, (wifi_event_handler_t)wifi_aia_disconnection_handler);
#endif
    wifi_connection_scan_init(g_ap_list, MTK_SCAN_LIST_SIZE);

#ifdef AUTO_CONNECT_WIFI
    user_wifi_init_qurey_status();
    /*Call APIs to connect only after Wi-Fi is initialized. open mode*/
    // uint8_t SSID = "UECAP";
    // uint8_t PASSWORD = "50897282";
    wifi_config_set_opmode(WIFI_MODE_STA_ONLY);
    wifi_config_set_ssid(WIFI_PORT_STA, (uint8_t *)"UECAP", kalStrLen("UECAP"));
    wifi_config_set_security_mode(WIFI_PORT_STA, 
                                    WIFI_AUTH_MODE_WPA2_PSK,
                                    WIFI_ENCRYPT_TYPE_AES_ENABLED);
    wifi_config_set_wpa_psk_key(WIFI_PORT_STA, (uint8_t *)"50897282", kalStrLen("50897282"));
    wifi_config_reload_setting(); //reload setting, then auto scanning to connect to AP
    printf("[KUO] wifi reload over\n");
#endif

    struct netif *sta_if = netif_find("st1");
    while (sta_if != NULL) {
        if ((pdTRUE == lwip_net_ready()) && (iot_IsIpReady(sta_if))) {
            /*ping_request(3, "8.8.8.8", PING_IP_ADDR_V4, 64, NULL);*/
            break;
        }
    }

    vTaskDelete(NULL);
}

int wifi_task_create(void)
{
    if (xTaskCreate(wifi_auto_init_task,
                    wifi_auto_init_TASK_NAME,
                    wifi_auto_init_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                    NULL,
                    wifi_auto_init_TASK_PRIO,
                    NULL) != pdPASS) {
        LOG_E(common, "xTaskCreate fail");
        return -1;
    }

    return 0;
}

/*[KUO] auto_connect_wifi*/
static void auto_connect_wifi(void *para)
{
    printf("[KUO] auto_connect_wifi\n");
#ifdef AUTO_WIFI_CONNECT 
    /*初始化wifi*/
    // wifi_auto_init_task(NULL);
#endif
}

static int auto_connect_wifi_task_create(void)
{
    printf("[KUO] auto_connect_wifi_task_create\n");

    if (xTaskCreate(auto_connect_wifi,
                    wifi_auto_init_TASK_NAME,
                    wifi_auto_init_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                    NULL,
                    wifi_auto_init_TASK_PRIO,
                    NULL) != pdPASS) {
        LOG_E(common, "xTaskCreate fail");
        return -1;
    }

    return 0;
}

static void small_test(void)
{
    while (1){
        printf("hello small test\n");
        vTaskDelay(10000/portTICK_RATE_MS); // 10s
    }
}

static int small_test_task_create(void)
{
    printf("[KUO] small_test_task_create\n");
    if (xTaskCreate(wifi_auto_init_task,
                    small_test_TASK_NAME,
                    small_test_TASK_STACKSIZE/ sizeof(portSTACK_TYPE),
                    NULL,
                    small_test_TASK_PRIO,
                    NULL) != pdPASS) {
        LOG_E(common, "xTaskCreate fail");
        return -1;
    }
    return 0;
}

#ifdef MTK_MT7933_AUDIO_DRIVER_ENABLE
void audio_init_task(void *pvParameters)
{
    printf("AUDIO DRIVER INIT\n");
    extern void audio_init(void);
    audio_init();
    vTaskDelete(NULL);
}
int audio_init_task_create(void)
{
    if (xTaskCreate(audio_init_task,
                    audio_init_TASK_NAME,
                    audio_init_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                    NULL,
                    audio_init_TASK_PRIO,
                    NULL) != pdPASS) {
        LOG_E(common, "xTaskCreate fail");
        return -1;
    }

    return 0;
}
#endif /* #ifdef MTK_MT7933_AUDIO_DRIVER_ENABLE */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
#ifdef MTK_IOT_SDK_DEMO_AS_LIB
__attribute__((weak))
int main(void)
{
}

int mtk_main(void)
#else /* #ifdef MTK_IOT_SDK_DEMO_AS_LIB */
int main(void)
#endif /* #ifdef MTK_IOT_SDK_DEMO_AS_LIB */
{
#ifndef MTK_IOT_SDK_DEMO_AS_LIB
    /* Do system initialization, eg: hardware, nvdm, logging and random seed. */
    system_init();
#endif /* #ifndef MTK_IOT_SDK_DEMO_AS_LIB */

#ifdef HAL_GPIO_MODULE_ENABLED
    bsp_ept_gpio_setting_init();
#endif /* #ifdef HAL_GPIO_MODULE_ENABLED */

#if defined(MTK_MINICLI_ENABLE)
    /* Initialize cli task to enable user input cli command from uart port.*/
    cli_def_create();
    cli_task_create();
#endif /* #if defined(MTK_MINICLI_ENABLE) */

    /* Call this function to indicate the system initialize done. */
    //SysInitStatus_Set();
    
#ifdef HAL_WDT_MODULE_ENABLED
    wdt_init();
#endif /* #ifdef HAL_WDT_MODULE_ENABLED */
    printf("Hello Mediatek!!\r\n\r\n");

    if (HAL_EFUSE_PKG_MODE_WBBGA == hal_efuse_get_pkg_mode()) {
#ifdef MTK_SSUSB_HOST_ENABLE
        /* Disable usb, use the cli command to init usb function */
        //mtk_usb_host_init(0);
#endif /* #ifdef MTK_SSUSB_HOST_ENABLE */

#ifdef MTK_SSUSB_GADGET_ENABLE
        /* Disable usb, use the cli command to init usb function */
        //serial_usb_init();
#endif /* #ifdef MTK_SSUSB_GADGET_ENABLE */
    }

#ifdef MTK_TFM_ENABLE
    tfm_ns_interface_iotsdk_init();
#endif /* #ifdef MTK_TFM_ENABLE */

#ifdef MTK_MT7933_CONSYS_ENABLE
    gConnsysCalLock = xSemaphoreCreateMutex();
    gConnsysRadioOnLock = xSemaphoreCreateMutex();
#if defined(BRINGUP_WIFI_ENABLE) || defined(BRINGUP_BT_ENABLE)
    mt7933_conninfra_init();
#ifdef MTK_BT_ENABLE
    //bt_driver_init();
#endif /* #ifdef MTK_BT_ENABLE */
#endif /* #if defined(BRINGUP_WIFI_ENABLE) || defined(BRINGUP_BT_ENABLE) */
#ifdef MTK_MT7933_CONSYS_WIFI_ENABLE
    /* mask out connsys on by default beofre ES for build sanity check */
    /* wifi_init_task(); */
#endif /* #ifdef MTK_MT7933_CONSYS_WIFI_ENABLE */
#endif /* #ifdef MTK_MT7933_CONSYS_ENABLE */

#ifdef HAL_GCPU_MODULE_ENABLED
    gcpu_init();
#endif /* #ifdef HAL_GCPU_MODULE_ENABLED */

    //#ifdef MTK_UT_ENABLE
    //    if (xTaskCreate((TaskFunction_t)ut_main, "utTask", 1024, NULL, utTask_PRIORITY, NULL) != pdPASS)
    //    {
    //        printf("Task creation failed!.\r\n");
    //        while (1);
    //    }
    //#endif

#ifdef MTK_HIFI4DSP_ENABLE
    extern void adsp_ipi_init(void);
    adsp_ipi_init();
#endif /* #ifdef MTK_HIFI4DSP_ENABLE */

#ifdef MTK_MT7933_AUDIO_DRIVER_ENABLE
    /*printf("AUDIO DRIVER INIT\n");
    extern void audio_init(void);
    audio_init();*/
    audio_init_task_create();
#endif /* #ifdef MTK_MT7933_AUDIO_DRIVER_ENABLE */

#ifdef MTK_HIFI4DSP_ENABLE
    /*
    * remove adsp_init into async_load_hifixdsp_bin_and_run.
    * Because adsp starts to work only when audio need it.
    */
    //adsp_init();
#endif /* #ifdef MTK_HIFI4DSP_ENABLE */

#ifdef MTK_BT_ENABLE
    extern void bt_app_common_init(void);
    bt_app_common_init();
#endif /* #ifdef MTK_BT_ENABLE */

#ifdef Just_small_test
    printf("[KUO] Small Test start !!\n");
    small_test_task_create();
#endif

    /*[KUO] auto_wifi_connect*/
    printf("[KUO] register call back func, if wifi init complete, trigger call back func\n");
    wifi_connection_register_event_handler(WIFI_EVENT_IOT_INIT_COMPLETE, user_wifi_init_callback);
#ifdef USE_AUTO_CONNECT_WIFI_TASK
    printf("[KUO] auto connect wifi task create !!\n");
    auto_connect_wifi_task_create();
#else
    printf("[KUO] wifi task create !!\n");
    // wifi_task_create();
#endif
    

    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for (;;);
}


