/* Copyright (c) 2024 wimanshahb@gmail.com
 * All rights reserved.
 */

#include "ad4130.h"
#include "ad4130_reg.h"

#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT ad_ad4130
#define AD4130_CHANNEL_COUNT 8 // Assume we have 8 channels for simplicity

LOG_MODULE_REGISTER(ad4130_dev, LOG_LEVEL_DBG);

/* DT INSTANCE BASED VARIABLE*/
#define AD4130_PARENT_NODE DT_INST_PARENT(0)

// for spi base driver
#if DT_HAS_COMPAT_ON_BUS_STATUS_OKAY(ad_ad4130, spi)
struct spi_config spi_cfg;
const struct gpio_dt_spec cs_spec = GPIO_DT_SPEC_GET(AD4130_PARENT_NODE, cs_gpios);
struct spi_cs_control ctrl;
#endif

const struct device *ad4130_dev;

/**
 * @brief initialize the ad4130 driver with dt instance
 * @return int 0 on sucsess or error number
 */
int ad4130_init(void)
{

// for spi
#if DT_HAS_COMPAT_ON_BUS_STATUS_OKAY(ad_ad4130, spi)
    ad4130_dev = DEVICE_DT_GET(AD4130_PARENT_NODE);

    if ((ad4130_dev == NULL) || (!device_is_ready(ad4130_dev)))
    {
        LOG_ERR("bus error");
        return -EIO;
    }

    ctrl.gpio = cs_spec;
    ctrl.delay = 1;
    spi_cfg.frequency = DT_PROP(DT_DRV_INST(0), spi_max_frequency);
    spi_cfg.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_TRANSFER_MSB | SPI_LINES_SINGLE;
    spi_cfg.cs = ctrl;

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
static int ad4130_read_register(uint8_t reg, uint8_t *data, size_t _len)
{
    uint8_t command = (reg | AD4130_COMMS_RD); //  command that need to send for read

    // buffers for spi

    // 1. first need to send command
    const struct spi_buf tx_bufs[] = {

        {.buf = &command, .len = 1}};

    // 2. need to capture the MISO line. we going to do this in two seperate buffer and discard the
    // first buffer so no need to worry about extra bit manipulation
    const struct spi_buf rx_bufs[] = {
        {.buf = NULL, .len = 1},
        {.buf = data, .len = _len},
    };

    // setting buffers for spi
    const struct spi_buf_set tx = {
        .buffers = tx_bufs,
        .count = ARRAY_SIZE(tx_bufs),
    };

    const struct spi_buf_set rx = {
        .buffers = rx_bufs,
        .count = 2,
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
static int ad4130_write_register(uint8_t reg, uint8_t *data, size_t len)
{

    uint8_t tx_data_buffer[len + 1];
    tx_data_buffer[0] = (AD4130_COMMS_RS(reg) | 0x00); //  command that need to send for write
    memcpy(tx_data_buffer + 1, data, len);
    LOG_HEXDUMP_INF(tx_data_buffer, sizeof(tx_data_buffer), "data");

    // buffers for spi

    // 1. send the tr buffer
    const struct spi_buf tx_bufs[] = {

        {.buf = tx_data_buffer, .len = len + 1}};

    // setting buffers for spi
    const struct spi_buf_set write_tx = {
        .buffers = tx_bufs,
        .count = ARRAY_SIZE(tx_bufs),
    };
    return spi_write(ad4130_dev, &spi_cfg, &write_tx);
}

/**
 * @brief return the id of the ad4130 device
 *
 */
void ad4130_get_id(void)
{
    uint8_t device_id = 0;
    ad4130_read_register(AD4130_ID_REG, &device_id, 1);
    printk("device id is %x \n", device_id);
}

/**
 * @brief function to settup channels using struct
 *
 * @param channel_num
 * @param cfg struct channel configuration
 * @return int 0 on sucsess
 */
// Function to initialize a channel with given configuration
int ad4130_init_channel(uint8_t channel_num, const ad4130_channel_cfg_t *cfg)
{
    if (channel_num >= AD4130_CHANNEL_COUNT)
    {
        return -1; // Invalid channel number
    }

    // Configure CHANNELn register
    uint32_t channel_reg = 0;

    // Enable the channel
    if (cfg->enable)
    {
        channel_reg |= AD4130_CHANNEL_ENABLE;
    }

    // Configure the setup
    channel_reg |= AD4130_CHANNEL_SETUP(cfg->setup);

    // Configure AINP and AINM
    channel_reg |= AD4130_CHANNEL_AINP(cfg->ainp);
    channel_reg |= AD4130_CHANNEL_AINM(cfg->ainm);

    // Configure THRES_EN (Threshold Enable)
    if (cfg->thres_en)
    {
        channel_reg |= AD4130_CHANNEL_THRES_EN;
    }

    // Configure PSDW_EN (Power-Down Switch)
    if (cfg->psdw_en)
    {
        channel_reg |= AD4130_CHANNEL_PSDW_EN;
    }

    // Configure IOUT0 and IOUT1 channels (based on bitfields in the image)
    channel_reg |= AD4130_CHANNEL_IOUT0(cfg->iout0);
    channel_reg |= AD4130_CHANNEL_IOUT1(cfg->iout1);

    channel_reg = FLIP_ENDIANNESS(channel_reg);

    // Write the CHANNELn register (assuming CHANNELn registers start at 0x09)
    uint32_t channel_reg_address = 0x09 + channel_num;
    printk("%x\n", channel_reg);
    ad4130_write_register(channel_reg_address, (uint8_t *)&channel_reg, sizeof(channel_reg));

    uint8_t data_rx[4] = {0, 0, 0, 0};

    ad4130_read_register(channel_reg_address, data_rx, 4);
    LOG_HEXDUMP_INF(data_rx, 4, "datarx");

    return 0; // Success
}
