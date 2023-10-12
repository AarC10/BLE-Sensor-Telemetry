//
// Created by aaron on 9/26/23.
//
// @link https://sensirion.com/media/documents/643F9C8E/63A5A436/Datasheet_SHTC3.pdf

#ifndef SHTC3_H
#define SHTC3_H

#include <stdint.h>

class SHTC3 {
public:
    typedef struct {
        float temperature;
        float humidity;
    } SHTC3_DATA_T;

    SHTC3(uint8_t address);

    bool init();

    bool getData(SHTC3_DATA_T *data);

private:
    const uint8_t i2cAddress;
    bool readReg(uint8_t reg, uint8_t *data, uint8_t len);

    bool writeReg(uint8_t reg, uint8_t *data, uint8_t len);
};

#endif // SHTC3_H
