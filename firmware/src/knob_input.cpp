#include "knob_input.h"
#include "io_pins.h"

const int MID = 2048;  // Midpoint for 12-bit ADC (range 0–4095)

void updateKnobs() {
    int panLock = digitalRead(PAN_LOCK_PIN);
    int tiltLock = digitalRead(TILT_LOCK_PIN);

    // Read the values of the potentiometers
    int panVal = analogRead(POT_PAN_PIN);
    int tiltVal = analogRead(POT_TILT_PIN);

    // Get the potentiometers' offset from the middle position
    int panOffset = panVal - MID;
    int tiltOffset = tiltVal - MID;

    if (!panLock) {
        Serial.print("Pan: ");
        Serial.print(panOffset);
        Serial.print(" ");
    }

    if (!tiltLock) {
        Serial.print("Tilt: ");
        Serial.print(tiltOffset);
        Serial.println();
    }
}
