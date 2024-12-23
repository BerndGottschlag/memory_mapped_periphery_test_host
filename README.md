# Memory Mapped Periphery Test Host

This project serves as the host for [a target application based on an FPGA](https://github.com/BerndGottschlag/memory_mapped_periphery_test). It uses a [NUCLEO-G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html) development board. The firmware was developed using the STM32CubeIDE version 1.17.0.

The host currently implements two functions:

1. The user button is read and if pressed the first LED of the target board is switched on.
2. The state of the first user button of the target board is read and if pressed the user LED is switched on.


## Connection to the Target Board

- SPI:
    - CS (SPI1_NSS): PA15 (Nucleo CN7-17)
    - SCK (SPI1_SCK): PB3 (Nucleo CN10-31)
    - MISO (SPI1_MISO): PB4 (Nucleo CN10-27)
    - MOSI (SPI1_MOSI): PB5 (Nucleo CN10-29)
- Reset output: PA10 (Nucleo CN10-33)
- User button input: PC13
- User LED output: PA5

## License

This project is licensed under [GPLv3](https://www.gnu.org/licenses/licenses.html#GPL).
