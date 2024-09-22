/* Copyright (c) 2024 wimanshahb@gmail.com
 * All rights reserved.
 */

#include "ad4130.h"
#include "ad4130_reg.h"

#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT ad_ad4130

LOG_MODULE_REGISTER(ad4130_dev, LOG_LEVEL_DBG);

/* DT INSTANCE BASED VARIABLE*/
#define AD4130_PARENT_NODE DT_INST_PARENT(0)

// for spi base driver
#if DT_HAS_COMPAT_ON_BUS_STATUS_OKAY(ad_ad4130, spi)
struct spi_config         spi_cfg;
const struct gpio_dt_spec cs_spec = GPIO_DT_SPEC_GET(AD4130_PARENT_NODE, cs_gpios);
struct spi_cs_control     ctrl;
#endif

const struct device *ad4130_dev;

/**
 * @brief initialize the ad4130 driver with dt instance
 * @return int 0 on sucsess or error number
 */
int ad4130_init(void) {

// for spi
#if DT_HAS_COMPAT_ON_BUS_STATUS_OKAY(ad_ad4130, spi)
    ad4130_dev = DEVICE_DT_GET(AD4130_PARENT_NODE);

    if ((ad4130_dev == NULL) || (!device_is_ready(ad4130_dev))) {
        LOG_ERR("bus error");
        return -EIO;
    }

    ctrl.gpio         = cs_spec;
    ctrl.delay        = 2;
    spi_cfg.frequency = DT_PROP(DT_DRV_INST(0), spi_max_frequency);
    spi_cfg.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_TRANSFER_LSB;
    spi_cfg.cs        = ctrl;

#endif // for spi

    return 0;
}

/**
 * @brief basic read function
 *
 * @param reg AD4130 register
 * @param data[out] buffer that need to store results from AD4130
 * @param len length of the data 1-4 (8bit to 32bits)
 * @return int 0 in sucsess or error number
 */
static int ad4130_read_register(uint8_t reg, uint8_t *data, size_t len) {
    uint8_t command = (reg | AD4130_COMMS_RD); //  command that need to send for read

    // buffers for spi

    // 1. first need to send command
    const struct spi_buf tx_bufs[] = {

        {.buf = &command, .len = 1}};

    // 2. need to capture the MISO line. we going to do this in two seperate buffer and discard the
    // first buffer so no need to worry about extra bit manipulation
    const struct spi_buf rx_bufs[] = {
        {.buf = NULL, len = 1},
        {.buf = data, len = len},
    };

    // setting buffers for spi
    const struct spi_buf_set tx = {
        .buffers = tx_bufs,
        .count   = ARRAY_SIZE(tx_bufs),
    };

    const struct spi_buf_set rx = {
        .buffers = rx_bufs,
        .count   = ARRAY_SIZE(rx_bufs),
    };

    return spi_transceive(ad4130_dev, &spi_cfg, &tx, &rx);
}

/**
 * @brief basic write function
 *
 * @param reg ad4130 register
 * @param data[in] data that need to transwer to ad4130
 * @param len length of the data
 * @return int 0 on sucsess, else erorr number
 */
static int ad4130_write_register(uint8_t reg, uint8_t *data, size_t len) {

    // since the idea was to send the LSB first,last byte should be the command
    // spi_cfg.operation  =|SEND_LSB_FIRST

    uint8_t tx_data_buffer[len + 1];
    tx_data_buffer[len] = (AD4130_COMMS_RS(reg) | 0x00); //  command that need to send for write
    memcpy(tx_data_buffer, data, len);

    // buffers for spi

    // 1. send the tr buffer
    const struct spi_buf tx_bufs[] = {

        {.buf = tx_data_buffer, .len = len + 1}};

    // setting buffers for spi
    const struct spi_buf_set tx = {
        .buffers = tx_bufs,
        .count   = ARRAY_SIZE(tx_bufs),
    };

    return spi_write(ad4130_dev, &spi_cfg, &tx);
}

/**
 * @brief return the id of the ad4130 device
 *
 */
void ad4130_get_id(void) {
    uint8_t device_id = 0;
    ad4130_read_register(AD4130_ID_REG, &device_id, 1);
    printk("device id is %x", device_id);
}

/**
 * @brief setting up adc
 *
 */
void ad4130_settup(void) {
    uint32_t channel_config = 0;
    channel_config          = AD4130_CHANNEL_ENABLE | ;
}