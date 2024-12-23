#ifndef FPGA_INTERFACE_H
#define FPGA_INTERFACE_H

void Reset_FPGA(void);
void Set_Register(SPI_HandleTypeDef * spiHandle,
                  const uint16_t registerAddress,
                  const uint8_t data);
void Read_Register(SPI_HandleTypeDef * spiHandle,
                   const uint16_t registerAddress,
                   uint8_t * const data);

#endif
