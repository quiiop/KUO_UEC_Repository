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

#if defined(UT_HAL_ENABLE) && defined (UT_HAL_DES_MODULE_ENABLE)

uint8_t des_key[24] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};

uint8_t des_plain[] = {
    0x82, 0x73, 0xE2, 0x04, 0xF1, 0x66, 0xFA, 0xE2, 0xEC, 0x50, 0xB4, 0xD8, 0x39, 0xAC, 0x03, 0x73,
    0xDC, 0x03, 0x44, 0xB8, 0x09, 0x3E, 0x4D, 0x12, 0xF2, 0x87, 0xB6, 0xE5, 0x9C, 0x81, 0x12, 0x39,
    0x15, 0x89, 0x0F, 0x2B, 0xD0, 0xC5, 0xDC, 0xA1, 0x64, 0x1B, 0x85, 0xC8, 0x40, 0x90, 0x5D, 0x81,
    0x50, 0xD5, 0xF9, 0xA1, 0x13, 0xB5, 0x55, 0x27, 0x82, 0x22, 0x3A, 0x04, 0x8F, 0x8C, 0x6E, 0x1F,
    0xCB, 0x5C, 0x80, 0x96, 0x2C, 0x2D, 0x23, 0x58, 0x89, 0x19, 0xB4, 0x12, 0x0A, 0x6E, 0x93, 0x14,
    0xD8, 0xAC, 0xE2, 0xB1, 0xCB, 0x22, 0x70, 0x96, 0xF6, 0xC3, 0x8E, 0xED, 0x2A, 0xC2, 0xD5, 0x55,
    0x7A, 0xB1, 0x1B, 0xF5, 0x15, 0x8B, 0x2B, 0x2B, 0x93, 0xC1, 0x22, 0x27, 0x56, 0xB4, 0x03, 0xAD,
    0xD3, 0xA8, 0xE4, 0xA7, 0x42, 0x49, 0xFF, 0x84, 0xDC, 0xEF, 0x90, 0xB9, 0xF3, 0xD7, 0xA6, 0xE7,
    0x6D, 0xE5, 0xBB, 0xDB, 0xA4, 0xDA, 0x56, 0x49, 0x28, 0x83, 0xB1, 0x51, 0x64, 0xBA, 0x0F, 0xC9,
    0x15, 0x46, 0xDD, 0x2A, 0xD0, 0xBC, 0x5E, 0xA1, 0xA2, 0xE6, 0x20, 0x45, 0x7D, 0x2A, 0x45, 0xFA,
    0xBE, 0x75, 0x42, 0x7C, 0x41, 0xA1, 0x05, 0x83, 0xFF, 0x4F, 0x3C, 0xFE, 0xB9, 0x46, 0x14, 0x72,
    0xB7, 0xDF, 0xAA, 0x6F, 0xB4, 0x55, 0xF2, 0x68, 0x78, 0x23, 0x21, 0xF0, 0x43, 0x46, 0x0D, 0x86,
    0x20, 0x76, 0x91, 0x40, 0x1C, 0x71, 0x97, 0x38, 0x7B, 0x0D, 0xA9, 0xF6, 0x94, 0x09, 0x76, 0x28,
    0x60, 0x28, 0x31, 0xC0, 0xE2, 0xBF, 0x1A, 0xC5, 0x1C, 0xDE, 0x71, 0x39, 0x3A, 0x62, 0x5F, 0x74,
    0x1E, 0x1C, 0x87, 0x3C, 0xD8, 0x6A, 0x6A, 0xB0, 0x31, 0x24, 0xD3, 0x62, 0x15, 0x21, 0x93, 0x2A,
    0xF0, 0xB1, 0x4E, 0xE1, 0x0A, 0xEC, 0x35, 0x15, 0xA1, 0x8B, 0xEE, 0x43, 0x0B, 0xE2, 0x9D, 0x17,
    0xC3, 0x36, 0x04, 0x86, 0x64, 0xB5, 0xE3, 0xC9, 0x60, 0xF6, 0x9D, 0xC1, 0x12, 0x97, 0xCB, 0x25,
    0xAD, 0x67, 0xE2, 0x5A, 0xC6, 0x9D, 0xA2, 0x8D, 0x16, 0x5B, 0x7B, 0x2C, 0x03, 0xD6, 0x27, 0x07,
    0xB8, 0xAD, 0xE6, 0x71, 0x06, 0x0A, 0x5D, 0x0C
};

