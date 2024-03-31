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

//#include "config.h"
#include "dsp_drv_afe_hal.h"
#include "dsp_drv_afe.h"
#include "dsp_audio_ctrl.h"
#include "dsp_control.h"
#ifdef HAL_AUDIO_READY
#include "hal_audio.h"
#endif
#include "audio_afe_common.h"
#include "dtm.h"

#ifdef ENABLE_AMP_TIMER
#define FW_AMP_CLOSURE_TIMER   (2000)
static fw_amp_config_t amp_ctrl;
#endif

#ifdef ENABLE_SIDETONE_RAMP_TIMER
fw_sidetone_ramp_config_t sidetone_ctrl;
#endif

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/
VOID DSP_DRV_AFE_Init (VOID);
VOID DSP_DRV_AFE_ChangeOperationMode (AU_AFE_OP_MODE_t Mode);
VOID DSP_DRV_AFE_ChangeOutputChannel (AU_AFE_OUT_CH_t Channel);
VOID DSP_DRV_AFE_ConfigAnalogOutput (AU_SIG_CTRL_t Enable);
VOID DSP_DRV_AFE_ConfigAnalogInput (AU_SIG_CTRL_t Enable);
VOID DSP_DRV_AFE_ConfigAnalogMicInput (AU_SIG_CTRL_t Enable);
VOID DSP_DRV_AFE_ConfigAnalogLineInput (AU_SIG_CTRL_t Enable);
VOID DSP_DRV_AFE_GetDefaultAfePara (VOID);
VOID DSP_DRV_AFE_SetDefaultAfePara (VOID);

VOID DSP_DRV_AFE_Init (VOID)
{
    DSP_DRV_AFE_GetDefaultAfePara();
    DSP_DRV_AFE_SetDefaultAfePara();
#ifdef HAL_AUDIO_READY
    hal_audio_init();
#endif
}

VOID DSP_DRV_AFE_ChangeOperationMode (AU_AFE_OP_MODE_t Mode)
{
     gAudioCtrl.Afe.OperationMode = Mode;
}

VOID DSP_DRV_AFE_ChangeOutputChannel (AU_AFE_OUT_CH_t Channel)
{
     gAudioCtrl.Afe.OutputChannel = Channel;
}

VOID DSP_DRV_AFE_ConfigAnalogOutput (AU_SIG_CTRL_t Enable)
{
    UNUSED(Enable);
}

VOID DSP_DRV_AFE_SetOutputGain (AU_AFE_OUT_GAIN_COMPONENT_t Component, S32 Gain)
{
    UNUSED(Component);
    UNUSED(Gain);
}

VOID DSP_DRV_AFE_SetInputGain (AU_AFE_IN_GAIN_COMPONENT_t Component, U8 Gain)
{
    UNUSED(Component);
    UNUSED(Gain);
}

VOID DSP_DRV_AFE_GetDefaultAfePara (VOID)
{
    // /* The followings should be captured from NVKEY */
    gAudioCtrl.Afe.InputChannel     = AU_AFE_IN_CH_1;
    gAudioCtrl.Afe.OutputChannel    = AU_AFE_OUT_CH_2;

    gAudioCtrl.Afe.OperationMode    = AU_AFE_OP_PLAYBACK_MODE;  //AU_AFE_OP_LINE_DSP_MODE;
    gAudioCtrl.Afe.OutputMode       = AU_AFE_OUT_DIFFERENTIAL_MODE;
    gAudioCtrl.Afe.UseAncMic        = 0;

    gAudioCtrl.Afe.DeviceInType     = HAL_AUDIO_DEVICE_MAIN_MIC;
    gAudioCtrl.Afe.DeviceOutType    = HAL_AUDIO_DEVICE_HEADSET;

    gAudioCtrl.Afe.AfeDLSetting.format  = AFE_PCM_FORMAT_S16_LE;
    gAudioCtrl.Afe.AfeDLSetting.rate    = 8000;
    gAudioCtrl.Afe.AfeDLSetting.period  = 15;
    gAudioCtrl.Afe.AfeULSetting.format  = AFE_PCM_FORMAT_S16_LE;
    gAudioCtrl.Afe.AfeULSetting.rate    = 8000;
    gAudioCtrl.Afe.AfeULSetting.period  = 15;

    /* Force settings from AFE default parameter */
    gAudioCtrl.Afe.ForceSet         = 0;
}

