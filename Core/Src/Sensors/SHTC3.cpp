#include <cstddef>
#include "Sensors/SHTC3.hpp"


//extern I2C_HandleTypeDef hi2c1;

SHTC3::SHTC3(const uint8_t address) : i2cAddress(address) {}

bool SHTC3::init() {
    return true;
}

bool SHTC3::getData(SHTC3::SHTC3_DATA_T *data) {
    readReg(0x00, (uint8_t *) data, sizeof(SHTC3_DATA_T)); // TODO: Figure out address

    return true;
}
