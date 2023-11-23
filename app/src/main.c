/*
 * Copyright (c) 2023 Aaron Chan
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <app_version.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

static void sensor_task(void *unused0, void *unused1, void *unused2) {
    int ret;
	const struct device *sensor;

	// sensor = DEVICE_DT_GET(DT_NODELABEL(examplesensor0));
	// if (!device_is_ready(sensor)) {
	// 	LOG_ERR("Sensor not ready");
	// 	return 0;
	// }
	//
	// while (1) {
	// 	struct sensor_value val;
	//
	// 	ret = sensor_sample_fetch(sensor);
	// 	if (ret < 0) {
	// 		LOG_ERR("Could not fetch sample (%d)", ret);
	// 		return 0;
	// 	}
	//
	// 	ret = sensor_channel_get(sensor, SENSOR_CHAN_PROX, &val);
	// 	if (ret < 0) {
	// 		LOG_ERR("Could not get sample (%d)", ret);
	// 		return 0;
	// 	}
	//
	// 	printk("Sensor value: %d\n", val.val1);
	//
	// 	k_sleep(K_MSEC(1000));
	// }
}


int main(void) {

	return 0;
}

