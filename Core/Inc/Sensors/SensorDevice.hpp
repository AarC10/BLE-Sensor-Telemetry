//
// Created by aaron on 9/26/23.
//

#ifndef SENSORDEVICE_H
#define SENSORDEVICE_H


#include <cstdint>
#include <cstddef>

class SensorDevice {
public:
    SensorDevice(const uint8_t address) {
        this->address = address;
    }

    virtual bool init() = 0;

    virtual bool getData(void *data) = 0;

protected:
    uint8_t address;

    /**
     * Read a register from the sensor
     * @param[in] reg Register to read from
     * @param data[out] Buffer to store data in
     * @param len[in] Size of data to read
     * @return Successful Operation
     */
    virtual bool readReg(const uint16_t reg, uint8_t *data, const size_t len);

    /**
     * Write a register to the sensor
     * @param[in] reg Register to write to
     * @param data[in] Buffer to write data from
     * @param[in] len Size of buffer to write
     * @return Successful Operation
     */
    virtual bool writeReg(const uint16_t reg, uint8_t *data, const size_t len);

    /**
     * Transmit data to the sensor
     * @param data[in] - Data to transmit
     * @param len[in] - Size of data to transmit
     * @return Successful Operation
     */
    virtual bool transmit(uint8_t *data, const size_t len);

    /**
     * Receive data from the sensor
     * @param data[out] - Buffer to store data in
     * @param len[in] - Size of data to receive
     * @return Successful Operation
     */
    virtual bool receive(uint8_t *data, const size_t len);
};


#endif //SENSORDEVICE_H
