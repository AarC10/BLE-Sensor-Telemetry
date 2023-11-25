/** @file
 *  @brief Button Service sample
 */

/*
 * Copyright (c) 2019 Marcio Montenegro <mtuxpe@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "button_svc.h"
#include "bt_svc.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(button_svc);

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static struct gpio_callback gpio_cb;
uint16_t but_val;

extern struct bt_conn *ble_conn;
extern volatile bool notify_enable;
extern struct bt_gatt_attr stsensor_svc; 

static void default_button_callback(const struct device *gpiob, struct gpio_callback *cb, uint32_t pins) {
	int err;

	LOG_INF("Button pressed");
	if (ble_conn) {
		if (notify_enable) {
            err = bt_handle_button_cb(&but_val);

            if (err) {
				LOG_ERR("Notify error: %d", err);
			} else {
				LOG_INF("Send notify ok");
				but_val = (but_val == 0) ? 0x100 : 0;
			}

		} else {
			LOG_INF("Notify not enabled");
		}

	} else {
		LOG_INF("BLE not connected");
	}
}


int button_init(gpio_callback_handler_t handler) {
	int ret;

	if (!gpio_is_ready_dt(&button)) {
		LOG_ERR("Error: button GPIO device %s is not ready",
			button.port->name);
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret) {
		LOG_ERR("Error %d: can't configure button on GPIO %s pin %d",
			ret, button.port->name, button.pin);
		return ret;

	}

    if (handler == NULL) handler = default_button_callback;

	gpio_init_callback(&gpio_cb, handler, BIT(button.pin));
	gpio_add_callback(button.port, &gpio_cb);
	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret) {
		LOG_ERR("Error %d: can't configure button interrupt on "
			"GPIO %s pin %d", ret, button.port->name, button.pin);
		return ret;
	}
	return 0;
}



