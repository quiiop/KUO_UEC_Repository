/* Copyright Statement:
 *
 * (C) 2005-2030  MediaTek Inc. All rights reserved.
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
#include "ut.h"

#if defined(UT_HAL_ENABLE) && defined (UT_HAL_I2C_MASTER_MODULE_ENABLE)
#include <hal_i2c_master.h>
#include <hal_gpio.h>
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
ut_status_t ut_hal_i2c_master(void)
{
    hal_i2c_config_t i2c_config;
    uint8_t slave_address = 0x50;
    uint8_t read_len = 8;
    //the data that used to send
    const uint8_t send_data[10] = {0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint8_t receive_data[8] = {0};
    volatile uint32_t size = 10;
    i2c_config.frequency = HAL_I2C_FREQUENCY_400K;
    hal_i2c_send_to_receive_config_t i2c_send_to_receive_config;
    int ret, i;

    /************* 1 init i2c-0 and i2c-1****************************************************************************************************/

    i2c_send_to_receive_config.slave_address = slave_address;
    i2c_send_to_receive_config.send_data = send_data;
    i2c_send_to_receive_config.send_length = 2;
    i2c_send_to_receive_config.receive_buffer = receive_data;
    i2c_send_to_receive_config.receive_length = read_len;

    hal_gpio_init(HAL_GPIO_23);  //sda-0
    hal_gpio_init(HAL_GPIO_24);  //scl-0
    hal_gpio_init(HAL_GPIO_20);  //scl-1
    hal_gpio_init(HAL_GPIO_19);  //sda-1

    hal_pinmux_set_function(HAL_GPIO_23, 3);
    hal_pinmux_set_function(HAL_GPIO_24, 3);
    hal_pinmux_set_function(HAL_GPIO_20, 3);
    hal_pinmux_set_function(HAL_GPIO_19, 3);

    hal_gpio_set_pupd_register(HAL_GPIO_23, 1, 0, 0);
    hal_gpio_set_pupd_register(HAL_GPIO_24, 1, 0, 0);
    hal_gpio_set_pupd_register(HAL_GPIO_19, 1, 0, 0);
    hal_gpio_set_pupd_register(HAL_GPIO_20, 1, 0, 0);

    hal_gpio_set_driving_current(HAL_GPIO_23, HAL_GPIO_DRIVING_CURRENT_10MA);
    hal_gpio_set_driving_current(HAL_GPIO_24, HAL_GPIO_DRIVING_CURRENT_10MA);
    hal_gpio_set_driving_current(HAL_GPIO_19, HAL_GPIO_DRIVING_CURRENT_10MA);
    hal_gpio_set_driving_current(HAL_GPIO_20, HAL_GPIO_DRIVING_CURRENT_10MA);

    hal_nvic_init();

    ret = hal_i2c_master_init(HAL_I2C_MASTER_0, &i2c_config);
    if (ret) {
        printf("i2c-0 hal_i2c_master_init failed!\n");
        goto test_error;
    }
    ret = hal_i2c_master_init(HAL_I2C_MASTER_1, &i2c_config);
    if (ret) {
        printf("i2c-1 hal_i2c_master_init failed!\n");
        goto test_error;
    }

    /************* 2 test dma mode write ***********************************************************************************/

    ret = hal_i2c_master_send_dma(HAL_I2C_MASTER_0, slave_address, send_data, size);
    if (ret) {
        printf("i2c-0 hal_i2c_master_send_dma failed!\n");
        goto test_error;
    }
    printf("i2c-0 hal_i2c_master_send_dma successfuly\n");

    ret = hal_i2c_master_send_dma(HAL_I2C_MASTER_1, slave_address, send_data, size);
    if (ret) {
        printf("i2c-1 hal_i2c_master_send_dma failed!\n");
        goto test_error;
    }
    printf("i2c-1 hal_i2c_master_send_dma successfuly\n");

    /************* 3 test dma mode read ************************************************************************************/
    hal_gpt_delay_ms(50);
    ret = hal_i2c_master_send_to_receive_dma(HAL_I2C_MASTER_0, &i2c_send_to_receive_config);
    if (ret) {
        printf("i2c-0 hal_i2c_master_send_to_receive_dma failed!\n");
        goto test_error;
    }

    //check the data read back with dma mode
    for (i = 0; i < read_len; i++) {
        if (send_data[2 + i] != receive_data[i]) {
            printf("i2c-0 read data failed with dma mode data-%d = 0x%x\n", i, receive_data[i]);
            goto test_error;
        }
    }
    printf("i2c-0 hal_i2c_master_send_to_receive_dma successfuly!\n");

    memset(receive_data, 0, sizeof(receive_data));

    ret = hal_i2c_master_send_to_receive_dma(HAL_I2C_MASTER_1, &i2c_send_to_receive_config);
    if (ret) {
        printf("i2c-1 hal_i2c_master_send_to_receive_dma failed!\n");
        goto test_error;
    }

    //check the data read back with dma mode
    for (i = 0; i < read_len; i++) {
        if (send_data[2 + i] != receive_data[i]) {
            printf("i2c-1 read data failed with dma mode data-%d = 0x%x\n", i, receive_data[i]);
            goto test_error;
        }
    }
    printf("i2c-1 hal_i2c_master_send_to_receive_dma successfuly!\n");

    /************* 4 test polling mode write ************************************************************************************/
    hal_gpt_delay_ms(50);
    ret = hal_i2c_master_send_polling(HAL_I2C_MASTER_0, slave_address, send_data, size);
    if (ret) {
        printf("i2c-0 hal_i2c_master_send_polling failed!\n");
        goto test_error;
    }
    printf("i2c-0 hal_i2c_master_send_polling successfuly!\n");
    ret = hal_i2c_master_send_polling(HAL_I2C_MASTER_1, slave_address, send_data, size);
    if (ret) {
        printf("i2c-1 hal_i2c_master_send_polling failed!\n");
        goto test_error;
    }
    printf("i2c-1 hal_i2c_master_send_polling successfuly!\n");

    /************* 5 test poling mode read ************************************************************************************/
    hal_gpt_delay_ms(50);
    memset(receive_data, 0, sizeof(receive_data));
    ret = hal_i2c_master_send_to_receive_polling(HAL_I2C_MASTER_0, &i2c_send_to_receive_config);
    if (ret) {
        printf("i2c-0 hal_i2c_master_send_to_receive_polling failed!\n");
        goto test_error;
    }

    //check the data read back with polling mode
    for (i = 0; i < read_len; i++) {
        if (send_data[2 + i] != receive_data[i]) {
            printf("i2c-0 read data failed with polling mode data-%d = 0x%x\n", i, receive_data[i]);
            goto test_error;
        }
    }
    printf("i2c-0 hal_i2c_master_send_to_receive_polling successfuly!\n");

    memset(receive_data, 0, sizeof(receive_data));
    ret = hal_i2c_master_send_to_receive_polling(HAL_I2C_MASTER_1, &i2c_send_to_receive_config);
    if (ret) {
        printf("i2c-1 hal_i2c_master_send_to_receive_polling failed!\n");
        goto test_error;
    }
    //check the data read back with poling mode
    for (i = 0; i < read_len; i++) {
        if (send_data[2 + i] != receive_data[i]) {
            printf("i2c-1 read data failed with poling mode data-%d = 0x%x\n", i, receive_data[i]);
            goto test_error;
        }
    }
    printf("i2c-1 hal_i2c_master_send_to_receive_polling successfuly!\n");

    /************* 6 deinit i2c ************************************************************************************/

    hal_i2c_master_deinit(HAL_I2C_MASTER_0);
    hal_i2c_master_deinit(HAL_I2C_MASTER_1);

    return UT_STATUS_OK;
test_error:
    return UT_STATUS_ERROR;
}

#endif /* #if defined(UT_HAL_ENABLE) && defined (UT_HAL_I2C_MASTER_MODULE_ENABLE) */