VOID DSP_DRV_AFE_SetDefaultAfePara (VOID)
{
    if (gAudioCtrl.Afe.ForceSet)
    {
        return;
    }
}

#ifdef USE_CCNI
/*Set device from CM4 ccni msg*/
void DSP_DRV_AFE_SetOutputDevice(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    hal_audio_device_t device = (hal_audio_device_t)(uint16_t)msg.ccni_message[1];
    hal_audio_set_stream_out_device(device);
    DSP_MW_LOG_I("DSP_DRV_AFE_SetOutputDevice, device=%d", 1,device);
    UNUSED(ack);
}

void DSP_DRV_AFE_SetInputDevice(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    hal_audio_device_t device = (hal_audio_device_t)(uint16_t)msg.ccni_message[1];
    hal_audio_set_stream_in_device(device);
    DSP_MW_LOG_I("DSP_DRV_AFE_SetInputDevice, device=%d", 1,device);
    UNUSED(ack);
}

/*Set channel from CM4 ccni msg*/
void DSP_DRV_AFE_SetOutputChannel(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    hal_audio_channel_number_t channel_number = (hal_audio_channel_number_t)(uint16_t)msg.ccni_message[1];
    hal_audio_set_stream_out_channel_number(channel_number);
    DSP_MW_LOG_I("DSP_DRV_AFE_SetOutputChannel, channel_number=%d", 1,channel_number);
    UNUSED(ack);
}

void DSP_DRV_AFE_SetInputChannel(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    hal_audio_channel_number_t channel_number = (hal_audio_channel_number_t)(uint16_t)msg.ccni_message[1];
    hal_audio_set_stream_in_channel_number(channel_number);
    DSP_MW_LOG_I("DSP_DRV_AFE_SetInputChannel, channel_number=%d", 1,channel_number);
    UNUSED(ack);
}
#endif

audio_hardware afe_get_audio_hardware_by_au_afe_open_param (au_afe_open_param_t afe_open)
{
    audio_hardware hardware;
    switch (afe_open.audio_device) {
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_L:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_R:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_DUAL:
            hardware = AUDIO_HARDWARE_DIGITAL_MIC;
            break;
        case HAL_AUDIO_DEVICE_NONE:
        case HAL_AUDIO_DEVICE_MAIN_MIC_L:
        case HAL_AUDIO_DEVICE_MAIN_MIC_R:
        case HAL_AUDIO_DEVICE_MAIN_MIC_DUAL:
        case HAL_AUDIO_DEVICE_DAC_L:
        case HAL_AUDIO_DEVICE_DAC_R:
        case HAL_AUDIO_DEVICE_DAC_DUAL:
        default:
            hardware = AUDIO_HARDWARE_PCM;
            break;
        case HAL_AUDIO_DEVICE_I2S_MASTER:
            hardware = AUDIO_HARDWARE_I2S_M;
            break;
        case HAL_AUDIO_DEVICE_I2S_SLAVE:
            hardware = AUDIO_HARDWARE_I2S_S;
            break;

        case HAL_AUDIO_DEVICE_EXT_CODEC:
            hardware = AUDIO_HARDWARE_CODEC;
            break;
    }
    return hardware;
}

