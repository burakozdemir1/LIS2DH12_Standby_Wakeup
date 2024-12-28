#include <stdio.h>
#include "LIS2DH12.h"

// Constructor
LIS2DH12::LIS2DH12(I2C_HandleTypeDef* handle) : i2cHandle(handle), currentState(lis2dh12State::DEVICE_READY) {}

// Destructor
LIS2DH12::~LIS2DH12() {}

// Write to a register
void LIS2DH12::writeRegister(uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};
    HAL_I2C_Master_Transmit(i2cHandle, LIS2DH12_DEVICE_ADDRESS, data, 2, HAL_MAX_DELAY);
}

// Public method to initialize the sensor
void LIS2DH12::LIS2DH12_Init()
{
    writeRegister(LIS2DH12_CTRL_REG1, 0x2F);  // Low-power, all axes enabled, 100 Hz
    writeRegister(LIS2DH12_CTRL_REG2, 0x09);  // High-pass filter enabled
    writeRegister(LIS2DH12_CTRL_REG3, 0x40);  // INT1 pin enabled
    writeRegister(LIS2DH12_CTRL_REG4, 0x00);  // ±2g range
    writeRegister(LIS2DH12_CTRL_REG5, 0x00);  // Interrupt not latched
    writeRegister(LIS2DH12_INT1_CONFIG, 0x95); // Interrupt on X, Y, Z axes
    writeRegister(LIS2DH12_INT1_THRESHOLD, 0x05); // Acceleration threshold
    writeRegister(LIS2DH12_INT1_DURATION, 0x00);  // Minimum duration
    writeRegister(LIS2DH12_TEMP_CONFIG, 0x00);  // Temperature sensor disabled
    writeRegister(LIS2DH12_FIFO_CONTROL, 0x00);  // FIFO disabled
    writeRegister(LIS2DH12_CTRL_REG6, 0x02);  // INT1 active low
}

// Check if device is ready
bool LIS2DH12::isDeviceReady()
{
	for(uint8_t i = 0 ; i < 255 ; i++)
	{
		if(HAL_I2C_IsDeviceReady(i2cHandle, i, 1, 10)==HAL_OK)
			return true;
	}
	return false;
}

// Update the sensor state
void LIS2DH12::updateLIS2DH12State(lis2dh12State newState)
{
    currentState = newState;
}


uint8_t LIS2DH12::runLIS2DH12()
{
    switch (currentState)
    {
        case lis2dh12State::DEVICE_READY:
            if (isDeviceReady())
            {
            	updateLIS2DH12State(lis2dh12State::LIS2DH12_INIT);
            }
            else
            {
                printf("Error: Failed to communicate with LIS2DH12. Transitioning to ERROR state.\n");
                updateLIS2DH12State(lis2dh12State::ERROR);

            }
            break;

        case lis2dh12State::LIS2DH12_INIT:
        	LIS2DH12_Init();
            printf("Info: LIS2DH12 successfully initialized and configured.\n");
            return 1;
            break;

        case lis2dh12State::ERROR:
            printf("Critical: LIS2DH12 is in ERROR state. Further operations are halted.\n");
            return 0;
            break;

        default:
            printf("Warning: Unknown state encountered. Transitioning to ERROR state.\n");
            updateLIS2DH12State(lis2dh12State::ERROR);

            break;
    }
}
