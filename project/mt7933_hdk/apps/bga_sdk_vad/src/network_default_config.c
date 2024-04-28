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


#include "nvdm.h"
//#include "network_default_config.h"
#include "nvdm_ctrl.h"
#ifdef MTK_MT7933_CONSYS_WIFI_ENABLE
#include "get_profile_string.h"
#include "gl_os.h"
#endif /* #ifdef MTK_MT7933_CONSYS_WIFI_ENABLE */


static const group_data_item_t g_network_data_item_array[] = {
    NVDM_DATA_ITEM("IpAddr",          "192.168.1.1"),
    NVDM_DATA_ITEM("IpNetmask",       "255.255.255.0"),
    NVDM_DATA_ITEM("IpGateway",       "192.168.1.254"),
    NVDM_DATA_ITEM("IpMode",          "dhcp"),
};

/* common config */
static const group_data_item_t g_common_data_item_array[] = {
    NVDM_DATA_ITEM("OpMode",      "1"),
    NVDM_DATA_ITEM("syslog_filters", ""),
};

/* multiple profile STA config */
const group_data_item_t g_sta_default_data_item_array[] = {
    NVDM_DATA_ITEM("MacAddr",        ""),
    NVDM_DATA_ITEM("Ssid",           ""),
    NVDM_DATA_ITEM("SsidLen",        "0"),
    NVDM_DATA_ITEM("Channel",        "0"),
    NVDM_DATA_ITEM("BW",             "0"),
    NVDM_DATA_ITEM("WirelessMode",   "0"),
    NVDM_DATA_ITEM("ListenInterval", "0"),
    NVDM_DATA_ITEM("AuthMode",       "0"),
    NVDM_DATA_ITEM("EncrypType",     "0"),
    NVDM_DATA_ITEM("WpaPsk",         ""),
    NVDM_DATA_ITEM("WpaPskLen",      "0"),
    NVDM_DATA_ITEM("DefaultKeyId",   "0"),
    NVDM_DATA_ITEM("SharedKey",      "0"),
    NVDM_DATA_ITEM("SharedKeyLen",   "0"),
    NVDM_DATA_ITEM("PSMode",         "0"),
};

/* STA config */
static const group_data_item_t g_sta_data_item_array[] = {
    NVDM_DATA_ITEM("MacAddr",        ""),
    NVDM_DATA_ITEM("Ssid",           "MTK_SOFT_AP"),
    NVDM_DATA_ITEM("SsidLen",        "11"),
    NVDM_DATA_ITEM("Channel",        "1"),
    NVDM_DATA_ITEM("BW",             "0"),
    NVDM_DATA_ITEM("WirelessMode",   "9"),
    NVDM_DATA_ITEM("ListenInterval", "1"),
    NVDM_DATA_ITEM("AuthMode",       "0"),
    NVDM_DATA_ITEM("EncrypType",     "1"),
    NVDM_DATA_ITEM("WpaPsk",         "12345678"),
    NVDM_DATA_ITEM("WpaPskLen",      "8"),
    NVDM_DATA_ITEM("DefaultKeyId",   "0"),
    NVDM_DATA_ITEM("SharedKey",      "12345,12345,12345,12345"),
    NVDM_DATA_ITEM("SharedKeyLen",   "5,5,5,5"),
    NVDM_DATA_ITEM("PSMode",         "0"),
};

