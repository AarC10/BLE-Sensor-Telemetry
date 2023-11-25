#include "sensor_svc.h"

SENSOR_DATA_T readings = {0};


static void update_sht30d_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(sensirion_sht3xd);
    

    while (1) {

        

    }


}

static void update_lps22hb_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(st_lps22hv);
} 


static void update_tmp117_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(ti_tmp116);
}


int sensor_init() {

    return 0;
}
