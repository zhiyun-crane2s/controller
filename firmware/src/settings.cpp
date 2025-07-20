#include "settings.h"
#include <Preferences.h>

Settings currentSettings;

void loadSettings() {
    Preferences prefs;
    prefs.begin("gimbalbox", true); // read-only

    // Connection method 1: Connecting to the app
    currentSettings.wifi_ssid = prefs.getString("wifi_ssid", "");
    currentSettings.wifi_pass = prefs.getString("wifi_pass", "");
    currentSettings.phone_ip = prefs.getString("phone_ip", "");
    currentSettings.websocket_port = prefs.getInt("port", 8080);

    // Connection method 2: Connecting to the gimbal
    currentSettings.gimbal_mac = prefs.getString("gimbal_mac", "");

    currentSettings.led_enabled = prefs.getBool("led", true);
    currentSettings.smoothness = prefs.getFloat("smooth", 0.8);
    prefs.end();
}

void saveSettings() {
    Preferences prefs;
    prefs.begin("gimbalbox", false); // Write mode

    prefs.putString("phone_ip", currentSettings.phone_ip);
    prefs.putInt("port", currentSettings.websocket_port);
    prefs.putString("gimbal_mac", currentSettings.gimbal_mac);
    prefs.putBool("led", currentSettings.led_enabled);
    prefs.putFloat("smooth", currentSettings.smoothness);

    prefs.end();
    Serial.println("Settings saved.");
}