uint8_t des_encrypted_ecb[] = {
    0xCA, 0xCD, 0xCF, 0x74, 0xA2, 0xC6, 0x73, 0xDE, 0xE2, 0xFE, 0xC4, 0xE6, 0x8F, 0x4E, 0x5C, 0xEE,
    0x1D, 0x65, 0x67, 0x5B, 0xD3, 0x3F, 0x32, 0x6E, 0xBF, 0x6B, 0xEE, 0x10, 0xAA, 0x7B, 0xCD, 0xFE,
    0xD3, 0x03, 0x61, 0x66, 0x18, 0x2D, 0x8B, 0x05, 0x77, 0x39, 0x9A, 0xE8, 0x40, 0x76, 0xC7, 0xF5,
    0xDC, 0xD0, 0x13, 0xFF, 0x25, 0x4B, 0x3D, 0x38, 0x3B, 0xD0, 0x72, 0xA0, 0x46, 0x21, 0x95, 0xF8,
    0x19, 0x4E, 0x45, 0x3D, 0x5C, 0x58, 0xB0, 0x63, 0xE6, 0x10, 0x12, 0x33, 0x43, 0xBB, 0xC8, 0x51,
    0xA9, 0x42, 0x50, 0x1A, 0x52, 0xA7, 0x95, 0xE2, 0xC7, 0x24, 0xF0, 0x2E, 0xC3, 0xD4, 0x53, 0xC7,
    0xA8, 0x7E, 0x72, 0xDA, 0x61, 0x38, 0xDE, 0x12, 0x37, 0x0F, 0xD0, 0x86, 0x93, 0xAD, 0x7F, 0x96,
    0x9E, 0x42, 0x97, 0xA1, 0xF4, 0x06, 0x44, 0x11, 0x9E, 0xAA, 0x9D, 0xC6, 0xE3, 0x24, 0xBC, 0x7C,
    0x09, 0x93, 0x48, 0x80, 0x34, 0x80, 0x2F, 0x01, 0x50, 0xB0, 0xDD, 0xF5, 0xE3, 0xA3, 0xA2, 0x9F,
    0x25, 0x60, 0x55, 0x8B, 0x8F, 0x1E, 0x01, 0xCF, 0x89, 0x10, 0x04, 0xD5, 0x34, 0xB2, 0x47, 0x36,
    0xA3, 0x0A, 0x72, 0xDF, 0x87, 0x47, 0x38, 0x77, 0x6E, 0x5A, 0x4D, 0x87, 0x24, 0x0F, 0xB7, 0x55,
    0x56, 0xAF, 0x78, 0xC3, 0x7B, 0x26, 0x94, 0xE2, 0x52, 0x17, 0x17, 0x13, 0xF1, 0x32, 0xDB, 0xF5,
    0xE2, 0x87, 0x8D, 0xB7, 0xDA, 0x29, 0x66, 0x2B, 0x0A, 0x93, 0x0D, 0x54, 0xEB, 0x98, 0x8F, 0xCB,
    0xE3, 0x2D, 0x15, 0x55, 0xC9, 0xC0, 0x00, 0x3C, 0xB6, 0xBF, 0x2C, 0x16, 0x3E, 0x82, 0xC5, 0xC3,
    0x37, 0x6D, 0x2A, 0x2D, 0xD4, 0x8C, 0x3A, 0x75, 0xCA, 0xAC, 0xE0, 0x46, 0x84, 0xBA, 0x4F, 0x51,
    0xCD, 0x48, 0xB3, 0x28, 0x9A, 0x26, 0xBB, 0x0B, 0x4D, 0xCF, 0x41, 0x98, 0xE8, 0x5C, 0x89, 0x9F,
    0x70, 0x6D, 0x58, 0xEE, 0xA1, 0x77, 0x2A, 0x46, 0x53, 0x99, 0x6E, 0x3F, 0xC3, 0x13, 0x96, 0x74,
    0x34, 0x4F, 0xB2, 0x47, 0x95, 0x03, 0x85, 0x3A, 0x1B, 0x65, 0x3F, 0x8E, 0x63, 0xCD, 0x56, 0xC7,
    0x53, 0xFD, 0xB1, 0xF7, 0x37, 0xE0, 0x92, 0xAC,
};

