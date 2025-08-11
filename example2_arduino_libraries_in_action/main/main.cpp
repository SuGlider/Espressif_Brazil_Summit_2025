#include "Arduino.h"
#include "Adafruit_SHTC3.h"
#include "ICM42670P.h"

#include <Wire.h>

#define RGB_LED_PIN 2      // Pin for RGB LED
#define LED_PIN 10          // Pin for status/blink LED
#define SDA_PIN 7         // I2C SDA pin
#define SCL_PIN 8          // I2C SCL pin

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
// Instantiate an ICM42670 IMU sensor with I2C interface and LSB address set to 0
ICM42670 IMU(Wire,0);

volatile uint8_t irq_received = 0; // Flag set by IMU interrupt

// Interrupt handler for IMU pedometer events
void irq_handler(void) {
  irq_received = 1;
}

void setup() {
  Serial.begin();
  // Wait for serial port to connect (needed for native USB port only)
  while (!Serial) {
    delay(100);
  }
  Serial.println("Hello World from Arduino as Component!");
  
  // Set custom I2C pins for your hardware
  Wire.setPins(SDA_PIN, SCL_PIN);

  // Initialize SHTC3 sensor
  Serial.println("SHTC3 test");
  if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1); // Halt if sensor not found
  }
  Serial.println("Found SHTC3 sensor");

  // Initialize ICM42670 IMU sensor
  int ret = IMU.begin();
  if (ret != 0) {
    Serial.print("ICM42670 initialization failed: ");
    Serial.println(ret);
    while(1); // Halt if IMU init fails
  }
  // Start pedometer with 50 Hz ODR and register interrupt handler
  IMU.startPedometer(2,irq_handler);
  Serial.println("ICM42670 Pedometer initialized successfully");

  // Initialize RGB LED and status LED pins
  pinMode(RGB_LED_PIN, OUTPUT);
  digitalWrite(RGB_LED_PIN, LOW); // Turn off RGB LED initially
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);    // Turn on status LED
}

void loop() {
  static int count = 0;

  // Blink status LED
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);

  // Cycle RGB LED through colors
  rgbLedWrite(RGB_LED_PIN, 64, 64, 64); // White
  delay(250);
  rgbLedWrite(RGB_LED_PIN, 0, 0, 0);   // Off
  delay(250);
  rgbLedWrite(RGB_LED_PIN, 64, 0, 0);  // Red
  delay(250);
  rgbLedWrite(RGB_LED_PIN, 0, 64, 0);  // Green
  delay(250);
  rgbLedWrite(RGB_LED_PIN, 0, 0, 64);  // Blue
  delay(250);
  rgbLedWrite(RGB_LED_PIN, 0, 0, 0);   // Off
  delay(250);

  // Print loop count
  Serial.printf("Count: %d", count++);
  Serial.println();

  // Read and print SHTC3 temperature and humidity
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp); // Get fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  // If IMU interrupt received, print pedometer data
  if(irq_received) {
    uint32_t step_count=0;
    float step_cadence=0;
    const char* activity;
    irq_received = 0;
    IMU.getPedometer(step_count,step_cadence,activity);
    Serial.println("==================================");
    Serial.print("Step count:");
    Serial.println(step_count);
    Serial.print("Step cadence:");
    Serial.println(step_cadence);
    Serial.print("activity:");
    Serial.println(activity);
    Serial.println("==================================");
  }
}
