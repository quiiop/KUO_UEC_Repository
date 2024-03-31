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

#ifndef __HAL_AUDIO_CM4_DSP_MESSAGE_H__
#define __HAL_AUDIO_CM4_DSP_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

//--------------------------------------------
// CM4 to DSP message base address
//--------------------------------------------
#define MSG_MCU2DSP_COMMON_BASE         0x0000
#define MSG_MCU2DSP_BT_AUDIO_UL_BASE    0x0100  //ToDo
#define MSG_MCU2DSP_BT_AUDIO_DL_BASE    0x0200
#define MSG_MCU2DSP_BT_VOICE_UL_BASE    0x0300
#define MSG_MCU2DSP_BT_VOICE_DL_BASE    0x0400
#define MSG_MCU2DSP_PLAYBACK_BASE       0x0500
#define MSG_MCU2DSP_RECORD_BASE         0x0600  //ToDo
#define MSG_MCU2DSP_PROMPT_BASE         0x0700
#define MSG_MCU2DSP_LINEIN_PLAYBACK_BASE 0x0800
#define MSG_MCU2DSP_BLE_AUDIO_UL_BASE    0x0900
#define MSG_MCU2DSP_BLE_AUDIO_DL_BASE    0x0A00
#define MSG_MCU2DSP_AUDIO_BASE          0x0B00

//--------------------------------------------
// DSP to CM4 message base address
//--------------------------------------------
#define MSG_DSP2MCU_COMMON_BASE         0x8000
#define MSG_DSP2MCU_BT_AUDIO_UL_BASE    0x8100  //ToDo
#define MSG_DSP2MCU_BT_AUDIO_DL_BASE    0x8200
#define MSG_DSP2MCU_BT_VOICE_UL_BASE    0x8300
#define MSG_DSP2MCU_BT_VOICE_DL_BASE    0x8400
#define MSG_DSP2MCU_PLAYBACK_BASE       0x8500
#define MSG_DSP2MCU_RECORD_BASE         0x8600  //ToDo
#define MSG_DSP2MCU_PROMPT_BASE         0x8700
#define MSG_DSP2MCU_LINEIN_PLAYBACK_BASE 0x8800
#define MSG_DSP2MCU_BLE_AUDIO_UL_BASE    0x8900
#define MSG_DSP2MCU_BLE_AUDIO_DL_BASE    0x8A00
#define MSG_DSP2MCU_AUDIO_BASE          0x8B00

