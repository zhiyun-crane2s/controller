#pragma once
#include <Arduino.h>

struct Settings {
    // Connection method 1: Connecting to the app
    String wifi_ssid;
    String wifi_pass;
    String phone_ip;
    int websocket_port;

    // Connection method 2: Connecting to the gimbal
    String gimbal_mac;

    // General settings
    bool led_enabled;
    float smoothness;
};

extern Settings currentSettings;

void loadSettings();
void saveSettings();  // for use from config page
