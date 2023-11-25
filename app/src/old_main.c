// /*
//  * Copyright (c) 2023 Aaron Chan
//  * SPDX-License-Identifier: Apache-2.0
//  */
//
// #include "zephyr/device.h"
// #include <zephyr/kernel.h>
// #include <zephyr/drivers/sensor.h>
// #include <app_version.h>
//
// #include <zephyr/bluetooth/bluetooth.h>
// #include <zephyr/bluetooth/hci.h>
//
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/drivers/led.h>
//
// #include <zephyr/logging/log.h>
//
// LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);
//
// static void sensor_task(void *unused0, void *unused1, void *unused2) {
//     int ret;
// 	const struct device *sensor;
//
// 	// sensor = DEVICE_DT_GET(DT_NODELABEL(examplesensor0));
// 	// if (!device_is_ready(sensor)) {
// 	// 	LOG_ERR("Sensor not ready");
// 	// 	return 0;
// 	// }
// 	//
// 	// while (1) {
// 	// 	struct sensor_value val;
// 	//
// 	// 	ret = sensor_sample_fetch(sensor);
// 	// 	if (ret < 0) {
// 	// 		LOG_ERR("Could not fetch sample (%d)", ret);
// 	// 		return 0;
// 	// 	}
// 	//
// 	// 	ret = sensor_channel_get(sensor, SENSOR_CHAN_PROX, &val);
// 	// 	if (ret < 0) {
// 	// 		LOG_ERR("Could not get sample (%d)", ret);
// 	// 		return 0;
// 	// 	}
// 	//
// 	// 	printk("Sensor value: %d\n", val.val1);
// 	//
// 	// 	k_sleep(K_MSEC(1000));
// 	// }
// }
//
//
// int main(void) {
//     static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
//
//     uint8_t adv_data[] = {0xff, 0xff, 0x00};
//
//     printk("Enabling Bluetooth\n");
// 	int ret = bt_enable(NULL);
// 	if (ret) {
// 		printk("Bluetooth init failed (err %d)\n", ret);
// 		return 0;
// 	}
//
// 	printk("Bluetooth initialized\n");
//
//
//     ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
// 	if (ret < 0) {
// 		return 0;
// 	}
//
// 	// while (1) {
// 	// 	ret = gpio_pin_toggle_dt(&led);
// 	// 	if (ret < 0) {
// 	// 		return 0;
// 	// 	}
// 	// 
//  //        ret = bt_le_adv_start(BT_LE_ADV_NCONN, adv_data, ARRAY_SIZE(adv_data), NULL, 0);
// 	// 	if (ret) {
// 	// 		printk("Advertising failed to start (err %d)\n", ret);
// 	// 	}
// 	//
// 	// 	k_msleep(1000);
// 	//
// 	// 	ret = bt_le_adv_stop();
// 	// 	if (ret) {
// 	// 		printk("Advertising failed to stop (err %d)\n", ret);
// 	// 	}
// 	//
//  //        k_msleep(1000);
// 	// }
//
// 	return 0;
// }
//
