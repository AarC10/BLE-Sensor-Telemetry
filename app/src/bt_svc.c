/*
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright (c) 2019 Marcio Montenegro <mtuxpe@gmail.com>
 * Copyright (c) 2023 Aaron Chan
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/logging/log.h>


#include "bt_svc.h"
#include "led_svc.h"
#include "sensor_svc.h"
#include "zephyr/bluetooth/gatt.h"


#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define ADV_LEN 12

LOG_MODULE_REGISTER(bt_svc);

struct bt_conn *ble_conn;
volatile bool notify_enable;

extern uint16_t but_val; 
extern SENSOR_DATA_T readings;


BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

/* ST Custom Service  */
struct bt_uuid_128 st_service_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe40, 0xcc7a, 0x482a, 0x984a, 0x7f2ed5b3e58f)
);

/* ST LED service */
struct bt_uuid_128 led_char_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe41, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19)
);

/* ST Notify button service */
struct bt_uuid_128 but_notif_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe42, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19)
);

/* Sensor Data Characteristic */
struct bt_uuid_128 sensor_data_uuid = BT_UUID_INIT_128(
    BT_UUID_128_ENCODE(0x0000feed, 0xfeed, 0xdead, 0xbeef, 0x000000000001)
);

/* Advertising data */
uint8_t manuf_data[ADV_LEN] = {
	0x01 /*SKD version */,
	0x83 /* STM32WB - P2P Server 1 */,
	0x00 /* GROUP A Feature  */,
	0x00 /* GROUP A Feature */,
	0x00 /* GROUP B Feature */,
	0x00 /* GROUP B Feature */,
	0x00, /* BLE MAC start -MSB */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, /* BLE MAC stop */
};

const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
	BT_DATA(BT_DATA_MANUFACTURER_DATA, manuf_data, ADV_LEN)
};


BT_GATT_SERVICE_DEFINE(stsensor_svc, 
                    BT_GATT_PRIMARY_SERVICE(&st_service_uuid),

                    BT_GATT_CHARACTERISTIC(&led_char_uuid.uuid, 
                                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE_WITHOUT_RESP, 
                                           BT_GATT_PERM_WRITE, NULL, recv, (void *)1),

                    BT_GATT_CHARACTERISTIC(&but_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY, 
                                           BT_GATT_PERM_READ, NULL, NULL, &but_val),
            
                    BT_GATT_CHARACTERISTIC(&sensor_data_uuid.uuid,
                                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                                           BT_GATT_PERM_READ, NULL, NULL, &readings),

                    BT_GATT_CCC(mpu_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);



void connected(struct bt_conn *connected, uint8_t err) {
	if (err) {
		LOG_ERR("Connection failed (err %u)", err);
	} else {
		LOG_INF("Connected");
		if (!ble_conn) {
			ble_conn = bt_conn_ref(connected);
		}
	}
}

void disconnected(struct bt_conn *disconn, uint8_t reason) {
	if (ble_conn) {
		bt_conn_unref(ble_conn);
		ble_conn = NULL;
	}

	LOG_INF("Disconnected (reason %u)", reason);
}

ssize_t recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buff, uint16_t len, uint16_t offset, uint8_t flags) {
	led_update();
	return 0;
}

void mpu_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value) {
	ARG_UNUSED(attr);
	notify_enable = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Notification %s", notify_enable ? "enabled" : "disabled");
}

void sensor_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value) {
	ARG_UNUSED(attr);
	notify_enable = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Notification %s", notify_enable ? "enabled" : "disabled");
}

void bt_ready(int err) {
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}
	
    LOG_INF("Bluetooth initialized");
	
    /* Start advertising */
    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}

	LOG_INF("Configuration mode: waiting connections...");
}

int bt_init() {
	int err = bt_enable(bt_ready);

	if (err) LOG_ERR("Bluetooth init failed (err %d)", err);

    return err;
}

int bt_handle_button_cb(uint16_t *but_val) {
    return bt_gatt_notify(NULL, &stsensor_svc.attrs[4], but_val, sizeof(but_val));
}

int notify_sensor_data(SENSOR_DATA_T *sensor_vals) {
    return bt_gatt_notify(NULL, &stsensor_svc.attrs[5], sensor_vals, sizeof(SENSOR_DATA_T));
}
