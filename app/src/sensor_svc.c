#include "sensor_svc.h"
#include "zephyr/device.h"
#include "zephyr/drivers/sensor.h"
#include "zephyr/kernel.h"
#include "zephyr/kernel/thread_stack.h"
#include "zephyr/sys/arch_interface.h"

#define STACK_SIZE (512)
#define NUM_SENSORS 3
#define MOVE_CURSOR_STR(row, col) printf("\x1b[%d;%dH", row, col)

static K_THREAD_STACK_ARRAY_DEFINE(sensor_stacks, NUM_SENSORS, STACK_SIZE);
static struct k_thread sensor_threads[NUM_SENSORS] = {0};

static K_THREAD_STACK_DEFINE(print_stack, STACK_SIZE);
static struct k_thread print_thread = {0};

SENSOR_DATA_T readings = {0};



int check_dev(const struct device *device) {
    int ret = device_is_ready(device);

    if (ret) printk("Error %d: %s is not ready\n", ret, device->name);

    return ret;
}


static void update_sht30d_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ONE(sensirion_sht3xd);

    struct sensor_value temperature = {0};   
    struct sensor_value humidity = {0};

    int ret = device_is_ready(device);
    if (ret) printk("Error %d: %s is not ready\n", ret, device->name);
    
    while (1) {
        if (sensor_sample_fetch(device)) continue;
        
        sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        sensor_channel_get(device, SENSOR_CHAN_HUMIDITY, &humidity);

        readings.sht30d_temp = sensor_value_to_float(&temperature);
        readings.sht30d_hum  = sensor_value_to_float(&humidity);

        k_msleep(100);
    }
}

static void update_lps22hb_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(st_lps22hv);

    struct sensor_value temperature = {0};   
    struct sensor_value pressure = {0};

    int ret = device_is_ready(device);
    if (ret) printk("Error %d: %s is not ready\n", ret, device->name);

    while (1) {
        // if (sensor_sample_fetch(device)) {
        //      printk("LPS22HB: Failed to get data");
        // }
        //
        // sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        // sensor_channel_get(device, SENSOR_CHAN_PRESS, &pressure);

        readings.lps22hb_temp = sensor_value_to_float(&temperature);
        readings.lps22hb_press = sensor_value_to_float(&pressure);


        k_msleep(100);
    }

} 


static void update_tmp117_readings(void *unused0, void *unused1, void *unused2) {
    const struct device *device = DEVICE_DT_GET_ANY(ti_tmp116);

    struct sensor_value temperature = {0};   

    int ret = device_is_ready(device);
    if (ret) printk("Error %d: %s is not ready\n", ret, device->name);

    while (1) {
        if (sensor_sample_fetch(device)) continue;
        
        sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &temperature);

        readings.tmp117_temp = sensor_value_to_float(&temperature);

        k_msleep(100);
    }
}

static void print_readings(void *unused, void *unused1, void *unused2) {
    while (1) {
        MOVE_CURSOR_STR(1, 1);
        printk("TMP117: %f C\n", readings.tmp117_temp);
        
        MOVE_CURSOR_STR(2, 1);
        printk("LPS22HB: %f C\t %f Pa\n", readings.lps22hb_temp, readings.lps22hb_press);
        
        MOVE_CURSOR_STR(3, 1);
        printk("SHT30D: %f C\t %f Pa\n", readings.sht30d_temp, readings.sht30d_hum);
        k_msleep(100);
    }
}


int sensor_init() {
    k_thread_entry_t sensor_tasks[] = {update_sht30d_readings, update_lps22hb_readings, update_tmp117_readings};
    for (int i = 0; i < NUM_SENSORS; i++) {
        k_thread_create(&sensor_threads[i], &sensor_stacks[i][0], STACK_SIZE, sensor_tasks[i], NULL, NULL, NULL, K_PRIO_PREEMPT(10), 0, K_NO_WAIT);
        k_thread_start(&sensor_threads[i]);
    }

    k_thread_create(&print_thread, &print_stack[0], STACK_SIZE, print_readings, NULL, NULL, NULL, K_PRIO_PREEMPT(10), 0, K_NO_WAIT);
    k_thread_start(&print_thread);

    return 0;
}
