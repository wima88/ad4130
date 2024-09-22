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

// Channel Configuration Registers (0x09 to 0x18)
#define AD4130_CHANNEL_REG(x) (0x09 + (x))
#define AD4130_CHANNEL_ENABLE (1 << 23)
// Setup for the channel (bits [22:20] define the ADC setup configuration)
#define AD4130_CHANNEL_SETUP_MASK (0x7 << 20)       // Mask to clear setup bits
#define AD4130_CHANNEL_SETUP(x) (((x) & 0x7) << 20) // x is the setup number (0 to 7)

// Positive input selection (bits [19:15], select the positive input channel)
#define AD4130_CHANNEL_AINP_MASK (0x1F << 15)       // Mask to clear AINP bits
#define AD4130_CHANNEL_AINP(x) (((x) & 0x1F) << 15) // x is the AIN+ (0x00 to 0x1F for all inputs)

// Negative input selection (bits [14:10], select the negative input channel)
#define AD4130_CHANNEL_AINM_MASK (0x1F << 10)       // Mask to clear AINM bits
#define AD4130_CHANNEL_AINM(x) (((x) & 0x1F) << 10) // x is the AIN- (0x00 to 0x1F for all inputs)

// Bipolar/Unipolar (bit [9], select bipolar/unipolar mode)
#define AD4130_CHANNEL_BIPOLAR (1 << 9)  // 1: Bipolar, 0: Unipolar
#define AD4130_CHANNEL_UNIPOLAR (0 << 9) // 0: Unipolar

// Burnout current (bit [8], enable/disable burnout current sources)
#define AD4130_CHANNEL_BURNOUT_EN (1 << 8) // Enable burnout current

// Differential/Single-ended mode (bit [7], select differential or single-ended mode)
#define AD4130_CHANNEL_DIFFERENTIAL (1 << 7) // 1: Differential
#define AD4130_CHANNEL_SINGLE_ENDED (0 << 7) // 0: Single-ended

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

typedef enum {
    AIN0                  = 0x00, // 00000 AIN0
    AIN1                  = 0x01, // 00001 AIN1
    AIN2                  = 0x02, // 00010 AIN2
    AIN3                  = 0x03, // 00011 AIN3
    AIN4                  = 0x04, // 00100 AIN4
    AIN5                  = 0x05, // 00101 AIN5
    AIN6                  = 0x06, // 00110 AIN6
    AIN7                  = 0x07, // 00111 AIN7
    AIN8                  = 0x08, // 01000 AIN8
    AIN9                  = 0x09, // 01001 AIN9
    AIN10                 = 0x0A, // 01010 AIN10
    AIN11                 = 0x0B, // 01011 AIN11
    AIN12                 = 0x0C, // 01100 AIN12
    AIN13                 = 0x0D, // 01101 AIN13
    AIN14                 = 0x0E, // 01110 AIN14
    AIN15                 = 0x0F, // 01111 AIN15
    TEMP_SENSOR           = 0x10, // 10000 Temperature Sensor
    AVSS                  = 0x11, // 10001 AVSS
    INTERNAL_REFERENCE    = 0x12, // 10010 Internal Reference
    DGND                  = 0x13, // 10011 DGND
    AVDD_AVSS_DIV6_PLUS   = 0x14, // 10100 (AVDD − AVSS)/6+
    AVDD_AVSS_DIV6_MINUS  = 0x15, // 10101 (AVDD − AVSS)/6−
    IOVDD_DGND_DIV6_PLUS  = 0x16, // 10110 (IOVDD − DGND)/6+
    IOVDD_DGND_DIV6_MINUS = 0x17, // 10111 (IOVDD − DGND)/6−
    ALDO_AVSS_DIV6_PLUS   = 0x18, // 11000 (ALDO − AVSS)/6+
    ALDO_AVSS_DIV6_MINUS  = 0x19, // 11001 (ALDO − AVSS)/6−
    DLDO_DGND_DIV6_PLUS   = 0x1A, // 11010 (DLDO − DGND)/6+
    DLDO_DGND_DIV6_MINUS  = 0x1B  // 11011 (DLDO − DGND)/6−
} ad4130_input_t;