/* AP config */
static const group_data_item_t g_ap_data_item_array[] = {
    NVDM_DATA_ITEM("MacAddr",       ""),
    NVDM_DATA_ITEM("Ssid",          "MTK_SOFT_AP"),
    NVDM_DATA_ITEM("SsidLen",       "11"),
    NVDM_DATA_ITEM("Channel",       "1"),
    NVDM_DATA_ITEM("BW",            "0"),
    NVDM_DATA_ITEM("WirelessMode",  "9"),
    NVDM_DATA_ITEM("DtimPeriod",    "1"),
    NVDM_DATA_ITEM("AuthMode",      "0"),
    NVDM_DATA_ITEM("EncrypType",    "1"),
    NVDM_DATA_ITEM("WpaPsk",        "12345678"),
    NVDM_DATA_ITEM("WpaPskLen",     "8"),
    NVDM_DATA_ITEM("DefaultKeyId",  "0"),
    NVDM_DATA_ITEM("SharedKey",     "12345,12345,12345,12345"),
    NVDM_DATA_ITEM("SharedKeyLen",  "5,5,5,5"),
    NVDM_DATA_ITEM("NatpTcpEntry",  "32"),
    NVDM_DATA_ITEM("NatpUdpEntry",  "32"),
};

static void network_check_default_value(void)
{
    check_default_value("network",
                        g_network_data_item_array,
                        sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

static void network_reset_to_default(void)
{
    reset_to_default("network",
                     g_network_data_item_array,
                     sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

static void network_show_value(void)
{
    show_group_value("network",
                     g_network_data_item_array,
                     sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

static const group_data_item_t g_hapd_data_item_array[] = {
    NVDM_DATA_ITEM("interface",      "ra0"),
    NVDM_DATA_ITEM("driver",         "gen4m"),
    NVDM_DATA_ITEM("logger_syslog",  "-1"),
    NVDM_DATA_ITEM("logger_syslog_level",  "2"),
    NVDM_DATA_ITEM("logger_stdout",  "-1"),
    NVDM_DATA_ITEM("logger_stdout_level",  "2"),
    NVDM_DATA_ITEM("ssid",           "MT7933_SAP"),
    NVDM_DATA_ITEM("macaddr_acl",    "0"),
    NVDM_DATA_ITEM("hw_mode",        "g"),
    NVDM_DATA_ITEM("channel",        "11"),
    NVDM_DATA_ITEM("beacon_int",     "100"),
    NVDM_DATA_ITEM("dtim_period",    "2"),
    NVDM_DATA_ITEM("max_num_sta",    "2"),
    NVDM_DATA_ITEM("rts_threshold",  "-1"),
    NVDM_DATA_ITEM("fragm_threshold",      "-1"),
    NVDM_DATA_ITEM("auth_algs",      "3"),
    NVDM_DATA_ITEM("ignore_broadcast_ssid", "0"),
    NVDM_DATA_ITEM("MacAddr",       ""),
    NVDM_DATA_ITEM("IpAddr",          "10.10.10.1"),
    NVDM_DATA_ITEM("IpNetmask",       "255.255.255.0"),
    NVDM_DATA_ITEM("IpGateway",       "10.10.10.254"),
    NVDM_DATA_ITEM("IpDns1",          "10.10.10.1"),
    NVDM_DATA_ITEM("IpDns2",          "0.0.0.0"),
};

static void hapd_check_default_value(void)
{
    check_default_value("hapd",
                        g_hapd_data_item_array,
                        sizeof(g_hapd_data_item_array) / sizeof(g_hapd_data_item_array[0]));
}

static void hapd_reset_to_default(void)
{
    reset_to_default("hapd",
                     g_hapd_data_item_array,
                     sizeof(g_hapd_data_item_array) / sizeof(g_hapd_data_item_array[0]));
}

static void hapd_show_value(void)
{
    show_group_value("hapd",
                     g_hapd_data_item_array,
                     sizeof(g_hapd_data_item_array) / sizeof(g_hapd_data_item_array[0]));
}

static void common_check_default_value(void)
{
    check_default_value("common",
                        g_common_data_item_array,
                        sizeof(g_common_data_item_array) / sizeof(g_common_data_item_array[0]));
}

static void common_reset_to_default(void)
{
    reset_to_default("common",
                     g_common_data_item_array,
                     sizeof(g_common_data_item_array) / sizeof(g_common_data_item_array[0]));
}

static void common_show_value(void)
{
    show_group_value("common",
                     g_common_data_item_array,
                     sizeof(g_common_data_item_array) / sizeof(g_common_data_item_array[0]));
}

static void sta_check_default_value(void)
{
    check_default_value("STA",
                        g_sta_data_item_array,
                        sizeof(g_sta_data_item_array) / sizeof(g_sta_data_item_array[0]));
}

static void sta_reset_to_default(void)
{
    reset_to_default("STA",
                     g_sta_data_item_array,
                     sizeof(g_sta_data_item_array) / sizeof(g_sta_data_item_array[0]));
}

static void sta_show_value(void)
{
    show_group_value("STA",
                     g_sta_data_item_array,
                     sizeof(g_sta_data_item_array) / sizeof(g_sta_data_item_array[0]));
}

static void sta2_check_default_value(void)
{
    check_default_value("STA2",
                        g_sta_default_data_item_array,
                        sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void sta2_reset_to_default(void)
{
    reset_to_default("STA2",
                     g_sta_default_data_item_array,
                     sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void sta2_show_value(void)
{
    show_group_value("STA2",
                     g_sta_default_data_item_array,
                     sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void sta3_check_default_value(void)
{
    check_default_value("STA3",
                        g_sta_default_data_item_array,
                        sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void sta3_reset_to_default(void)
{
    reset_to_default("STA3",
                     g_sta_default_data_item_array,
                     sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void sta3_show_value(void)
{
    show_group_value("STA3",
                     g_sta_default_data_item_array,
                     sizeof(g_sta_default_data_item_array) / sizeof(g_sta_default_data_item_array[0]));
}

static void ap_check_default_value(void)
{
    check_default_value("AP",
                        g_ap_data_item_array,
                        sizeof(g_ap_data_item_array) / sizeof(g_ap_data_item_array[0]));
}

static void ap_reset_to_default(void)
{
    reset_to_default("AP",
                     g_ap_data_item_array,
                     sizeof(g_ap_data_item_array) / sizeof(g_ap_data_item_array[0]));
}

static void ap_show_value(void)
{
    show_group_value("AP",
                     g_ap_data_item_array,
                     sizeof(g_ap_data_item_array) / sizeof(g_ap_data_item_array[0]));
}

const user_data_item_operate_t network_data_item_operate_array[] = {
    {
        "network",
        network_check_default_value,
        network_reset_to_default,
        network_show_value,
    },
    {
        "hapd",
        hapd_check_default_value,
        hapd_reset_to_default,
        hapd_show_value,
    },
    {
        "common",
        common_check_default_value,
        common_reset_to_default,
        common_show_value,
    },
    {
        "STA",
        sta_check_default_value,
        sta_reset_to_default,
        sta_show_value,
    },
    {
        "STA2",
        sta2_check_default_value,
        sta2_reset_to_default,
        sta2_show_value,
    },
    {
        "STA3",
        sta3_check_default_value,
        sta3_reset_to_default,
        sta3_show_value,
    },
    {
        "AP",
        ap_check_default_value,
        ap_reset_to_default,
        ap_show_value,
    },
};

#ifdef MTK_MT7933_CONSYS_WIFI_ENABLE
static void save_wep_key_length(uint8_t *length, char *wep_key_len, uint8_t key_id)
{
    uint8_t id = 0;
    uint8_t index = 0;

    do {
        if ('\0' == wep_key_len[index]) {
            return;
        }
        if (key_id == id) {
            *length = (uint8_t)atoi(&wep_key_len[index]);
            return;
        }
        if (',' == wep_key_len[index++]) {
            id++;
        }
    } while (id < 4);
}

static void save_shared_key(uint8_t *wep_key, uint8_t *raw_wep_key, uint8_t length, uint8_t key_id)
{
    uint8_t id = 0;
    uint8_t index = 0;

    do {
        if ('\0' == raw_wep_key[index]) {
            return;
        }
        if (key_id == id) {
            memcpy(wep_key, &raw_wep_key[index], length);
            wep_key[length] = '\0';
            return;
        }
        if (',' == raw_wep_key[index++]) {
            id++;
        }
    } while (id < 4);
}

int32_t wifi_config_init(struct wifi_cfg *wifi_config)
{
#ifdef MTK_WIFI_PROFILE_ENABLE

    // init wifi profile
    uint8_t buff[PROFILE_BUF_LEN];
    uint32_t len = sizeof(buff);

    // common
    len = sizeof(buff);
    nvdm_read_data_item("common", "OpMode", buff, &len);
    wifi_config->opmode = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("common", "CountryCode", buff, &len);
    if (len <= sizeof(wifi_config->country_code)) {
        memcpy(wifi_config->country_code, buff, len);
    } else {
        return -1;
    }

    // STA
    len = sizeof(buff);
    nvdm_read_data_item("STA", "SsidLen", buff, &len);
    wifi_config->sta_ssid_len = (uint8_t)atoi((char *)buff);
    if (wifi_config->sta_ssid_len > sizeof(wifi_config->sta_ssid))
        return -1;
    len = sizeof(buff);
    nvdm_read_data_item("STA", "Ssid", buff, &len);
    memcpy(wifi_config->sta_ssid, buff, wifi_config->sta_ssid_len);

    len = sizeof(buff);
    nvdm_read_data_item("STA", "EncrypType", buff, &len);
    if (0 == (uint8_t)atoi((char *)buff)) { /*0 = WIFI_ENCRYPT_TYPE_WEP_ENABLED*/
        len = sizeof(buff);
        nvdm_read_data_item("STA", "DefaultKeyId", buff, &len);
        wifi_config->sta_default_key_id = (uint8_t)atoi((char *)buff);

        len = sizeof(buff);
        nvdm_read_data_item("STA", "SharedKeyLen", buff, &len);
        save_wep_key_length(&wifi_config->sta_wpa_psk_len, (char *)buff, wifi_config->sta_default_key_id);

        len = sizeof(buff);
        nvdm_read_data_item("STA", "SharedKey", buff, &len);
        save_shared_key(wifi_config->sta_wpa_psk, buff, wifi_config->sta_wpa_psk_len, wifi_config->sta_default_key_id);
    } else if (1 != (uint8_t)atoi((char *)buff)) { /*1 = WIFI_ENCRYPT_TYPE_WEP_DISABLED*/
        len = sizeof(buff);
        nvdm_read_data_item("STA", "WpaPskLen", buff, &len);
        wifi_config->sta_wpa_psk_len = (uint8_t)atoi((char *)buff);
        if (wifi_config->sta_wpa_psk_len >= sizeof(wifi_config->sta_wpa_psk))
            return -1;
        len = sizeof(buff);
        nvdm_read_data_item("STA", "WpaPsk", buff, &len);
        memcpy(wifi_config->sta_wpa_psk, buff, wifi_config->sta_wpa_psk_len);
        wifi_config->sta_default_key_id = 255;
    }
    len = sizeof(buff);
    nvdm_read_data_item("STA", "BW", buff, &len);
    wifi_config->sta_bandwidth = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("STA", "WirelessMode", buff, &len);
    wifi_config->sta_wireless_mode = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("STA", "ListenInterval", buff, &len);
    wifi_config->sta_listen_interval = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("STA", "PSMode", buff, &len);
    wifi_config->sta_power_save_mode = (uint8_t)atoi((char *)buff);

    nvdm_read_data_item("STA", "Channel", buff, &len);
    wifi_config->sta_channel = (uint8_t)atoi((char *)buff);
    // AP
#ifdef MTK_WIFI_REPEATER_ENABLE
    if (wifi_config->opmode == WIFI_MODE_REPEATER) {
        len = sizeof(buff);
        nvdm_read_data_item("STA", "Channel", buff, &len);
        wifi_config->ap_channel = (uint8_t)atoi((char *)buff);
        len = sizeof(buff);
        nvdm_read_data_item("STA", "BW", buff, &len);
        wifi_config->ap_bw = (uint8_t)atoi((char *)buff);
    } else {
#endif /* #ifdef MTK_WIFI_REPEATER_ENABLE */
        /* Use STA MAC/IP as AP MAC/IP for the time being, due to N9 dual interface not ready yet */
        len = sizeof(buff);
        nvdm_read_data_item("AP", "Channel", buff, &len);
        wifi_config->ap_channel = (uint8_t)atoi((char *)buff);
        len = sizeof(buff);
        nvdm_read_data_item("AP", "BW", buff, &len);
        wifi_config->ap_bw = (uint8_t)atoi((char *)buff);
#ifdef MTK_WIFI_REPEATER_ENABLE
    }
#endif /* #ifdef MTK_WIFI_REPEATER_ENABLE */
    len = sizeof(buff);
    nvdm_read_data_item("AP", "SsidLen", buff, &len);
    wifi_config->ap_ssid_len = (uint8_t)atoi((char *)buff);
    if (wifi_config->ap_ssid_len >= sizeof(wifi_config->ap_ssid))
        return -1;
    len = sizeof(buff);
    nvdm_read_data_item("hapd", "ssid", buff, &len);
    memcpy(wifi_config->ap_ssid, buff, wifi_config->ap_ssid_len);
    len = sizeof(buff);
    nvdm_read_data_item("AP", "HideSSID", buff, &len);
    wifi_config->ap_hide_ssid = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("AP", "AuthMode", buff, &len);
    wifi_config->ap_auth_mode = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("AP", "EncrypType", buff, &len);
    wifi_config->ap_encryp_type = (uint8_t)atoi((char *)buff);

    if (0 == wifi_config->ap_encryp_type) { /*WIFI_ENCRYPT_TYPE_WEP_ENABLED*/
        len = sizeof(buff);
        nvdm_read_data_item("AP", "DefaultKeyId", buff, &len);
        wifi_config->ap_default_key_id = (uint8_t)atoi((char *)buff);

        len = sizeof(buff);
        nvdm_read_data_item("AP", "SharedKeyLen", buff, &len);
        save_wep_key_length(&wifi_config->ap_wpa_psk_len, (char *)buff, wifi_config->ap_default_key_id);

        len = sizeof(buff);
        nvdm_read_data_item("AP", "SharedKey", buff, &len);
        save_shared_key(wifi_config->ap_wpa_psk, buff, wifi_config->ap_wpa_psk_len, wifi_config->ap_default_key_id);
    } else {
        len = sizeof(buff);
        nvdm_read_data_item("AP", "WpaPskLen", buff, &len);
        wifi_config->ap_wpa_psk_len = (uint8_t)atoi((char *)buff);
        if (wifi_config->ap_wpa_psk_len >= sizeof(wifi_config->ap_wpa_psk))
            return -1;
        len = sizeof(buff);
        nvdm_read_data_item("AP", "WpaPsk", buff, &len);
        memcpy(wifi_config->ap_wpa_psk, buff, wifi_config->ap_wpa_psk_len);
    }
    len = sizeof(buff);
    nvdm_read_data_item("AP", "WirelessMode", buff, &len);
    wifi_config->ap_wireless_mode = (uint8_t)atoi((char *)buff);
    len = sizeof(buff);
    nvdm_read_data_item("AP", "DtimPeriod", buff, &len);
    wifi_config->ap_dtim_interval = (uint8_t)atoi((char *)buff);

#else /* #ifdef MTK_WIFI_PROFILE_ENABLE */
    //wifi profile is disabled, take the user

#endif /* #ifdef MTK_WIFI_PROFILE_ENABLE */
    return 0;
}
#endif /* #ifdef MTK_MT7933_CONSYS_WIFI_ENABLE */

