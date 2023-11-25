/*
 * Copyright (c) 2023 Aaron Chan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ST_BLE_SENSOR_BT_SVC_H_
#define ST_BLE_SENSOR_BT_SVC_H_

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#ifdef __cplusplus
extern "C" {
#endif

void connected(struct bt_conn *connected, uint8_t err);

void disconnected(struct bt_conn *disconn, uint8_t reason);

ssize_t recv(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buff, uint16_t len, uint16_t offset, uint8_t flags);

void mpu_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value);

void sensor_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value);

void bt_ready(int err);

int bt_init();

int bt_handle_button_cb(uint16_t *but_val);

int notify_sensor_data();
#ifdef __cplusplus
}
#endif

#endif
