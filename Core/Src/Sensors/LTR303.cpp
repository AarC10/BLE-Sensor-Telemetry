//
// Created by aaron on 10/11/23.
//

#include "Sensors/LTR303.hpp"
#include "stm32wbxx_hal.h"

bool LTR303::init() {
    uint8_t manufacturer_id = 0;
    if (!readReg(LTR303::MANUFAC_ID_REG, &manufacturer_id, 1)) {
        return false;
    }

    if (manufacturer_id != 0x05) {
        return false;
    }

    // Reset the chip
    if (!writeReg(LTR303::CONTROL_REG, reinterpret_cast<uint8_t *>(0b1 << 1), 1)) {
        return false;
    }

    HAL_Delay(100);

    return setActive(true);
}

bool LTR303::getData(LTR303::LTR303_DATA_T *data) {


}

bool LTR303::setActive(bool isActive) {
    uint8_t control_reg = 0;
    if (!readReg(LTR303::CONTROL_REG, &control_reg, 1)) {
        return false;
    }

    control_reg = isActive ? control_reg | 0b1 : control_reg & ~0b1;

    return writeReg(LTR303::CONTROL_REG, &control_reg, 1);
}
