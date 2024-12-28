/*
 * standyMode.h
 *
 *  Created on: Dec 29, 2024
 *      Author: BurakOzdemir
 */

#ifndef STANDYMODE_H_
#define STANDYMODE_H_

#include "stm32f0xx_hal.h"
#include <cstdint>

class standyMode {
public:
    standyMode();          // Constructor
    virtual ~standyMode(); // Destructor

    void enterStandbyMode(); // Function to handle standby mode
};

#endif /* STANDYMODE_H_ */
