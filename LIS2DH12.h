/*
 * standyMode.h
 *
 *  Created on: Dec 29, 2024
 *      Author: BurakOzdemir
 */

#ifndef LIS2DH12_H_
#define LIS2DH12_H_

#include "stm32f0xx_hal.h"
#include <cstdint>

// Register definitions
#define LIS2DH12_DEVICE_ADDRESS	  0x33
#define LIS2DH12_CTRL_REG1        0x20
#define LIS2DH12_CTRL_REG2        0x21
#define LIS2DH12_CTRL_REG3        0x22
#define LIS2DH12_CTRL_REG4        0x23
#define LIS2DH12_CTRL_REG5        0x24
#define LIS2DH12_CTRL_REG6        0x25
#define LIS2DH12_TEMP_CONFIG      0x1F
#define LIS2DH12_FIFO_CONTROL     0x2E
#define LIS2DH12_INT1_THRESHOLD   0x32
#define LIS2DH12_INT1_DURATION    0x33
#define LIS2DH12_INT1_CONFIG      0x30

class LIS2DH12
{
private:
    I2C_HandleTypeDef* i2cHandle; // Pointer to the I2C handle

    // State for the sensor
    enum class lis2dh12State { DEVICE_READY, LIS2DH12_INIT, ERROR };
    lis2dh12State currentState;

public:
    // Constructor and Destructor
    LIS2DH12(I2C_HandleTypeDef* handle);
    virtual ~LIS2DH12();

    // Public Methods
    void LIS2DH12_Init();
    bool isDeviceReady();
    uint8_t runLIS2DH12();

private:
    void writeRegister(uint8_t reg, uint8_t value); // Fonksiyon bildirimi burada
    void updateLIS2DH12State(lis2dh12State newState);
};

#endif /* LIS2DH12_H_ */
