//
// Created by aaron on 10/11/23.
//
// @link https://www.mouser.com/datasheet/2/239/Lite-On_LTR-303ALS-01_DS_ver%201.1-1175269.pdf

#ifndef LTR303_H
#define LTR303_H


#include "SensorDevice.hpp"

class LTR303 : public SensorDevice {
public:

    typedef enum {
        CONTROL_REG = 0x80,
        ALS_MEAS_RATE_REG = 0x85,
        PART_ID_REG = 0x86,
        MANUFAC_ID_REG = 0x07,
        ALS_DATA_CH1_0_REG = 0x88,
        ALS_DATA_CH1_1_REG = 0x89,
        ALS_DATA_CH0_0_REG = 0x8A,
        ALS_DATA_CH0_1_REG = 0x8B,
        ALS_STATUS_REG = 0x8C,
        INTERRUPT_REG = 0x8F,
        ALS_THRES_UP_0_REG = 0x97,
        ALS_THRES_UP_1_REG = 0x98,
        ALS_THRES_LOW_0_REG = 0x99,
        ALS_THRES_LOW_1_REG = 0x9A,
        INTERRUPT_PERSIST_REG = 0x9E,
    } LTR303_REG_T;

    typedef struct {
        uint16_t infrared_light;
        uint16_t visible_light;
    } LTR303_DATA_T;

    LTR303() : SensorDevice(LTR303_ADDRESS) {};

    bool init() override;

    bool setActive(bool isActive);

    bool getData(void *data) override;

private:
    static constexpr uint8_t LTR303_ADDRESS = 0x29 << 1;
};

#endif //LTR303_H
