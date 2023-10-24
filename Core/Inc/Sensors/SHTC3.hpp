/**
 * @file SHTC3.hpp
 *
 * @brief SHTC3 Sensor Driver
 * @author Aaron Chan
 * @link https://sensirion.com/media/documents/643F9C8E/63A5A436/Datasheet_SHTC3.pdf
 *
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

    SHTC3(uint8_t address);

    bool init();

    bool getData(SHTC3_DATA_T *data);

private:
    const uint8_t SHTC3_ADDRESS = 0x70 << 1;
    const uint8_t i2cAddress;

    bool wakeup();

    bool measurement();

    bool read_out(uint8_t *data, const size_t len);

    bool sleep();

    bool readCommand(uint8_t *data, const size_t len);

    bool writeCommand(uint16_t command);

protected:
    bool transmit(uint8_t *data, const size_t len) override;

    bool receive(uint8_t *data, const size_t len) override;

};

#endif // SHTC3_H
