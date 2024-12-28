#include "standyMode.h"

standyMode::standyMode() {
    // Constructor logic (if needed)
}

standyMode::~standyMode() {

}

void standyMode::enterStandbyMode() {
    // Check if the system woke up from standby mode
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); // Clear the standby flag
        HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1); // Disable wake-up pin PA0
    }

    // Clear wake-up flag
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

    // Enable wake-up pin PA0
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

    // Enter standby mode
    HAL_PWR_EnterSTANDBYMode();
}
