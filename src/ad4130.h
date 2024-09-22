/* Copyright (c) 2024 wimanshahb@gmail.com
 * All rights reserved.
 */

#ifndef AD4130_H
#define AD4130_H

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
#endif