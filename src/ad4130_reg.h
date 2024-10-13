/* Copyright (c) 2024 wimanshahb@gmail.com
 * All rights reserved.
 */

// Communication Register
#define AD4130_COMMS_REG 0x00
#define AD4130_COMMS_WEN (1 << 7)
#define AD4130_COMMS_RD (1 << 6)
#define AD4130_COMMS_RS(x) ((x) & 0x3F)

// Status Register
#define AD4130_STATUS_REG 0x00
#define AD4130_STATUS_RDYB (1 << 7)
#define AD4130_STATUS_MASTER_ERR (1 << 6)
#define AD4130_STATUS_POR_FLAG (1 << 4)
#define AD4130_STATUS_CH_ACTIVE (1 << 0)

// ADC Control Register
#define AD4130_ADC_CONTROL_REG 0x01
#define AD4130_ADC_CONTROL_BIPOLAR (1 << 14)
#define AD4130_ADC_CONTROL_INT_REF_VAL (1 << 13)
#define AD4130_ADC_CONTROL_CONT_READ (1 << 11)
#define AD4130_ADC_CONTROL_DATA_STATUS (1 << 10)
#define AD4130_ADC_CONTROL_INT_REF_EN (1 << 8)

// Data Register
#define AD4130_DATA_REG 0x02

// IO Control Register
#define AD4130_IO_CONTROL_REG 0x03
#define AD4130_IO_CONTROL_SYNCB_CLEAR (1 << 10)
#define AD4130_IO_CONTROL_INT_PIN_SEL(x) ((x) << 8)
#define AD4130_IO_CONTROL_GPO_CTRL_P1 (1 << 0)

// VBIAS Control Register
#define AD4130_VBIAS_CONTROL_REG 0x04
#define AD4130_VBIAS_ENABLE(x) (1 << (x))

// ID Register
#define AD4130_ID_REG 0x05

// Error Register
#define AD4130_ERROR_REG 0x06
#define AD4130_ERROR_AINP_OV_UV_ERR (1 << 11)
#define AD4130_ERROR_AINM_OV_UV_ERR (1 << 10)
#define AD4130_ERROR_REF_OV_UV_ERR (1 << 9)

// Error Enable Register
#define AD4130_ERROR_EN_REG 0x07

// MCLK Count Register
#define AD4130_MCLK_COUNT_REG 0x08

#define AD4130_CHANNEL_AINP(x) (((x) & 0x1F) << 13) // x is the AIN+ (0x00 to 0x1F for all inputs)
#define AD4130_CHANNEL_AINM(x) (((x) & 0x1F) << 8)  // x is the AIN- (0x00 to 0x1F for all inputs)

// Bipolar/Unipolar (bit [9], select bipolar/unipolar mode)
#define AD4130_CHANNEL_BIPOLAR (1 << 9)  // 1: Bipolar, 0: Unipolar
#define AD4130_CHANNEL_UNIPOLAR (0 << 9) // 0: Unipolar

// Burnout current (bit [8], enable/disable burnout current sources)
#define AD4130_CHANNEL_BURNOUT_EN (1 << 8) // Enable burnout current

/**
 *
 * CHANNEL CONFIGS
 *
 */
// Channel Configuration Registers (0x09 to 0x18)
#define AD4130_CHANNEL_ENABLE (1 << 23)

// Differential/Single-ended mode (bit [7], select differential or single-ended mode)
#define AD4130_CHANNEL_DIFFERENTIAL (1 << 7) // 1: Differential
#define AD4130_CHANNEL_SINGLE_ENDED (0 << 7) // 0: Single-ended

#define AD4130_CHANNEL_IOUT0(x) (((x) & 0x1F))
#define AD4130_CHANNEL_IOUT1(x) (((x) & 0x1F) << 4)

#define AD4130_CHANNEL_THRES_EN (1 << 18)
#define AD4130_CHANNEL_PSDW_EN (1 << 19)

// Setup for the channel (bits [22:20] define the ADC setup configuration)
#define AD4130_CHANNEL_SETUP(x) (((x) & 0x7) << 20) // x is the setup number (0 to 7)
/*********** */

// Analog input buffer enable (bit [6], enable/disable input buffer)
#define AD4130_CHANNEL_BUFFER_EN (1 << 6) // Enable analog input buffer

// Reference selection (bits [5:0], select the reference source)
#define AD4130_CHANNEL_REF_MASK (0x3F)     // Mask for reference selection
#define AD4130_CHANNEL_REF(x) ((x) & 0x3F) // x is the reference (0x00 to 0x3F)

// Configuration Registers (n = 0 to 7)
#define AD4130_CONFIG_REG(n) (0x19 + (n))
#define AD4130_CONFIG_REF_SEL (1 << 2)

// Filter Registers (n = 0 to 7)
#define AD4130_FILTER_REG(n) (0x21 + (n))

// Offset Registers (n = 0 to 7)
#define AD4130_OFFSET_REG(n) (0x29 + (n))

// Gain Registers (n = 0 to 7)
#define AD4130_GAIN_REG(n) (0x31 + (n))

// Miscellaneous Register
#define AD4130_MISC_REG 0x39

// FIFO Control Register
#define AD4130_FIFO_CONTROL_REG 0x3A

// FIFO Status Register
#define AD4130_FIFO_STATUS_REG 0x3B

// FIFO Threshold Register
#define AD4130_FIFO_THRESHOLD_REG 0x3C

// FIFO Data Register
#define AD4130_FIFO_DATA_REG 0x3D
