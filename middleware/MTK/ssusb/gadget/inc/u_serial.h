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
 * MediaTek Inc. (C) 2010. All rights reserved.
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

#ifndef __USB_TTY_H__
#define __USB_TTY_H__

#include "mtu3.h"
#include "usbdcore.h"
#include "usbd.h"

#define NUM_INTERFACES  2
#define NUM_ENDPOINTS   3

/* hardware endpoint arrange */
#define ACM_BULK_OUT_EP   1
#define ACM_BULK_IN_EP    2
#define ACM_INT_IN_EP     3

#define NUM_CONFIGS 1
#define NUM_COMM_INTERFACES 1
#define NUM_DATA_INTERFACES 1
#define NUM_DIAG_INTERFACES 1
#define NUM_COMM_ENDPOINTS  1
#define NUM_DATA_ENDPOINTS  2
#define NUM_DIAG_ENDPOINTS  2

#define EP0_MAX_PACKET_SIZE_U2_EXP 0x06
#define EP0_MAX_PACKET_SIZE (0x40) /* (2^EP0_MAX_PACKET_SIZE_U2_EXP) 64 */

#define EP0_MAX_PACKET_SIZE_U3_EXP 0x09
#define EP0_MAX_PACKET_SIZE_U3 (0x200) /* (2^EP0_MAX_PACKET_SIZE_U3_EXP) 512 */

#define USBD_VENDORID                   (0x0E8D)
#define USBD_PRODUCTID                  (0x0003)

#define USBD_MANUFACTURER               "MediaTek"
#define USBD_PRODUCT_NAME               "VCOM"

#define USBD_CONFIGURATION_STR      "USB CDC ACM for preloader"
#define USBD_DATA_INTERFACE_STR     "CDC ACM Data Interface"
#define USBD_COMM_INTERFACE_STR     "CDC ACM Comm Interface"
#define USBD_DIAG_INTERFACE_STR     "Serial Interface"
#define CLASS_NAME                  "acm"
#define USBD_SERIAL_OUT_ENDPOINT    1
#define USBD_SERIAL_OUT_SS_PKTSIZE  1024
#define USBD_SERIAL_OUT_HS_PKTSIZE  512
#define USBD_SERIAL_OUT_FS_PKTSIZE  64

#define USBD_SERIAL_IN_ENDPOINT     1
#define USBD_SERIAL_IN_SS_PKTSIZE   1024
#define USBD_SERIAL_IN_HS_PKTSIZE   512
#define USBD_SERIAL_IN_FS_PKTSIZE   64

#define USBD_INT_IN_ENDPOINT        3
#define USBD_INT_IN_SS_PKTSIZE      64
#define USBD_INT_IN_HS_PKTSIZE      64
#define USBD_INT_IN_FS_PKTSIZE      64

#define USBDL_DEVICE_CLASS      0x02
#define USBDL_DEVICE_SUBCLASS   0x00
#define USBDL_DEVICE_PROTOCOL   0x00

/* communication interface class */
#define USBDL_COMM_INTERFACE_CLASS     0x02
#define USBDL_COMM_INTERFACE_SUBCLASS  0x02     /* Abstract Control Model subclass */
#define USBDL_COMM_INTERFACE_PROTOCOL  0x01     /* uses the Common AT commands Protocol */

/* data interface class */
#define USBDL_DATA_INTERFACE_CLASS    0x0a
#define USBDL_DATA_INTERFACE_SUBCLASS 0x00
#define USBDL_DATA_INTERFACE_PROTOCOL 0x00

/* DIAG serial interface class */
#define USBDL_DIAG_INTERFACE_CLASS    0xFF
#define USBDL_DIAG_INTERFACE_SUBCLASS 0xFF
#define USBDL_DIAG_INTERFACE_PROTOCOL 0x00

#define USBD_BCD_DEVICE 0x0100
#define USBD_MAXPOWER       0xfa    /* 2-mA units in HS */
#define USBD_SS_MAXPOWER    0x32    /* 8-mA units in SS */

#define STR_MANUFACTURER    1
#define STR_PRODUCT         2
#define STR_CONFIG          3
#define STR_DATA_INTERFACE  4
#define STR_COMM_INTERFACE  5
#define STR_ISERIAL         6
#define STR_DIAG_INTERFACE  7

/* CDC ACM Class-specific requests */
#define CDCACM_REQ_SET_LINE_CODING           0x20
#define CDCACM_REQ_GET_LINE_CODING           0x21
#define CDCACM_REQ_SET_CONTROL_LINE_STATE    0x22
#define CDCACM_REQ_SEND_BREAK                0x23

/* timeout of usb enumeration to avoid system hang when enum fail */
#define USB_ENUM_TIMEOUT            (CFG_USB_ENUM_TIMEOUT)

/* Buffers to hold input and output data */
#define USBTTY_BUFFER_SIZE 1024

/* Descriptors used by CDC ACM */
struct cdcacm_class_header_function_descriptor {
    unsigned char bFunctionLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned short bcdCDC;
} __attribute__((packed));

struct cdcacm_class_call_management_descriptor {
    unsigned char bFunctionLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bmCapabilities;
    unsigned char bDataInterface;
} __attribute__((packed));

struct cdcacm_class_abstract_control_descriptor {
    unsigned char bFunctionLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bmCapabilities;
} __attribute__((packed));

struct cdcacm_class_union_function_descriptor {
    unsigned char bFunctionLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bMasterInterface;
    unsigned char bSlaveInterface0;
} __attribute__((packed));

struct mt_altsetting {
    struct interface_descriptor *p_interface_desc;
    /* communication class specific interface descriptors */
    /* only communication interfaces have these fields */
    struct cdcacm_class_header_function_descriptor *p_header_function_desc;
    struct cdcacm_class_abstract_control_descriptor *p_abstract_control_desc;
    struct cdcacm_class_union_function_descriptor *p_union_function_desc;
    struct cdcacm_class_call_management_descriptor *p_call_management_desc;
    int endpoints;
    struct endpoint_descriptor **pp_eps_desc_array;
    struct ss_ep_comp_descriptor **p_ss_ep_comp_desc;
};

struct usb_acm_line_coding {
    unsigned int dwDTERate;
    unsigned char bCharFormat;
    unsigned char bParityType;
    unsigned char bDataBits;
} __attribute__((packed));

#endif /* #ifndef __USB_TTY_H__ */
