/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Modifications are Copyright (c) 2019 Arm Limited.
 */

#ifndef H_IMAGE_
#define H_IMAGE_

#include <inttypes.h>
#include <stdbool.h>

#ifdef __ZEPHYR__
#include <toolchain/gcc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct flash_area;

#define IMAGE_MAGIC                 0xbd9fc018
#define IMAGE_MAGIC_V1              0x96f3b83c
#define IMAGE_MAGIC_NONE            0xffffffff
#define IMAGE_TLV_INFO_MAGIC        0x5676
#define IMAGE_TLV_PROT_INFO_MAGIC   0x5677

#define IMAGE_HEADER_SIZE           32

/*
 * Image header flags.
 */
#define IMAGE_F_PIC                      0x00000001 /* Not supported. */
#define IMAGE_F_NON_BOOTABLE             0x00000010 /* Split image app. */
#define IMAGE_F_ENCRYPTED                0x00000004 /* Encrypted. */
#define IMAGE_F_SCTRL_CERT               0x00000100 /* SCTRL CERT */
#define IMAGE_F_TOOL_AUTH                0x00000200 /* TOOL AUTH */
/*
 * Indicates that this image should be loaded into RAM instead of run
 * directly from flash.  The address to load should be in the
 * ih_load_addr field of the header.
 */
#define IMAGE_F_RAM_LOAD                 0x00000020

/*
 * ECSDA224 is with NIST P-224
 * ECSDA256 is with NIST P-256
 */

/*
 * Image trailer TLV types.
 *
 * Signature is generated by computing signature over the image hash.
 * Currently the only image hash type is SHA256.
 *
 * Signature comes in the form of 2 TLVs.
 *   1st on identifies the public key which should be used to verify it.
 *   2nd one is the actual signature.
 */
#define IMAGE_TLV_KEYHASH           0x01   /* hash of the public key */
#define IMAGE_TLV_SHA256            0x10   /* SHA256 of image hdr and body */
#define IMAGE_TLV_RSA2048_PSS       0x20   /* RSA2048 of hash output */
#define IMAGE_TLV_ECDSA224          0x21   /* ECDSA of hash output */
#define IMAGE_TLV_ECDSA256          0x22   /* ECDSA of hash output */
#define IMAGE_TLV_RSA3072_PSS       0x23   /* RSA3072 of hash output */
#define IMAGE_TLV_ED25519           0x24   /* ed25519 of hash output */
#define IMAGE_TLV_ENC_RSA2048       0x30   /* Key encrypted with RSA-OAEP-2048 */
#define IMAGE_TLV_ENC_KW128         0x31   /* Key encrypted with AES-KW-128 */
#define IMAGE_TLV_ENC_EC256         0x32   /* Key encrypted with ECIES-EC256 */
#define IMAGE_TLV_DEPENDENCY        0x40   /* Image depends on other image */
#define IMAGE_TLV_PUB_KEY           0x60   /* Public key */
#define IMAGE_TLV_JTAG_EN           0x61   /* JTAG debug port enable*/
#define IMAGE_TLV_JTAG_PW           0x62   /* JTAG enable password */
#define IMAGE_TLV_MEID              0x63   /* MEID */
#define IMAGE_TLV_AR_VER            0x64   /* Version for Anti-rollback */
#define IMAGE_TLV_DAA_PUBKEY        0x65   /* Public key for DAA */
#define IMAGE_TLV_DA_HASH           0x66   /* HASH value of DA */
#define IMAGE_TLV_CUST_NAME         0x67   /* Customer Name */
#define IMAGE_TLV_BL_SECURE_ATTR    0x71   /* Bootloader Secure Attribute */
#define IMAGE_TLV_SCTRL_CERT_ATTR   0x80   /* SCTRL CERT Attribute */
#define IMAGE_TLV_TOOL_AUTH_ATTR    0x90   /* TOOL AUTH Attribute */
#define IMAGE_TLV_ANY               0xffff /* Used to iterate over all TLV */

struct image_version {
    uint8_t iv_major;
    uint8_t iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
};

struct image_dependency {
    uint8_t image_id;                       /* Image index (from 0) */
    uint8_t _pad1;
    uint16_t _pad2;
    struct image_version image_min_version; /* Indicates at minimum which
                                             * version of firmware must be
                                             * available to satisfy compliance
                                             */
};

/** Image header.  All fields are in little endian byte order. */
struct image_header {
    uint32_t ih_magic;
    uint32_t ih_load_addr;
    uint16_t ih_hdr_size;           /* Size of image header (bytes). */
    uint16_t ih_protect_tlv_size;   /* Size of protected TLV area (bytes). */
    uint32_t ih_img_size;           /* Does not include header. */
    uint32_t ih_flags;              /* IMAGE_F_[...]. */
    struct image_version ih_ver;
    uint32_t _pad1;
};

/** Image TLV header.  All fields in little endian. */
struct image_tlv_info {
    uint16_t it_magic;
    uint16_t it_tlv_tot;  /* size of TLV area (including tlv_info header) */
};

/** Image trailer TLV format. All fields in little endian. */
struct image_tlv {
    uint16_t it_type;   /* IMAGE_TLV_[...]. */
    uint16_t it_len;    /* Data length (not including TLV header). */
};

#define IS_ENCRYPTED(hdr) ((hdr)->ih_flags & IMAGE_F_ENCRYPTED)
#define MUST_DECRYPT(fap, idx, hdr) \
    ((fap)->fa_id == FLASH_AREA_IMAGE_SECONDARY(idx) && IS_ENCRYPTED(hdr))

#ifdef __ZEPHYR__
BUILD_ASSERT_MSG(sizeof(struct image_header) == IMAGE_HEADER_SIZE,
               "struct image_header not required size");
#else
_Static_assert(sizeof(struct image_header) == IMAGE_HEADER_SIZE,
               "struct image_header not required size");
#endif

struct enc_key_data;
int bootutil_img_validate(struct enc_key_data *enc_state, int image_index,
                          struct image_header *hdr,
                          const struct flash_area *fap,
                          uint8_t *tmp_buf, uint32_t tmp_buf_sz,
                          uint8_t *seed, int seed_len, uint8_t *out_hash);

struct image_tlv_iter {
    const struct image_header *hdr;
    const struct flash_area *fap;
    uint16_t type;
    bool prot;
    uint32_t prot_end;
    uint32_t tlv_off;
    uint32_t tlv_end;
};

int bootutil_tlv_iter_begin(struct image_tlv_iter *it,
                            const struct image_header *hdr,
                            const struct flash_area *fap, uint16_t type,
                            bool prot);
int bootutil_tlv_iter_next(struct image_tlv_iter *it, uint32_t *off,
                           uint16_t *len, uint16_t *type);

#ifdef __cplusplus
}
#endif

#endif
