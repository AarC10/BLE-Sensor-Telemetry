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

    // Turn to active mode. Rest of the bits are defaulted to 0 so no need to OR
    return writeReg(LTR303::CONTROL_REG, reinterpret_cast<uint8_t *>(0b1), 1);
}

bool LTR303::getData(LTR303::LTR303_DATA_T *data) {


}

bool LTR303::setActive(bool isActive) {

}
