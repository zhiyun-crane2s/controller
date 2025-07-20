#include <Arduino.h>
#include "io_pins.h"
#include "settings.h"
#include "led_feedback.h"
#include "knob_input.h"

bool configMode = false;

void setup() {
    Serial.begin(115200);

    // Set the modes of the pins
    pinMode(CONFIG_BTN_PIN, INPUT_PULLUP);
    pinMode(MODE_SW_PIN, INPUT_PULLUP);

    initLED();
    loadSettings();

    // Check if the config button is toggled on
    if (digitalRead(CONFIG_BTN_PIN) == LOW) {
        configMode = true;
        Serial.println("Config mode requested.");
    }

    // If config mode is enabled: Start a WiFi network with a captive portal.
    // The captive portal contains settings.
    if (configMode) {
        setLEDColor(0, 0, 255); // blue
        startConfigPortal();    // stub for config mode
    } else {
        bool wifiMode = (digitalRead(MODE_SW_PIN) == LOW);
        if (wifiMode) {
            Serial.println("Starting Wi-Fi control mode...");
            setLEDColor(0, 255, 0); // green
            // startWiFiControl(); // implement this later
        } else {
            Serial.println("Starting Bluetooth mode...");
            setLEDColor(255, 0, 255); // purple
            // startBluetoothControl(); // implement this later
        }
    }
}

void loop() {
    if (!configMode) {
        updateKnobs();  // read and process analog input
        delay(20);
    }
}