uint8_t des_encrypted[296] = {0};
uint8_t des_decrypted[296] = {0};

hal_des_buffer_t des_origin_text = {
    .buffer = des_plain,
    .length = sizeof(des_plain)
};

hal_des_buffer_t des_key_text = {
    .buffer = des_key,
    .length = sizeof(des_key)
};

hal_des_buffer_t des_encrypted_text = {
    .buffer = des_encrypted,
    .length = sizeof(des_encrypted)
};

hal_des_buffer_t des_decrypted_text = {
    .buffer = des_decrypted,
    .length = sizeof(des_decrypted)
};

uint8_t des_cbc_key[24] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xf1, 0xe0, 0xd3, 0xc2, 0xb5, 0xa4, 0x97, 0x86,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
};

uint8_t des_cbc_iv[HAL_DES_CBC_IV_LENGTH] = {
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
};

uint8_t des_cbc_plain[] = {
    0x1D, 0x06, 0x33, 0x3A, 0x9D, 0xCC, 0x60, 0x3B, 0x0A, 0xAA, 0x4B, 0x15, 0xBF, 0x23, 0x32, 0x7E,
    0x6C, 0x9C, 0x4B, 0xD9, 0x78, 0xD9, 0x9B, 0xF1, 0x26, 0x35, 0xFB, 0x4C, 0x31, 0x23, 0x07, 0x62,
    0x47, 0xB9, 0xA1, 0x8F, 0x4F, 0xA1, 0x55, 0x9F, 0xDB, 0xCD, 0x60, 0xB7, 0x7C, 0x6D, 0xA9, 0xF8,
    0xAE, 0x7D, 0x94, 0x5C, 0xCF, 0xC4, 0x56, 0x9F, 0x44, 0xDE, 0x37, 0x89, 0xAD, 0xCB, 0xC0, 0x5B,
    0xE8, 0x23, 0x3E, 0xD0, 0xA4, 0xAE, 0x32, 0x49, 0xA8, 0xC7, 0xFC, 0x51, 0xEB, 0xFE, 0xC0, 0xD7,
    0x06, 0x1D, 0x7F, 0x0C, 0x4B, 0x21, 0x2F, 0x96, 0x64, 0x57, 0xED, 0xC8, 0xE1, 0x2C, 0xCE, 0xC2,
    0x1E, 0xF2, 0xED, 0x3D, 0xBB, 0x82, 0x5A, 0x77, 0xBF, 0x05, 0x00, 0x7E, 0x09, 0x0C, 0xDB, 0x12,
    0x1C, 0xD9, 0xE7, 0x39, 0x36, 0xE5, 0x81, 0x6D, 0xE9, 0xEB, 0xF6, 0xD3, 0x0F, 0xD2, 0x8F, 0x1F,
    0xBC, 0x14, 0x88, 0x78, 0x42, 0xD9, 0x2F, 0x85, 0x24, 0x8B, 0x4B, 0x49, 0x2D, 0xDA, 0x59, 0x5B,
    0x15, 0x0C, 0xAF, 0x2A, 0x9F, 0xF2, 0xAE, 0x3F, 0xC3, 0x3F, 0x38, 0x86, 0x2C, 0x15, 0x63, 0x58,
    0xCE, 0x2F, 0xF2, 0x9C, 0xC7, 0x1A, 0x0C, 0x8E, 0x93, 0x7D, 0xBC, 0x26, 0x7D, 0x35, 0x99, 0xFA,
    0xD1, 0x8B, 0xB4, 0xA3, 0x39, 0x96, 0x17, 0x73, 0xD9, 0xD2, 0x92, 0xB3, 0x97, 0x99, 0xA8, 0x2F,
    0x22, 0x29, 0x0D, 0x44, 0xAF, 0xD8, 0x56, 0x5F, 0xE5, 0x9B, 0x36, 0xCB, 0x7B, 0xF8, 0xFD, 0xF7,
    0x2D, 0x28, 0xDB, 0x5A, 0xF3, 0x09, 0x1A, 0xE6, 0xF6, 0x82, 0xE2, 0xED, 0x14, 0xCF, 0xC1, 0x29,
    0xB2, 0x9F, 0xB6, 0x65, 0xED, 0x53, 0x6C, 0xDA, 0xEF, 0xBE, 0x94, 0xDF, 0xDA, 0x8A, 0xE2, 0xB5,
    0x22, 0x31, 0xFF, 0x44, 0x3C, 0xF1, 0x19, 0x79, 0x15, 0x09, 0x0B, 0x2A, 0xE8, 0x74, 0x0C, 0xD0,
    0x07, 0x6F, 0xCF, 0x0E, 0x55, 0xF6, 0xAD, 0xAB,
};

