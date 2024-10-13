/* Copyright (c) 2024 wimanshahb@gmail.com
 * All rights reserved.
 */

#ifndef AD4130_H
#define AD4130_H

#include <zephyr/kernel.h>

#include <stdint.h>

#include <stdint.h>

// Macro to flip (reverse) the endianness of 16-bit, 32-bit, and 64-bit integers
#define FLIP_ENDIANNESS_16(x) ((((x) & 0x00FF) << 8) | \
                               (((x) & 0xFF00) >> 8))

#define FLIP_ENDIANNESS_32(x) ((((x) & 0x000000FF) << 24) | \
                               (((x) & 0x0000FF00) << 8) |  \
                               (((x) & 0x00FF0000) >> 8) |  \
                               (((x) & 0xFF000000) >> 24))

#define FLIP_ENDIANNESS_64(x) ((((x) & 0x00000000000000FFULL) << 56) | \
                               (((x) & 0x000000000000FF00ULL) << 40) | \
                               (((x) & 0x0000000000FF0000ULL) << 24) | \
                               (((x) & 0x00000000FF000000ULL) << 8) |  \
                               (((x) & 0x000000FF00000000ULL) >> 8) |  \
                               (((x) & 0x0000FF0000000000ULL) >> 24) | \
                               (((x) & 0x00FF000000000000ULL) >> 40) | \
                               (((x) & 0xFF00000000000000ULL) >> 56))

// Generic macro to handle different sizes
#define FLIP_ENDIANNESS(x) (sizeof(x) == 2 ? FLIP_ENDIANNESS_16(x) : sizeof(x) == 4 ? FLIP_ENDIANNESS_32(x) \
                                                                 : sizeof(x) == 8   ? FLIP_ENDIANNESS_64(x) \
                                                                                    : (x))

typedef struct
{
    uint8_t ainp;   // Positive analog input channel (AINP)
    uint8_t ainm;   // Negative analog input channel (AINM)
    uint8_t setup;  // ADC setup (0-7)
    uint8_t enable; // Channel enable (1: enable, 0: disable)

    uint8_t thres_en; // Threshold enable (1: enable, 0: disable)
    uint8_t psdw_en;  // Power-down switch enable (1: enable, 0: disable)

    // New fields for IOUT channels
    uint8_t iout0; // IOUT0 channel selection (AIN0-AIN15 or other special channels)
    uint8_t iout1; // IOUT1 channel selection (AIN0-AIN15 or other special channels)
} ad4130_channel_cfg_t;

typedef enum
{
    AIN0 = 0x00,                  // 00000 AIN0
    AIN1 = 0x01,                  // 00001 AIN1
    AIN2 = 0x02,                  // 00010 AIN2
    AIN3 = 0x03,                  // 00011 AIN3
    AIN4 = 0x04,                  // 00100 AIN4
    AIN5 = 0x05,                  // 00101 AIN5
    AIN6 = 0x06,                  // 00110 AIN6
    AIN7 = 0x07,                  // 00111 AIN7
    AIN8 = 0x08,                  // 01000 AIN8
    AIN9 = 0x09,                  // 01001 AIN9
    AIN10 = 0x0A,                 // 01010 AIN10
    AIN11 = 0x0B,                 // 01011 AIN11
    AIN12 = 0x0C,                 // 01100 AIN12
    AIN13 = 0x0D,                 // 01101 AIN13
    AIN14 = 0x0E,                 // 01110 AIN14
    AIN15 = 0x0F,                 // 01111 AIN15
    TEMP_SENSOR = 0x10,           // 10000 Temperature Sensor
    AVSS = 0x11,                  // 10001 AVSS
    INTERNAL_REFERENCE = 0x12,    // 10010 Internal Reference
    DGND = 0x13,                  // 10011 DGND
    AVDD_AVSS_DIV6_PLUS = 0x14,   // 10100 (AVDD − AVSS)/6+
    AVDD_AVSS_DIV6_MINUS = 0x15,  // 10101 (AVDD − AVSS)/6−
    IOVDD_DGND_DIV6_PLUS = 0x16,  // 10110 (IOVDD − DGND)/6+
    IOVDD_DGND_DIV6_MINUS = 0x17, // 10111 (IOVDD − DGND)/6−
    ALDO_AVSS_DIV6_PLUS = 0x18,   // 11000 (ALDO − AVSS)/6+
    ALDO_AVSS_DIV6_MINUS = 0x19,  // 11001 (ALDO − AVSS)/6−
    DLDO_DGND_DIV6_PLUS = 0x1A,   // 11010 (DLDO − DGND)/6+
    DLDO_DGND_DIV6_MINUS = 0x1B   // 11011 (DLDO − DGND)/6−
} ad4130_input_t;

/**
 * @brief initialize the ad4130 driver with dt instance
 * @return int 0 on sucsess or error number
 */
int ad4130_init(void);

/**
 * @brief return the id of the ad4130 device
 *
 */
void ad4130_get_id(void);

/**
 * @brief setting up adc
 *
 */
void ad4130_settup(void);

/**
 * @brief function to settup channels using struct
 *
 * @param channel_num
 * @param cfg struct channel configuration
 * @return int 0 on sucsess
 */
int ad4130_init_channel(uint8_t channel_num, const ad4130_channel_cfg_t *cfg);
#endif