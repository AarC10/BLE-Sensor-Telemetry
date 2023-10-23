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

bool SHTC3::wakeup() {
    static uint8_t constexpr command = (0b00110101 << 8) | 0b00010111;
    return writeCommand(command, nullptr, 0);
}

bool SHTC3::measurement() {
    static uint8_t constexpr command = (0b01011100 << 8) | 0b00100100;
    return writeCommand(command, nullptr, 0);
}

bool SHTC3::read_out(uint8_t *data, const size_t len) {
    return readCommand(data, len);
}

bool SHTC3::sleep() {
    static uint8_t constexpr command = (0b10110111 << 8) | 0b10011000;
    return writeCommand(command, nullptr, 0);
}

bool SHTC3::readCommand(uint8_t *data, const size_t len) {
    return receive(data, len);
}

bool SHTC3::writeCommand(uint16_t command) {
    return transmit((uint8_t *) &command, 2);
}

bool SHTC3::transmit(uint8_t *data, const size_t len) {
    return HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, i2cAddress, data, len, 1000);
}

bool SHTC3::receive(uint8_t *data, const size_t len) {
    return HAL_OK != HAL_I2C_Master_Receive(&hi2c1, i2cAddress | 0b1, data, len, 1000);
}