uint8_t des_encrypted_cbc[] = {
    0xAE, 0x4D, 0x98, 0x64, 0xDE, 0x5C, 0xD9, 0x1E, 0x65, 0x3D, 0xD8, 0x7A, 0xE1, 0x0A, 0x36, 0x80,
    0xD4, 0x55, 0xFD, 0xFA, 0x6C, 0x0C, 0x86, 0xF2, 0x4D, 0xCC, 0x9A, 0x66, 0x62, 0x9D, 0x2C, 0x65,
    0x6E, 0x75, 0x82, 0xD0, 0x42, 0x2F, 0x11, 0xE4, 0x90, 0xEE, 0x94, 0x9B, 0x9C, 0xF7, 0xAA, 0x9E,
    0x0A, 0xB5, 0x1A, 0xBE, 0x51, 0xCA, 0x0D, 0xA8, 0xC6, 0xA4, 0xF4, 0x05, 0x54, 0xB4, 0x4A, 0x70,
    0xDE, 0x64, 0xE6, 0x13, 0xF5, 0x87, 0xB3, 0xFF, 0x59, 0xE4, 0xEF, 0x7E, 0xC8, 0xB7, 0x91, 0x81,
    0x47, 0x88, 0x41, 0xC7, 0x6A, 0x75, 0xE8, 0xEF, 0xF4, 0xEC, 0xAE, 0xDD, 0xBC, 0x24, 0xCF, 0x37,
    0x71, 0x9B, 0x38, 0xE6, 0x7D, 0x5A, 0xA7, 0xE7, 0xAC, 0x3C, 0x91, 0x60, 0x4E, 0x56, 0xEB, 0x58,
    0x77, 0xC8, 0x3A, 0x09, 0xAB, 0x74, 0x0B, 0x73, 0x9A, 0xD4, 0xC3, 0xC2, 0xF1, 0xD4, 0xE8, 0x45,
    0x0E, 0x3B, 0x20, 0x71, 0x17, 0x8A, 0xA5, 0x28, 0xFA, 0x8A, 0x0C, 0x69, 0xFF, 0x10, 0x53, 0xB4,
    0xF3, 0x18, 0x50, 0xD6, 0x28, 0xF2, 0x83, 0x52, 0x6D, 0x34, 0xAF, 0xE6, 0xE2, 0x0C, 0x9E, 0xB0,
    0x4B, 0x49, 0xB0, 0x46, 0x96, 0xF3, 0xD8, 0xB4, 0x54, 0xEE, 0xE4, 0xC7, 0xA0, 0xB7, 0x0E, 0x84,
    0xBB, 0x83, 0x09, 0x4B, 0x6C, 0x72, 0xA8, 0xD1, 0xAB, 0x7C, 0x27, 0x85, 0x78, 0xC0, 0x1C, 0x44,
    0x62, 0x33, 0x93, 0x0A, 0xE7, 0xFE, 0x21, 0x55, 0xD4, 0x68, 0x37, 0x8D, 0x0F, 0x4D, 0x04, 0xF0,
    0x84, 0x9B, 0xBA, 0xE5, 0xD1, 0x77, 0x7A, 0xF0, 0xAC, 0x65, 0x05, 0xED, 0x12, 0x0E, 0xD8, 0x1D,
    0x24, 0xCD, 0xE9, 0xDA, 0x7D, 0x4D, 0xFC, 0x4A, 0x68, 0x82, 0x6D, 0x04, 0xDF, 0x61, 0x36, 0x46,
    0xA5, 0xAA, 0x44, 0xDA, 0x02, 0x2C, 0x45, 0x3E, 0xC2, 0x6E, 0xAC, 0xDC, 0x49, 0x2D, 0x1D, 0xF9,
    0x84, 0x53, 0xA0, 0x2B, 0x72, 0x71, 0xC6, 0x9A, 0xfe, 0x34, 0xfa, 0x35, 0x8a, 0x2d, 0x4e, 0x41,
    0x0e, 0xea, 0x6c, 0x29, 0xb2, 0x88, 0x08
};
uint8_t des_cbc_encrypted[264] = {0};
uint8_t des_cbc_decrypted[264] = {0};

