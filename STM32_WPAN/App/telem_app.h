//
// Created by aaron on 10/12/23.
//

#ifndef TELEM_APP_H
#define TELEM_APP_H

#include <stdint.h>

void transmitTelemetry(void *sensorData, uint8_t sensorType);

void requestTelemetry(uint8_t sensorID);

#endif // TELEM_APP_H
