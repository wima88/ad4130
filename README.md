# Analog Devices AD4130-x Zephyr Module
32 μA, Ultra Low Power, 24-Bit Sigma-Delta ADC with Integrated PGA and FIFO
* Analog Device releases official supporting libs for [AD4130](https://github.com/analogdevicesinc/no-OS/blob/main/drivers/afe/ad413x/ad413x.h) for non-os  

### Intergrating to exsisitng workspace

#### 1. Append following to  `west.yml` 
```yaml
    - name: ad4130
      path: modules/lib/ad4130
      revision: 0.0.1
      url: https://github.com/wima88/ad4130.git
```
`west manifest --path` can show location of the `west.yaml`
Call `west update` to checkout the code and placed in `modules/lib/ad4130`

#### 2. Device tree Overlay
```
&spi3 {
    status = "okay";
    cs-gpios = <&gpio1 12 GPIO_ACTIVE_LOW>;

    adc0: ad4130@0 {
        compatible = "ad,ad4130";
        reg = <0x0>;
        spi-max-frequency = <4000000>;
        irq-gpios = <&gpio1 3 GPIO_ACTIVE_HIGH>;
    };
};
```
#### 3. prj.conf
```
CONFIG_SPI=y
CONFIG_AD4130=y
```
### Application  
in `main.c` add follwoing for minimalistic Integration
```c
#include "ad4130.h"
#include <zephyr/kernel.h>

int main(void) {
    printf("Hello World! %s\n", CONFIG_BOARD);

    ad4130_init();

    ad4130_get_id();

    // Example configuration for channel 0
    ad4130_channel_cfg_t channel0_cfg = {
        .ainp   = AIN1, // AIN0 as positive input
        .ainm   = AIN0, // AIN1 as negative input
        .setup  = 0,    // Use setup 0
        .enable = 1,    // Enable the channel

        // From the bitfield image
        .thres_en = 0, // Disable threshold
        .psdw_en  = 0, // Disable power-down switch

        // IOUT fields (Configure current sources)
        .iout0 = AIN0, // IOUT0 connected to AIN0
        .iout1 = AIN0, // IOUT1 connected to AIN0
    };

    // Initialize channel 0
    ad4130_init_channel(0, &channel0_cfg);

    return 0;
}
```
### ToDo
1. Add channel configs to DT
2. have KCONFIG option to enable disable dynamic channel config 


## Reference Documents
1. [Product summery](https://www.analog.com/en/products/ad4130-8.html#part-details)
2. [Data Sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad4130-8.pdf)

