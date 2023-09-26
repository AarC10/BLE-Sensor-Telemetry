//
// Created by aaron on 9/26/23.
//

#ifndef SHTC3_H
#define SHTC3_H

class SHTC3 {
public:
    typedef struct {
        float temperature;
        float humidity;
    } SHTC3_DATA_T;

    SHTC3();

    bool init();

    bool getData(SHTC3_DATA_T *data);

};

#endif // SHTC3_H
