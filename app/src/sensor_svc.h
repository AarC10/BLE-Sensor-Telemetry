/*
 * Copyright (c) 2023 Aaron Chan
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef ST_BLE_SENSOR_SENSOR_SVC_H_
#define ST_BLE_SENSOR_SENSOR_SVC_H_


#include "zephyr/device.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute__((__packed__)) {
    float lps22hb_temp;
    float lps22hb_press;

    float tmp117_temp;

    float sht30d_temp;
    float sht30d_hum;
} SENSOR_DATA_T;

int sensor_init();

#ifdef __cplusplus
}
#endif

#endif