hal_des_buffer_t des_cbc_origin_text = {
    .buffer = des_cbc_plain,
    .length = sizeof(des_cbc_plain)
};

hal_des_buffer_t des_cbc_key_text = {
    .buffer = des_cbc_key,
    .length = sizeof(des_cbc_key)
};

hal_des_buffer_t des_cbc_encrypted_text = {
    .buffer = des_cbc_encrypted,
    .length = sizeof(des_cbc_encrypted)
};

hal_des_buffer_t des_cbc_decrypted_text = {
    .buffer = des_cbc_decrypted,
    .length = sizeof(des_cbc_decrypted)
};

static void des_result_dump(uint8_t *result, uint8_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++) {
        if (i % 16 == 0) {
            printf("\r\n");
        }

        printf(" %02x ", result[i]);
    }
    printf("\r\n");

}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
ut_status_t ut_hal_des(void)
{
    hal_des_cbc_encrypt(&des_cbc_encrypted_text,
                        &des_cbc_origin_text,
                        &des_cbc_key_text,
                        des_cbc_iv);
    printf("Encrypted(DES CBC):");
    if (memcmp(des_cbc_encrypted_text.buffer, des_encrypted_cbc, des_cbc_encrypted_text.length)) {
        des_result_dump(des_cbc_encrypted_text.buffer, des_cbc_encrypted_text.length);
        printf("DES CBC encryption fail\r\n");
        return UT_STATUS_ERROR;
    } else {
        printf("DES CBC encryption success\r\n");
    }

    hal_des_cbc_decrypt(&des_cbc_decrypted_text,
                        &des_cbc_encrypted_text,
                        &des_cbc_key_text,
                        des_cbc_iv);
    printf("Decrypted(DES CBC):");
    if (memcmp(des_cbc_decrypted_text.buffer, des_cbc_plain, des_cbc_decrypted_text.length)) {
        des_result_dump(des_cbc_decrypted_text.buffer, des_cbc_decrypted_text.length);
        printf("DES CBC decryption fail\r\n");
        return UT_STATUS_ERROR;
    } else {
        printf("DES CBC decryption success\r\n");
    }

    hal_des_ecb_encrypt(&des_encrypted_text,
                        &des_origin_text,
                        &des_key_text);
    printf("Encrypted(DES ECB):");
    if (memcmp(des_encrypted_text.buffer, des_encrypted_ecb, des_encrypted_text.length)) {
        des_result_dump(des_encrypted_text.buffer, des_encrypted_text.length);
        printf("DES ECB encryption fail\r\n");
        return UT_STATUS_ERROR;
    } else {
        printf("DES ECB encryption success\r\n");
    }

    hal_des_ecb_decrypt(&des_decrypted_text,
                        &des_encrypted_text,
                        &des_key_text);
    printf("Decrypted(DES ECB):");
    if (memcmp(des_decrypted_text.buffer, des_plain, des_decrypted_text.length)) {
        des_result_dump(des_decrypted_text.buffer, des_decrypted_text.length);
        printf("DES ECB decryption fail\r\n");
        return UT_STATUS_ERROR;
    } else {
        printf("DES ECB decryption success\r\n");
    }

    return UT_STATUS_OK;
}
#endif /* #if defined(UT_HAL_ENABLE) && defined (UT_HAL_DES_MODULE_ENABLE) */
