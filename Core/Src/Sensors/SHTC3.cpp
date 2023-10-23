#include <cstddef>
#include "Sensors/SHTC3.hpp"
#include "stm32wbxx_hal_i2c.h"


extern I2C_HandleTypeDef hi2c1;

SHTC3::SHTC3(const uint8_t address) : i2cAddress(address) {}

bool SHTC3::init() {
    return true;
}

bool SHTC3::getData(SHTC3::SHTC3_DATA_T *data) {


    return true;
}

bool SHTC3::readCommand(uint16_t command, uint8_t *data, const size_t len) {
    bool ret = transmit((uint8_t *) &command, 2);

    if (ret) {
        ret = receive(data, len);
    }

    return ret;
}

bool SHTC3::writeCommand(uint16_t command, uint8_t *data, const size_t len) {
    bool ret = transmit((uint8_t *) &command, 2);

    if (ret) {
        ret = transmit(data, len);
    }

    return ret;
}

bool SHTC3::transmit(uint8_t *data, const size_t len) {
    return HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, i2cAddress, data, len, 1000);
}

bool SHTC3::receive(uint8_t *data, const size_t len) {
    return HAL_OK != HAL_I2C_Master_Receive(&hi2c1, i2cAddress | 0b1, data, len, 1000);
}