audio_instance afe_get_audio_instance_by_au_afe_open_param (au_afe_open_param_t afe_open)
{
    audio_instance instance = INSTANCE_A;
    switch (afe_open.audio_device) {
        case HAL_AUDIO_DEVICE_MAIN_MIC_L:
        case HAL_AUDIO_DEVICE_MAIN_MIC_R:
        case HAL_AUDIO_DEVICE_MAIN_MIC_DUAL:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_L:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_R:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_DUAL:
            instance = INSTANCE_B;
            break;
        case HAL_AUDIO_DEVICE_NONE:
        case HAL_AUDIO_DEVICE_DAC_L:
        case HAL_AUDIO_DEVICE_DAC_R:
        case HAL_AUDIO_DEVICE_DAC_DUAL:
        case HAL_AUDIO_DEVICE_EXT_CODEC:
        default:
            instance = INSTANCE_A;
            break;
        case HAL_AUDIO_DEVICE_I2S_MASTER:
        case HAL_AUDIO_DEVICE_I2S_SLAVE:
            if (afe_open.audio_interface == HAL_AUDIO_INTERFACE_1) {
                instance = INSTANCE_A;
            } else if (afe_open.audio_interface == HAL_AUDIO_INTERFACE_2) {
                instance = INSTANCE_B;
            } else if (afe_open.audio_interface == HAL_AUDIO_INTERFACE_3) {
                instance = INSTANCE_C;
            } else if (afe_open.audio_interface == HAL_AUDIO_INTERFACE_4) {
                instance = INSTANCE_D;
            }
            break;
    }
    return instance;
}

audio_channel afe_get_audio_channel_by_au_afe_open_param (au_afe_open_param_t afe_open)
{
    audio_channel channel;
    switch (afe_open.audio_device) {
        case HAL_AUDIO_DEVICE_MAIN_MIC_L:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_L:
        case HAL_AUDIO_DEVICE_DAC_L:
            if (afe_open.stream_channel == HAL_AUDIO_DIRECT) {
                channel = AUDIO_CHANNEL_A;
            } else {
                channel = AUDIO_CHANNEL_A_AND_B;
            }

            if(afe_open.audio_device1 != HAL_AUDIO_DEVICE_NONE)
            {
                if(afe_open.audio_device2 != HAL_AUDIO_DEVICE_NONE)
                {
                    if(afe_open.audio_device3 != HAL_AUDIO_DEVICE_NONE)
                    {
                        channel = AUDIO_CHANNEL_4ch;
                    }else{
                        channel = AUDIO_CHANNEL_3ch;
                    }
                } else {
                    channel = AUDIO_CHANNEL_A_AND_B;
                }
            }
            break;
        case HAL_AUDIO_DEVICE_MAIN_MIC_R:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_R:
        case HAL_AUDIO_DEVICE_DAC_R:
            if (afe_open.stream_channel == HAL_AUDIO_DIRECT) {
                channel = AUDIO_CHANNEL_B;
            } else {
                channel = AUDIO_CHANNEL_A_AND_B;
            }

            if(afe_open.audio_device1 != HAL_AUDIO_DEVICE_NONE)
            {
                if(afe_open.audio_device2 != HAL_AUDIO_DEVICE_NONE)
                {
                    if(afe_open.audio_device3 != HAL_AUDIO_DEVICE_NONE)
                    {
                        channel = AUDIO_CHANNEL_4ch;
                    }else{
                        channel = AUDIO_CHANNEL_3ch;
                    }
                } else {
                    channel = AUDIO_CHANNEL_A_AND_B;
                }
            }
            break;
        case HAL_AUDIO_DEVICE_NONE:
        case HAL_AUDIO_DEVICE_DIGITAL_MIC_DUAL:
        case HAL_AUDIO_DEVICE_MAIN_MIC_DUAL:
        case HAL_AUDIO_DEVICE_DAC_DUAL:
        case HAL_AUDIO_DEVICE_I2S_MASTER:
        case HAL_AUDIO_DEVICE_I2S_SLAVE:
        case HAL_AUDIO_DEVICE_EXT_CODEC:
        default:
            channel = AUDIO_CHANNEL_A_AND_B;
            break;
    }
#if defined(MTK_ANC_ENABLE) && defined(MTK_DEQ_ENABLE)
    if (afe_open.audio_device & HAL_AUDIO_DEVICE_DAC_DUAL) {
        channel = AUDIO_CHANNEL_A_AND_B;
    }
#endif
    //Need to modify for echo path channel

    return channel;
}

