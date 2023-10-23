/**
 * @file SHTC3.hpp
 *
 * @brief SHTC3 Sensor Driver
 * @author Aaron Chan
 */

#ifndef SHTC3_H
#define SHTC3_H

#include <cstdint>
#include "SensorDevice.hpp"

class SHTC3 : public SensorDevice {
public:
    typedef struct {
        float temperature;
        float humidity;
    } SHTC3_DATA_T;

    SHTC3();

    bool init();

    bool getData(SHTC3_DATA_T *data);

private:
    const uint8_t SHTC3_ADDRESS = 0x70 << 1;
};

#endif // SHTC3_H
