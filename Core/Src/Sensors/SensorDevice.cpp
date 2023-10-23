//
// Created by aaron on 10/7/23.
//

#include "Sensors/SensorDevice.hpp"
#include "stm32wbxx_hal.h"

extern I2C_HandleTypeDef hi2c1;

bool SensorDevice::readReg(const uint16_t reg, uint8_t *data, const size_t len) {
    if (HAL_OK != HAL_I2C_Mem_Read(&hi2c1, address, reg, I2C_MEMADD_SIZE_16BIT, data, len, 1000)) {
        return false;
    }

    return true;
}

bool SensorDevice::writeReg(const uint16_t reg, uint8_t *data, const size_t len) {
    if (HAL_OK != HAL_I2C_Mem_Write(&hi2c1, address, reg, I2C_MEMADD_SIZE_16BIT, data, len, 1000)) {
        return false;
    }

    return true;
}

bool SensorDevice::transmit(uint8_t *data, const size_t len) {
    if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, address, data, len, 1000)) {
        return false;
    }

    return true;
}

bool SensorDevice::receive(uint8_t *data, const size_t len) {
    if (HAL_OK != HAL_I2C_Master_Receive(&hi2c1, address, data, len, 1000)) {
        return false;
    }

    return true;
}

