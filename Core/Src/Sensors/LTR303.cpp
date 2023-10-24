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
    uint8_t reg_data[4] = {0};

    if (readReg(ALS_DATA_CH1_0_REG, reg_data, 4)) {
        data->infrared_light = (reg_data[1] << 8) | reg_data[0];
        data->visible_light = (reg_data[3] << 8) | reg_data[2];
        return true;
    }

    return false;
}

bool LTR303::setActive(bool isActive) {
    uint8_t control_reg = 0;
    if (!readReg(LTR303::CONTROL_REG, &control_reg, 1)) {
        return false;
    }

    control_reg = isActive ? control_reg | 0b1 : control_reg & ~0b1;

    return writeReg(LTR303::CONTROL_REG, &control_reg, 1);
}
