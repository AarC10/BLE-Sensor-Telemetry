//
// Created by aaron on 9/26/23.
//

#ifndef SENSORDEVICE_H
#define SENSORDEVICE_H


class SensorDevice {
public:
    SensorDevice() {}

    virtual bool init() = 0;

    virtual bool getData(void *data) = 0;

private:

};


#endif //SENSORDEVICE_H
