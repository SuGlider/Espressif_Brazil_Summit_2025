| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-H21 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | --------- | -------- | -------- | -------- |

# Espressif Brazil Summit 2025
Repository for the "Arduino as an ESP-IDF Component: Flexible Development Made Simple" workshop

The workshop was based on using the [RUST board](https://github.com/esp-rs/esp-rust-board) version designed for the workshop. It is the same as the ESP-Rust-Board v1.2 but the LED and I2C SDA pins are swapped (LED is IO 10 and I2C SDA is Io 7)

## Example 1: Arduino as Component Blink Example

This example demonstrates how to use an ESP-IDF component in an Arduino sketch. It shows how to blink both a regular GPIO LED and an addressable LED using Arduino APIs alongside ESP-IDF components.

[Access The Code Here](https://github.com/SuGlider/Espressif_Brazil_Summit_2025/blob/main/example1_mixing_idf_and_arduino_components/README.md
)

## Example 2: Arduino as Component using Arduino Libraries Example

This example demonstrates how to use public Arudino Libraries in an Arduino as IDF Component project. It will use Adafurit and TDK Arduino Libraries to read the RUST-Board sensors.

[Access The Code Here](https://github.com/SuGlider/Espressif_Brazil_Summit_2025/blob/main/example2_arduino_libraries_in_action/README.md)
