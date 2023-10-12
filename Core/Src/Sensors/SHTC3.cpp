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

bool SHTC3::readReg(uint8_t reg, uint8_t *data, uint8_t len) {
//    return HAL_OK == HAL_I2C_Mem_Read(&hi2c1, i2cAddress, reg, I2C_MEMADD_SIZE_8BIT, data, len, 100);
    return false;
}

bool SHTC3::writeReg(uint8_t reg, uint8_t *data, uint8_t len) {
//    return HAL_OK == HAL_I2C_Mem_Write(&hi2c1, i2cAddress, reg, I2C_MEMADD_SIZE_8BIT, data, len, 100);
    return false;
}

