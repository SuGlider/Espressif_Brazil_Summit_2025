// This example code is in the Public Domain (or CC0 licensed, at your option.)
// The code demonstrates how to use the IDF Component created from the ESP-IDF Blink Example
// in an Arduino sketch, using Arduino as Component.
// It blinks an LED connected to a GPIO pin or an addressable LED strip if configured.

#include <Arduino.h>
#include "blink_idf_component.h"

// Define the GPIO pin where the LED is connected
// the red LED on the RUST board will be controlled using Arduino API
const int ledPin = 10;  // LED connected to GPIO pin 10

void setup() {
    // Configure the peripheral according to the LED type
    // By default the example is configured to blink the RGB LED connected to an addressable LED strip on GPIO 2
    // This can be changed in the project configuration menu (idf.py menuconfig)
    configure_led();

    // Arduino allows to use both the regular red LED on pin 10 or the addressable color LED o pin 2 
    pinMode(ledPin, OUTPUT); // Set the LED pin as an output

}

void loop() {
    static bool ledOn = false; // Track the LED state

    log_i("Turning the RED LED %s", ledOn == true ? "ON" : "OFF");

    blink_led(0, 32, 64); // Example: Set LED to blueish cyan color (R, G, B values from 0 to 255)
    // For a simple on/off LED, you might use - it works with the red LED on pin 10 and/or the addressable LED strip on GPIO 2
    digitalWrite(ledPin, ledOn ? HIGH : LOW); // Turn the LED on or off
    ledOn = !ledOn; // Toggle the Arduiino contorlled LED state

    delay(CONFIG_BLINK_PERIOD); // Wait for the configured blink period (in milliseconds) - this is set in the project configuration menu
}

