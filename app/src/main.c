/*
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright (c) 2019 Marcio Montenegro <mtuxpe@gmail.com>
 * Copyright (c) 2023 Aaron Chan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include "bt_svc.h"
#include "button_svc.h"
#include "led_svc.h"
#include "sensor_svc.h"

LOG_MODULE_REGISTER(main);

int main(void) {
 //    int err = button_init(NULL);
 //    if (err) return err;
	//
	// err = led_init();
 //    if (err) return err;
	//
 //    err = bt_init();
 //    if (err) return err;
	//
    return sensor_init();
}
