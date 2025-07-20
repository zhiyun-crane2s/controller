#include "led_feedback.h"
#include <Adafruit_NeoPixel.h>
#include "io_pins.h"

Adafruit_NeoPixel led(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLED() {
    led.begin();
    led.show();
}

void setLEDColor(uint8_t r, uint8_t g, uint8_t b) {
    led.setPixelColor(0, led.Color(r, g, b));
    led.show();
}