//--------------------------------------------
// Detailed message from CM4 to DSP
//--------------------------------------------
typedef enum {
    // MSG_MCU2DSP_COMMON_BASE           0x0000
    MSG_MCU2DSP_COMMON_SET_MEMORY = MSG_MCU2DSP_COMMON_BASE,
    MSG_MCU2DSP_COMMON_SET_SYSRAM,
    MSG_MCU2DSP_COMMON_STREAM_DEINIT,

    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE = MSG_MCU2DSP_COMMON_BASE + 0x10,
    MSG_MCU2DSP_COMMON_MUTE_INPUT_DEVICE,
    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE_VOLUME,
    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE_CHANNEL,

    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE = MSG_MCU2DSP_COMMON_BASE + 0x20,
    MSG_MCU2DSP_COMMON_MUTE_OUTPUT_DEVICE,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE_VOLUME,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE_CHANNEL,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_VOLUME_PARAMETERS,
    MSG_MCU2DSP_COMMON_SW_GAIN_EN,

    MSG_MCU2DSP_COMMON_SPEECH_SET_MODE = MSG_MCU2DSP_COMMON_BASE + 0x30,
    MSG_MCU2DSP_COMMON_SPEECH_SET_ENHANCEMENT_PARAMTER,
    MSG_MCU2DSP_COMMON_SPEECH_ENHANCEMENT_START,
    MSG_MCU2DSP_COMMON_SPEECH_ENHANCEMENT_STOP,

    MSG_MCU2DSP_COMMON_SIDETONE_START = MSG_MCU2DSP_COMMON_BASE + 0x40,
    MSG_MCU2DSP_COMMON_SIDETONE_STOP,
    MSG_MCU2DSP_COMMON_SIDETONE_SET_VOLUME,
    MSG_MCU2DSP_COMMON_ANC_START,
    MSG_MCU2DSP_COMMON_ANC_STOP,
    MSG_MCU2DSP_COMMON_ANC_SET_VOLUME,
    MSG_MCU2DSP_COMMON_ANC_SET_PARAM,
    MSG_MCU2DSP_COMMON_ANC_START_DONE_TEMP,
    MSG_MCU2DSP_COMMON_DC_COMPENSATION_START,
    MSG_MCU2DSP_COMMON_DC_COMPENSATION_STOP,
    MSG_MCU2DSP_COMMON_CHANGE_DSP_SETTING,
    MSG_MCU2DSP_COMMON_CHANGE_DSP_CHANEL,
    MSG_MCU2DSP_COMMON_DUMMY_DSP_SHUTDOWN,
    MSG_MCU2DSP_COMMON_ALC_SWITCH,

    MSG_MCU2DSP_COMMON_REQ_GET_REALTIME_REF_GAIN = MSG_MCU2DSP_COMMON_BASE + 0x50,
    MSG_MCU2DSP_COMMON_AEC_NR_SET_PARAM,
    MSG_MCU2DSP_COMMON_PEQ_SET_PARAM,
    MSG_MCU2DSP_COMMON_DEQ_SET_PARAM,

    MSG_MCU2DSP_COMMON_REQ_GET_AUDIO_FEATURE_PARAMETER_ACK = MSG_MCU2DSP_COMMON_BASE + 0x60,
    MSG_MCU2DSP_COMMON_REQ_SET_AUDIO_FEATURE_PARAMETER_ACK,

    MSG_MCU2DSP_COMMON_AUDIO_DUMP_MASK = MSG_MCU2DSP_COMMON_BASE + 0x70,
    MSG_MCU2DSP_COMMON_AIRDUMP_EN,
    MSG_MCU2DSP_COMMON_AEC_NR_EN,

    // MSG_MCU2DSP_BT_AUDIO_UL_BASE    0x0100

    // MSG_MCU2DSP_BT_AUDIO_DL_BASE    0x0200
    MSG_MCU2DSP_BT_AUDIO_DL_OPEN = MSG_MCU2DSP_BT_AUDIO_DL_BASE,
    MSG_MCU2DSP_BT_AUDIO_DL_CLOSE,
    MSG_MCU2DSP_BT_AUDIO_DL_START,
    MSG_MCU2DSP_BT_AUDIO_DL_STOP,
    MSG_MCU2DSP_BT_AUDIO_DL_CONFIG,
    MSG_MCU2DSP_BT_AUDIO_DL_SET_VOLUME,
    MSG_MCU2DSP_BT_AUDIO_DL_ERROR_TEMP,
    MSG_MCU2DSP_BT_AUDIO_DL_TIME_REPORT_TEMP,
    MSG_MCU2DSP_BT_AUDIO_DL_SUSPEND,
    MSG_MCU2DSP_BT_AUDIO_DL_RESUME,
    MSG_MCU2DSP_BT_AUDIO_DL_LTCS_DATA_REPORT_TEMP,
    MSG_MCU2DSP_BT_AUDIO_DL_REINIT_REQUEST_TEMP,
    MSG_MCU2DSP_BT_AUDIO_DL_RST_LOSTNUM_REPORT,

    // MSG_MCU2DSP_BT_VOICE_UL_BASE    0x0300
    MSG_MCU2DSP_BT_VOICE_UL_OPEN = MSG_MCU2DSP_BT_VOICE_UL_BASE,
    MSG_MCU2DSP_BT_VOICE_UL_CLOSE,
    MSG_MCU2DSP_BT_VOICE_UL_START,
    MSG_MCU2DSP_BT_VOICE_UL_STOP,
    MSG_MCU2DSP_BT_VOICE_UL_CONFIG,
    MSG_MCU2DSP_BT_VOICE_UL_SET_VOLUME,
    MSG_MCU2DSP_BT_VOICE_UL_ERROR_TEMP,
    MSG_MCU2DSP_BT_VOICE_UL_PLAY_EN,
    MSG_MCU2DSP_BT_VOICE_UL_SUSPEND,
    MSG_MCU2DSP_BT_VOICE_UL_RESUME,

    // MSG_MCU2DSP_BT_VOICE_DL_BASE    0x0400
    MSG_MCU2DSP_BT_VOICE_DL_OPEN = MSG_MCU2DSP_BT_VOICE_DL_BASE,
    MSG_MCU2DSP_BT_VOICE_DL_CLOSE,
    MSG_MCU2DSP_BT_VOICE_DL_START,
    MSG_MCU2DSP_BT_VOICE_DL_STOP,
    MSG_MCU2DSP_BT_VOICE_DL_CONFIG,
    MSG_MCU2DSP_BT_VOICE_DL_SET_VOLUME,
    MSG_MCU2DSP_BT_VOICE_DL_ERROR_TEMP,
    MSG_MCU2DSP_BT_VOICE_DL_SUSPEND,
    MSG_MCU2DSP_BT_VOICE_DL_RESUME,
    MSG_MCU2DSP_BT_VOICE_DL_AVC_PARA_SEND,

    // MSG_MCU2DSP_PLAYBACK_BASE       0x0500
    MSG_MCU2DSP_PLAYBACK_OPEN = MSG_MCU2DSP_PLAYBACK_BASE,
    MSG_MCU2DSP_PLAYBACK_CLOSE,
    MSG_MCU2DSP_PLAYBACK_START,
    MSG_MCU2DSP_PLAYBACK_STOP,
    MSG_MCU2DSP_PLAYBACK_CONFIG,
    MSG_MCU2DSP_PLAYBACK_SET_VOLUME,
    MSG_MCU2DSP_PLAYBACK_ERROR_TEMP,
    MSG_MCU2DSP_PLAYBACK_DATA_REQUEST_TEMP,
    MSG_MCU2DSP_PLAYBACK_SUSPEND,
    MSG_MCU2DSP_PLAYBACK_RESUME,

    // MSG_MCU2DSP_RECORD_BASE         0x0600
    MSG_MCU2DSP_RECORD_OPEN = MSG_MCU2DSP_RECORD_BASE,
    MSG_MCU2DSP_RECORD_CLOSE,
    MSG_MCU2DSP_RECORD_START,
    MSG_MCU2DSP_RECORD_STOP,
    MSG_MCU2DSP_RECORD_CONFIG,
    MSG_MCU2DSP_RECORD_SET_VOLUME,
    MSG_MCU2DSP_RECORD_DATA_NOTIFY_TEMP,
    MSG_MCU2DSP_RECORD_ERROR_TEMP,
    MSG_MCU2DSP_RECORD_SUSPEND,
    MSG_MCU2DSP_RECORD_RESUME,

    // MSG_MCU2DSP_PROMPT_BASE         0x0700
    MSG_MCU2DSP_PROMPT_OPEN = MSG_MCU2DSP_PROMPT_BASE,
    MSG_MCU2DSP_PROMPT_CLOSE,
    MSG_MCU2DSP_PROMPT_START,
    MSG_MCU2DSP_PROMPT_STOP,
    MSG_MCU2DSP_PROMPT_CONFIG,
    MSG_MCU2DSP_PROMPT_SET_VOLUME,
    MSG_MCU2DSP_PROMPT_ERROR_TEMP,
    MSG_MCU2DSP_PROMPT_DATA_REQUEST_TEMP,
    MSG_MCU2DSP_PROMPT_AWS_SYNC_TRIGGER,

    // MSG_MCU2DSP_LINEIN_PLAYBACK_BASE         0x0800
    MSG_MCU2DSP_LINEIN_PLAYBACK_OPEN = MSG_MCU2DSP_LINEIN_PLAYBACK_BASE,
    MSG_MCU2DSP_LINEIN_PLAYBACK_CLOSE,
    MSG_MCU2DSP_LINEIN_PLAYBACK_START,
    MSG_MCU2DSP_LINEIN_PLAYBACK_STOP,
    MSG_MCU2DSP_LINEIN_PLAYBACK_SUSPEND,
    MSG_MCU2DSP_LINEIN_PLAYBACK_RESUME,
    MSG_MCU2DSP_TRULY_LINEIN_PLAYBACK_OPEN,
    MSG_MCU2DSP_TRULY_LINEIN_PLAYBACK_CLOSE,

    // MSG_MCU2DSP_BLE_AUDIO_UL_BASE    0x0900
    MSG_MCU2DSP_BLE_AUDIO_UL_OPEN = MSG_MCU2DSP_BLE_AUDIO_UL_BASE,
    MSG_MCU2DSP_BLE_AUDIO_UL_CLOSE,
    MSG_MCU2DSP_BLE_AUDIO_UL_START,
    MSG_MCU2DSP_BLE_AUDIO_UL_STOP,
    MSG_MCU2DSP_BLE_AUDIO_UL_CONFIG,
    MSG_MCU2DSP_BLE_AUDIO_UL_SET_VOLUME,
    MSG_MCU2DSP_BLE_AUDIO_UL_ERROR_TEMP,
    MSG_MCU2DSP_BLE_AUDIO_UL_PLAY_EN,
    MSG_MCU2DSP_BLE_AUDIO_UL_SUSPEND,
    MSG_MCU2DSP_BLE_AUDIO_UL_RESUME,
    MSG_MCU2DSP_BLE_AUDIO_UL_BUFFER_INFO,
    MSG_MCU2DSP_BLE_AUDIO_UL_PLAYBACK_DATA_INFO,

    // MSG_MCU2DSP_BLE_AUDIO_DL_BASE    0x0A00
    MSG_MCU2DSP_BLE_AUDIO_DL_OPEN = MSG_MCU2DSP_BLE_AUDIO_DL_BASE,
    MSG_MCU2DSP_BLE_AUDIO_DL_CLOSE,
    MSG_MCU2DSP_BLE_AUDIO_DL_START,
    MSG_MCU2DSP_BLE_AUDIO_DL_STOP,
    MSG_MCU2DSP_BLE_AUDIO_DL_CONFIG,
    MSG_MCU2DSP_BLE_AUDIO_DL_SET_VOLUME,
    MSG_MCU2DSP_BLE_AUDIO_DL_ERROR_TEMP,
    MSG_MCU2DSP_BLE_AUDIO_DL_SUSPEND,
    MSG_MCU2DSP_BLE_AUDIO_DL_RESUME,
    MSG_MCU2DSP_BLE_AUDIO_DL_BUFFER_INFO,
    MSG_MCU2DSP_BLE_AUDIO_INIT_PLAY_INFO,

    // MSG_MCU2DSP_AUDIO_BASE
    MSG_MCU2DSP_AUDIO_AMP_RESERVED  = MSG_MCU2DSP_AUDIO_BASE,
    MSG_MCU2DSP_AUDIO_AMP_FORCE_CLOSE,

    //== Ack ==
    // 0x8207
    MSG_MCU2DSP_BT_AUDIO_DL_ERROR_ACK = MSG_MCU2DSP_BT_AUDIO_DL_ERROR_TEMP + 0x8000,
    MSG_MCU2DSP_BT_AUDIO_DL_TIME_REPORT_ACK,

    // 0x8306
    MSG_MCU2DSP_BT_VOICE_UL_ERROR_ACK = MSG_MCU2DSP_BT_VOICE_UL_ERROR_TEMP + 0x8000,

    // 0x8406
    MSG_MCU2DSP_BT_VOICE_DL_ERROR_ACK = MSG_MCU2DSP_BT_VOICE_DL_ERROR_TEMP + 0x8000,

    // 0x8506
    MSG_MCU2DSP_PLAYBACK_ERROR_ACK = MSG_MCU2DSP_PLAYBACK_ERROR_TEMP + 0x8000,
    MSG_MCU2DSP_PLAYBACK_DATA_REQUEST_ACK,

    // 0x8606
    MSG_MCU2DSP_RECORD_DATA_NOTIFY_ACK = MSG_MCU2DSP_RECORD_DATA_NOTIFY_TEMP + 0x8000,
    MSG_MCU2DSP_RECORD_ERROR_ACK = MSG_MCU2DSP_RECORD_ERROR_TEMP + 0x8000,

    // 0x8704
    MSG_MCU2DSP_PROMPT_CONFIG_ACK = MSG_MCU2DSP_PROMPT_CONFIG + 0x8000,

    // 0x8706
    MSG_MCU2DSP_PROMPT_ERROR_ACK = MSG_MCU2DSP_PROMPT_ERROR_TEMP + 0x8000,
    MSG_MCU2DSP_PROMPT_DATA_REQUEST_ACK,

} mcu2dsp_audio_msg_t;

