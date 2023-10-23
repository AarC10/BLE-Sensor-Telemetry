#include <cstddef>
#include "Sensors/SHTC3.hpp"


//extern I2C_HandleTypeDef hi2c1;

SHTC3::SHTC3(const uint8_t address) : i2cAddress(address) {}

bool SHTC3::init() {
    return true;
}

bool SHTC3::getData(SHTC3::SHTC3_DATA_T *data) {


    return true;
}

bool SHTC3::readCommand(uint16_t command, uint8_t *data, const size_t len) {
    bool ret = transmit((uint8_t *) &command, 2);

}

bool SHTC3::writeCommand(uint16_t command, uint8_t *data, const size_t len) {

}