#ifdef ENABLE_AMP_TIMER
static void fw_amp_timer_callback(TimerHandle_t xTimer)
{
    UNUSED(xTimer);
    DSP_MW_LOG_I("DSP AMP timer callback  %d \n", 1, fw_amp_get_status());
    if (xSemaphoreTake(amp_ctrl.semaphore, portMAX_DELAY) == pdTRUE) {
        if (fw_amp_get_status() == FW_AMP_TIMER_START) {
            fw_amp_set_status(FW_AMP_TIMER_END);
            // AMP close
            afe_audio_device_enable(false, HAL_AUDIO_DEVICE_DAC_DUAL, HAL_AUDIO_INTERFACE_NONE, HAL_AUDIO_MEM1, AFE_PCM_FORMAT_S32_LE, 48000, DOWNLINK_PERFORMANCE_NORMAL);
            afe_send_amp_status_ccni(false);
        }
    } else {
        configASSERT(false);
    }
    xSemaphoreGive(amp_ctrl.semaphore);
}

void fw_amp_init_semaphore (void)
{
    amp_ctrl.semaphore = xSemaphoreCreateBinary();
    if(!amp_ctrl.semaphore) {
        DSP_MW_LOG_I("fw_amp_init_semaphore create semaphore FAIL \n", 0);
    } else {
        xSemaphoreGive(amp_ctrl.semaphore);
    }
}
void fw_amp_init_timer (void)
{
    if (!amp_ctrl.timer) {
        amp_ctrl.timer = xTimerCreate("AMP_Timer", pdMS_TO_TICKS(FW_AMP_CLOSURE_TIMER), pdFALSE, 0, fw_amp_timer_callback);
        if(!amp_ctrl.timer) {
            DSP_MW_LOG_E("dsp amp timer start FAIL \n", 0);
        }
    }
}

void fw_amp_set_status(fw_amp_timer_status_t status)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    amp_ctrl.status = status;
    hal_nvic_restore_interrupt_mask(mask);
}


fw_amp_timer_status_t fw_amp_get_status(void)
{
    return amp_ctrl.status;
}



bool fw_amp_timer_start(void)
{
    if (fw_amp_get_status() == FW_AMP_TIMER_STOP) {
        fw_amp_set_status(FW_AMP_TIMER_START);
        xTimerChangePeriod(amp_ctrl.timer, pdMS_TO_TICKS(FW_AMP_CLOSURE_TIMER), 0);
        DSP_MW_LOG_I("DSP AMP fw_amp_timer_start \r\n", 0);
    } else {
        DSP_MW_LOG_I("DSP AMP timer existence !! \n", 0);
    }
    return false;
}


bool fw_amp_timer_stop(uint32_t samplerate)
{
    BaseType_t ret = pdPASS;
    bool result = true;
    if (xSemaphoreTake(amp_ctrl.semaphore, portMAX_DELAY) == pdTRUE) {
        if (fw_amp_get_status() == FW_AMP_TIMER_START) {
            DSP_MW_LOG_I("DSP AMP fw_amp_timer_stop \r\n", 0);
            ret = xTimerStop(amp_ctrl.timer, 0);
            if (samplerate != afe_get_audio_device_samplerate(HAL_AUDIO_DEVICE_DAC_DUAL, HAL_AUDIO_INTERFACE_NONE)) {
                afe_set_dac_enable(false);
                DSP_MW_LOG_I("DSP AMP fw_amp_timer_stop force dac disable !!\r\n", 0);
            } else {
                result = false;
            }
            if(ret == pdFAIL) {
                DSP_MW_LOG_E("DSP AMP timer stop FAIL\n", 0);
            }
            fw_amp_set_status(FW_AMP_TIMER_STOP);
        } else if (fw_amp_get_status() == FW_AMP_TIMER_END) {
            configASSERT(false);
        }
    } else {
        configASSERT(false);
    }
    xSemaphoreGive(amp_ctrl.semaphore);
    return result;
}