//--------------------------------------------
// Detailed message from DSP to MCU
//--------------------------------------------
typedef enum {
    // MSG_DSP2MCU_COMMON_BASE           0x8000
    MSG_DSP2MCU_COMMON_SET_MEMORY_ACK = MSG_DSP2MCU_COMMON_BASE,
    MSG_DSP2MCU_COMMON_SET_SYSRAM_ACK,
    MSG_DSP2MCU_COMMON_STREAM_DEINIT_ACK,

    MSG_DSP2MCU_COMMON_SET_INPUT_DEVICE_ACK = MSG_DSP2MCU_COMMON_BASE + 0x10,
    MSG_DSP2MCU_COMMON_MUTE_INPUT_DEVICE_ACK,
    MSG_DSP2MCU_COMMON_SET_INPUT_DEVICE_VOLUME_ACK,

    MSG_DSP2MCU_COMMON_SET_OUTPUT_DEVICE_ACK = MSG_DSP2MCU_COMMON_BASE + 0x20,
    MSG_DSP2MCU_COMMON_MUTE_OUTPUT_DEVICE_ACK,
    MSG_DSP2MCU_COMMON_SET_OUTPUT_DEVICE_VOLUME_ACK,
    MSG_DSP2MCU_COMMON_SET_OUTPUT_DEVICE_CHANNEL_ACK,
    MSG_DSP2MCU_COMMON_SET_OUTPUT_VOLUME_PARAMETERS_ACK,

    MSG_DSP2MCU_COMMON_SPEECH_SET_MODE_ACK = MSG_DSP2MCU_COMMON_BASE + 0x30,
    MSG_DSP2MCU_COMMON_SPEECH_SET_ENHANCEMENT_PARAMTER_ACK,
    MSG_DSP2MCU_COMMON_SPEECH_ENHANCEMENT_START_ACK,
    MSG_DSP2MCU_COMMON_SPEECH_ENHANCEMENT_STOP_ACK,

    MSG_DSP2MCU_COMMON_SIDETONE_START_ACK = MSG_DSP2MCU_COMMON_BASE + 0x40,
    MSG_DSP2MCU_COMMON_SIDETONE_STOP_ACK,
    MSG_DSP2MCU_COMMON_ANC_START_ACK      = MSG_DSP2MCU_COMMON_BASE + MSG_MCU2DSP_COMMON_ANC_START,
    MSG_DSP2MCU_COMMON_ANC_STOP_ACK,
    MSG_DSP2MCU_COMMON_ANC_SET_VOLUME_ACK,
    MSG_DSP2MCU_COMMON_ANC_SET_PARAM_ACK,
    MSG_DSP2MCU_COMMON_ANC_START_DONE_TEMP,
    MSG_DSP2MCU_COMMON_DC_COMPENSATION_START_ACK = MSG_DSP2MCU_COMMON_BASE + MSG_MCU2DSP_COMMON_DC_COMPENSATION_START,
    MSG_DSP2MCU_COMMON_DC_COMPENSATION_STOP_ACK,
    MSG_DSP2MCU_COMMON_CHANGE_DSP_SETTING_ACK    = MSG_DSP2MCU_COMMON_BASE + MSG_MCU2DSP_COMMON_CHANGE_DSP_SETTING,
    MSG_DSP2MCU_COMMON_CHANGE_DSP_CHANEL_ACK,
    MSG_DSP2MCU_COMMON_DUMMY_DSP_SHUTDOWN_ACK = MSG_DSP2MCU_COMMON_BASE + MSG_MCU2DSP_COMMON_DUMMY_DSP_SHUTDOWN,

    MSG_DSP2MCU_COMMON_REQ_GET_REALTIME_REF_GAIN_ACK = MSG_DSP2MCU_COMMON_BASE + 0x50,
    MSG_DSP2MCU_COMMON_AEC_NR_SET_PARAM_ACK,
    MSG_DSP2MCU_COMMON_PEQ_SET_PARAM_ACK,
    MSG_DSP2MCU_COMMON_DEQ_SET_PARAM_ACK,

    MSG_DSP2MCU_COMMON_REQ_GET_AUDIO_FEATURE_PARAMETER = MSG_DSP2MCU_COMMON_BASE + 0x60,
    MSG_DSP2MCU_COMMON_REQ_SET_AUDIO_FEATURE_PARAMETER,

    // MSG_DSP2MCU_BT_AUDIO_UL_BASE    0x8100

    // MSG_DSP2MCU_BT_AUDIO_DL_BASE    0x8200
    MSG_DSP2MCU_BT_AUDIO_DL_OPEN_ACK = MSG_DSP2MCU_BT_AUDIO_DL_BASE,
    MSG_DSP2MCU_BT_AUDIO_DL_CLOSE_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_START_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_STOP_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_CONFIG_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_SET_VOLUME_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_ERROR_TEMP,
    MSG_DSP2MCU_BT_AUDIO_DL_TIME_REPORT_TEMP,
    MSG_DSP2MCU_BT_AUDIO_DL_SUSPEND_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_RESUME_ACK,
    MSG_DSP2MCU_BT_AUDIO_DL_LTCS_DATA_REPORT_TEMP,
    MSG_DSP2MCU_BT_AUDIO_DL_REINIT_REQUEST_TEMP,
    MSG_DSP2MCU_BT_AUDIO_DL_ALC_REQUEST_TEMP,

    // MSG_DSP2MCU_BT_VOICE_UL_BASE    0x8300
    MSG_DSP2MCU_BT_VOICE_UL_OPEN_ACK = MSG_DSP2MCU_BT_VOICE_UL_BASE,
    MSG_DSP2MCU_BT_VOICE_UL_CLOSE_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_START_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_STOP_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_CONFIG_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_SET_VOLUME_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_ERROR_TEMP,
    MSG_DSP2MCU_BT_VOICE_UL_PLAY_EN_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_SUSPEND_ACK,
    MSG_DSP2MCU_BT_VOICE_UL_RESUME_ACK,
    MSG_DSP2MCU_AVC_PARA_SEND_TEMP,

    // MSG_DSP2MCU_BT_VOICE_DL_BASE    0x8400
    MSG_DSP2MCU_BT_VOICE_DL_OPEN_ACK = MSG_DSP2MCU_BT_VOICE_DL_BASE,
    MSG_DSP2MCU_BT_VOICE_DL_CLOSE_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_START_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_STOP_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_CONFIG_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_SET_VOLUME_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_ERROR_TEMP,
    MSG_DSP2MCU_BT_VOICE_DL_SUSPEND_ACK,
    MSG_DSP2MCU_BT_VOICE_DL_RESUME_ACK,

    // MSG_DSP2MCU_PLAYBACK_BASE       0x8500
    MSG_DSP2MCU_PLAYBACK_OPEN_ACK = MSG_DSP2MCU_PLAYBACK_BASE,
    MSG_DSP2MCU_PLAYBACK_CLOSE_ACK,
    MSG_DSP2MCU_PLAYBACK_START_ACK,
    MSG_DSP2MCU_PLAYBACK_STOP_ACK,
    MSG_DSP2MCU_PLAYBACK_CONFIG_ACK,
    MSG_DSP2MCU_PLAYBACK_SET_VOLUME_ACK,
    MSG_DSP2MCU_PLAYBACK_ERROR_TEMP,
    MSG_DSP2MCU_PLAYBACK_DATA_REQUEST_TEMP,
    MSG_DSP2MCU_PLAYBACK_SUSPEND_ACK,
    MSG_DSP2MCU_PLAYBACK_RESUME_ACK,

    // MSG_DSP2MCU_RECORD_BASE         0x8600
    MSG_DSP2MCU_RECORD_OPEN_ACK = MSG_DSP2MCU_RECORD_BASE,
    MSG_DSP2MCU_RECORD_CLOSE_ACK,
    MSG_DSP2MCU_RECORD_START_ACK,
    MSG_DSP2MCU_RECORD_STOP_ACK,
    MSG_DSP2MCU_RECORD_CONFIG_ACK,
    MSG_DSP2MCU_RECORD_SET_VOLUME_ACK,
    MSG_DSP2MCU_RECORD_DATA_NOTIFY_TEMP,
    MSG_DSP2MCU_RECORD_ERROR_TEMP,
    MSG_DSP2MCU_RECORD_SUSPEND_ACK,
    MSG_DSP2MCU_RECORD_RESUME_ACK,

    // MSG_DSP2MCU_PROMPT_BASE         0x8700
    MSG_DSP2MCU_PROMPT_OPEN_ACK = MSG_DSP2MCU_PROMPT_BASE,
    MSG_DSP2MCU_PROMPT_CLOSE_ACK,
    MSG_DSP2MCU_PROMPT_START_ACK,
    MSG_DSP2MCU_PROMPT_STOP_ACK,
    MSG_DSP2MCU_PROMPT_CONFIG_ACK,
    MSG_DSP2MCU_PROMPT_SET_VOLUME_ACK,
    MSG_DSP2MCU_PROMPT_ERROR_TEMP,
    MSG_DSP2MCU_PROMPT_DATA_REQUEST_TEMP,

    // MSG_DSP2MCU_LINEIN_PLAYBACK_BASE         0x8800
    MSG_DSP2MCU_LINEIN_PLAYBACK_OPEN_ACK = MSG_DSP2MCU_LINEIN_PLAYBACK_BASE,
    MSG_DSP2MCU_LINEIN_PLAYBACK_CLOSE_ACK,
    MSG_DSP2MCU_LINEIN_PLAYBACK_START_ACK,
    MSG_DSP2MCU_LINEIN_PLAYBACK_STOP_ACK,
    MSG_DSP2MCU_LINEIN_PLAYBACK_SUSPEND_ACK,
    MSG_DSP2MCU_LINEIN_PLAYBACK_RESUME_ACK,
    MSG_DSP2MCU_TRULY_LINEIN_PLAYBACK_OPEN_ACK,
    MSG_DSP2MCU_TRULY_LINEIN_PLAYBACK_CLOSE_ACK,

    // MSG_DSP2MCU_BLE_AUDIO_UL_BASE    0x8900
    MSG_DSP2MCU_BLE_AUDIO_UL_OPEN_ACK = MSG_DSP2MCU_BLE_AUDIO_UL_BASE,
    MSG_DSP2MCU_BLE_AUDIO_UL_CLOSE_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_START_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_STOP_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_CONFIG_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_SET_VOLUME_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_ERROR_TEMP,
    MSG_DSP2MCU_BLE_AUDIO_UL_PLAY_EN_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_SUSPEND_ACK,
    MSG_DSP2MCU_BLE_AUDIO_UL_RESUME_ACK,

    // MSG_DSP2MCU_BLE_AUDIO_DL_BASE    0x8A00
    MSG_DSP2MCU_BLE_AUDIO_DL_OPEN_ACK = MSG_DSP2MCU_BLE_AUDIO_DL_BASE,
    MSG_DSP2MCU_BLE_AUDIO_DL_CLOSE_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_START_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_STOP_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_CONFIG_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_SET_VOLUME_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_ERROR_TEMP,
    MSG_DSP2MCU_BLE_AUDIO_DL_SUSPEND_ACK,
    MSG_DSP2MCU_BLE_AUDIO_DL_RESUME_ACK,

    //MSG_DSP2MCU_AUDIO_BASE
    MSG_DSP2MCU_AUDIO_AMP_TEMP          = MSG_DSP2MCU_AUDIO_BASE,
    MSG_DSP2MCU_AUDIO_AMP_FORCE_CLOSE_ACK,

    //== Master command ==
    // 0x0047
    MSG_DSP2MCU_COMMON_ANC_START_DONE        = MSG_DSP2MCU_COMMON_ANC_START_DONE_TEMP - 0x8000,

    // 0x0206
    MSG_DSP2MCU_BT_AUDIO_DL_ERROR            = MSG_DSP2MCU_BT_AUDIO_DL_ERROR_TEMP - 0x8000,
    MSG_DSP2MCU_BT_AUDIO_DL_TIME_REPORT      = MSG_DSP2MCU_BT_AUDIO_DL_TIME_REPORT_TEMP - 0x8000,
    MSG_DSP2MCU_BT_AUDIO_DL_LTCS_DATA_REPORT = MSG_DSP2MCU_BT_AUDIO_DL_LTCS_DATA_REPORT_TEMP - 0x8000,
    MSG_DSP2MCU_BT_AUDIO_DL_REINIT_REQUEST   = MSG_DSP2MCU_BT_AUDIO_DL_REINIT_REQUEST_TEMP - 0x8000,
    MSG_DSP2MCU_BT_AUDIO_DL_ALC_REQUEST      = MSG_DSP2MCU_BT_AUDIO_DL_ALC_REQUEST_TEMP - 0x8000,

    // 0x0306
    MSG_DSP2MCU_BT_VOICE_UL_ERROR = MSG_DSP2MCU_BT_VOICE_UL_ERROR_TEMP - 0x8000,

    // 0x0307
    MSG_DSP2MCU_AVC_PARA_SEND     = MSG_DSP2MCU_AVC_PARA_SEND_TEMP - 0x8000,

    // 0x0406
    MSG_DSP2MCU_BT_VOICE_DL_ERROR = MSG_DSP2MCU_BT_VOICE_DL_ERROR_TEMP - 0x8000,

    // 0x0506
    MSG_DSP2MCU_PLAYBACK_ERROR = MSG_DSP2MCU_PLAYBACK_ERROR_TEMP - 0x8000,
    MSG_DSP2MCU_PLAYBACK_DATA_REQUEST = MSG_DSP2MCU_PLAYBACK_DATA_REQUEST_TEMP - 0x8000,

    // 0x0606
    MSG_DSP2MCU_RECORD_DATA_NOTIFY = MSG_DSP2MCU_RECORD_DATA_NOTIFY_TEMP - 0x8000,
    MSG_DSP2MCU_RECORD_ERROR = MSG_DSP2MCU_RECORD_ERROR_TEMP - 0x8000,

    // 0x0706
    MSG_DSP2MCU_PROMPT_ERROR = MSG_DSP2MCU_PROMPT_ERROR_TEMP - 0x8000,
    MSG_DSP2MCU_PROMPT_DATA_REQUEST = MSG_DSP2MCU_PROMPT_DATA_REQUEST_TEMP - 0x8000,

    // 0x0B03
    MSG_DSP2MCU_AUDIO_AMP  = MSG_DSP2MCU_AUDIO_AMP_TEMP - 0x8000,
} dsp2mcu_audio_msg_t;

