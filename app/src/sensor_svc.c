#include "sensor_svc.h"
#include "zephyr/device.h"
#include "zephyr/drivers/sensor.h"

SENSOR_DATA_T readings = {0};

int check_dev(const struct device *device) {
    int ret = device_is_ready(device);

    if (ret) printk("Error %d: %s is not ready", ret, device->name);


    return ret;
}


static void update_sht30d_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ONE(sensirion_sht3xd);
    if (check_dev(device)) return;

    struct sensor_value temperature;   
    struct sensor_value humidity;


    while (1) {
        if (sensor_sample_fetch(device)) continue;

        sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        sensor_channel_get(device, SENSOR_CHAN_HUMIDITY, &humidity);

        readings.sht30d_temp = sensor_value_to_float(&temperature);
        readings.sht30d_hum  = sensor_value_to_float(&humidity);

        printk("SHT30D: %f C\t %f Pa\n", readings.sht30d_temp, readings.sht30d_hum);
    }
}

static void update_lps22hb_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(st_lps22hv);
    if (check_dev(device)) return;

    struct sensor_value temperature;   
    struct sensor_value pressure;


    while (1) {
        if (sensor_sample_fetch(device)) continue;

        sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        sensor_channel_get(device, SENSOR_CHAN_PRESS, &pressure);

        readings.lps22hb_temp = sensor_value_to_float(&temperature);
        readings.lps22hb_press = sensor_value_to_float(&pressure);

        printk("SHT30D: %f C\t %f Pa\n", readings.lps22hb_temp, readings.lps22hb_press);
    }

} 


static void update_tmp117_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(ti_tmp116);
    if (check_dev(device)) return;

    struct sensor_value temperature;   


    while (1) {
        if (sensor_sample_fetch(device)) continue;

        sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);

        readings.tmp117_temp = sensor_value_to_float(&temperature);

        printk("TMP117: %f C\n", readings.tmp117_temp);
    }


}


int sensor_init() {
    // update_sht30d_readings(NULL, NULL, NULL);
    update_lps22hb_readings(NULL, NULL, NULL);
    update_tmp117_readings(NULL, NULL, NULL);
    return 0;
}
