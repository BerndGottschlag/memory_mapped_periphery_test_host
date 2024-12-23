#include "stm32g4xx_hal.h"
#include "main.h"

#define PACKET_SIZE_IN_BYTES 3

#define OPCODE_READ 0
#define OPCODE_WRITE 1

void Reset_FPGA(void)
{
	HAL_GPIO_WritePin(RESET_OUTPUT_GPIO_Port, RESET_OUTPUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(RESET_OUTPUT_GPIO_Port, RESET_OUTPUT_Pin, GPIO_PIN_SET);
}

void Set_Register(SPI_HandleTypeDef * spiHandle,
                  const uint16_t registerAddress,
                  const uint8_t data)
{
	uint8_t packetBuffer[PACKET_SIZE_IN_BYTES];

	/* Packet 0 contains the mode (MSB), rest contains the upper part of the address */
	packetBuffer[0] = (OPCODE_WRITE << 7) |
	                  ((registerAddress >> 8) & 0xFF);
	/* Packet 1 contains the lower part of the address */
	packetBuffer[1] = registerAddress & 0xFF;
	/* Packet 2 contains the data */
	packetBuffer[2] = data;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spiHandle, packetBuffer, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

void Read_Register(SPI_HandleTypeDef * spiHandle,
                   const uint16_t registerAddress,
                   uint8_t * const data)
{
	uint8_t txPacketBuffer[PACKET_SIZE_IN_BYTES] = {};
	uint8_t rxPacketBuffer[PACKET_SIZE_IN_BYTES] = {};

	/* Packet 0 contains the mode (MSB), rest contains the upper part of the address */
	txPacketBuffer[0] = (OPCODE_READ << 7) |
	                    ((registerAddress >> 8) & 0xFF);
	/* Packet 1 contains the lower part of the address */
	txPacketBuffer[1] = registerAddress & 0xFF;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(spiHandle,
	                        txPacketBuffer,
	                        rxPacketBuffer,
	                        3,
	                        HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

	/* Packet 2 contains the data */
	*data = rxPacketBuffer[2];
}