typedef struct _stream_params_t {
    uint32_t sample_rate;
    uint32_t channels;
    uint32_t bit_type;
    uint32_t period_size;
    uint32_t period_count;
    uint32_t format;
} stream_params_t;

enum {
    DSP_BT_BLE_START = 0,
    DSP_BT_BLE_STOP,
    DSP_BT_BLE_LC3_CODEC,
    DSP_BT_BLE_CH_UPDATE,
};

int32_t _auddrv_cset(const char *ctrl_name, int32_t value_count, void *value);
int32_t _auddrv_cget(const char *ctrl_name, int32_t value_count, void *value);
int32_t audio_drv_init(stream_params_t *stream_param, bool is_leaudio);
int32_t audio_drv_deinit(bool is_leaudio);
int32_t audio_drv_set_volume(uint32_t volume);
int32_t audio_ipi_dsp_open(stream_params_t *stream_param);
int32_t audio_ipi_dsp_close(void);
int32_t audio_ipi_dsp_start(void);
int32_t audio_ipi_dsp_stop(void);
int32_t audio_ipi_dsp_suspend(void);
int32_t audio_ipi_dsp_resume(void);
uint16_t _copy_shared(void *buffer, uint32_t data_size);

#ifdef CFG_AUDIO_DSP_LEAUDIO_EN
int32_t le_audio_ipi_dsp_open(stream_params_t *stream_param);
int32_t le_audio_ipi_dsp_close(void);
int32_t le_audio_ipi_dsp_start(void);
int32_t le_audio_ipi_dsp_stop(void);
int32_t le_audio_ipi_dsp_suspend(void);
int32_t le_audio_ipi_dsp_resume(void);
#endif /* #ifdef CFG_AUDIO_DSP_LEAUDIO_EN */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef __HAL_AUDIO_CM4_DSP_MESSAGE_H__ */