bool fw_amp_force_close(void)
{
    BaseType_t ret = pdPASS;
    bool result = false;
    //Close Amp while delay timer started.
    if (xSemaphoreTake(amp_ctrl.semaphore, portMAX_DELAY) == pdTRUE) {
        if (fw_amp_get_status() == FW_AMP_TIMER_START) {
            DSP_MW_LOG_I("DSP AMP fw_amp_force_stop \r\n", 0);
            ret = xTimerStop(amp_ctrl.timer, 0);
            fw_amp_set_status(FW_AMP_TIMER_END);
            // AMP close
            afe_audio_device_enable(false, HAL_AUDIO_DEVICE_DAC_DUAL, HAL_AUDIO_INTERFACE_NONE, HAL_AUDIO_MEM1, AFE_PCM_FORMAT_S32_LE, 48000, DOWNLINK_PERFORMANCE_NORMAL);
            afe_send_amp_status_ccni(false);
            result = true;
        }
    } else {
        configASSERT(false);
    }
    xSemaphoreGive(amp_ctrl.semaphore);
    return result;
}

#endif


#ifdef ENABLE_SIDETONE_RAMP_TIMER
static void fw_sidetone_timer_callback(TimerHandle_t xTimer)
{
    UNUSED(xTimer);
    bool is_increase = (sidetone_ctrl.current_gain<=sidetone_ctrl.target_gain) ? true : false;
    int32_t gain_step = (is_increase) ? FW_SIDETONE_RAMP_STEP : -(FW_SIDETONE_RAMP_STEP<<2);

    if (sidetone_ctrl.current_gain != sidetone_ctrl.target_gain) {
        if ((((sidetone_ctrl.target_gain - sidetone_ctrl.current_gain) > gain_step) && is_increase) ||
            (((sidetone_ctrl.target_gain - sidetone_ctrl.current_gain) < gain_step) && !is_increase))
        {
            sidetone_ctrl.current_gain += gain_step;
        }
        else
        {
            sidetone_ctrl.current_gain = sidetone_ctrl.target_gain;
        }
        afe_set_sidetone_volume(sidetone_ctrl.current_gain);
    } else {
        DSP_MW_LOG_E("DSP Sidetone ramp time-up gain:%d\n", 1, sidetone_ctrl.current_gain);
        if (!afe_get_sidetone_enable_flag()) {
            DTM_enqueue(DTM_EVENT_ID_SIDETONE_STOP, 0, false);
        }
        xTimerStop(sidetone_ctrl.timer, 0);
    }
}

void fw_sidetone_ramp_init (void)
{
    if (!sidetone_ctrl.timer) {
        sidetone_ctrl.timer = xTimerCreate("Sidetone_Timer", pdMS_TO_TICKS(FW_SIDETONE_RAMP_TIMER), pdTRUE, 0, fw_sidetone_timer_callback);
        if(!sidetone_ctrl.timer) {
            DSP_MW_LOG_E("DSP Sidetone ramp timer start FAIL \n", 0);
        }
    }
    sidetone_ctrl.current_gain = FW_SIDETONE_MUTE_GAIN;
    sidetone_ctrl.target_gain  = FW_SIDETONE_MUTE_GAIN;
}

void fw_sidetone_set_ramp_timer (int32_t target_gain)
{
    sidetone_ctrl.target_gain = target_gain;
    xTimerChangePeriod(sidetone_ctrl.timer, pdMS_TO_TICKS(FW_SIDETONE_RAMP_TIMER), 0);
    DSP_MW_LOG_I("DSP Sidetone ramp start %d to %d \r\n", 2, sidetone_ctrl.current_gain, sidetone_ctrl.target_gain);
}


#endif
