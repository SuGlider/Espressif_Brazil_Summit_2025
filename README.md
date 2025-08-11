| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-H21 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | --------- | -------- | -------- | -------- |

# Espressif Brazil Summit 2025
Repository for the "Arduino as an ESP-IDF Component: Flexible Development Made Simple" workshop

## Arduino as Component Blink Example

This is part of the Espressif Brazil Summit 2025 workshop about "how to accelerate IDF development using Arduino as IDF Component"

The workshop was based on using the [RUST board](https://github.com/esp-rs/esp-rust-board) version designed for the workshop. It is the same as the ESP-Rust-Board v1.2 but the LED and I2C SDA pins are swapped (LED is IO 10 and I2C SDA is Io 7)

This example demonstrates how to use an ESP-IDF component in an Arduino sketch. It shows how to blink both a regular GPIO LED and an addressable LED using Arduino APIs alongside ESP-IDF components. By default, the example uses:
- Arduino GPIO control for a regular LED on GPIO 10
- [led_strip](https://components.espressif.com/component/espressif/led_strip) component from ESP-IDF for an addressable LED (e.g., [WS2812](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf))
The `led_strip` library is installed via [component manager](main/idf_component.yml).

## How to Use Example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target esp32c3`. This example is specifically designed for the ESP32-C3 RUST board.

### Hardware Required

* A development board (any) with:
  * A regular LED on GPIO 10 (e.g., the red LED on ESP32-C3 RUST boards)
  * An addressable LED on GPIO 2 (e.g., RGB LED on ESP32-C3 RUST boards)
* A USB cable for Power supply and programming

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

The IDF Component GPIO can be changed using the `idf.py menuconfig` command to change the `LED IDF Component Example Configuration` menu item. For the Arduino sketch, it is necessary to change the code line `const int ledPin = 10;` in the `main/main.cpp` file.

### Configure the Project

Open the project configuration menu (`idf.py menuconfig`).

In the `Example Configuration` menu:

* Select the LED type in the `Blink LED type` option.
  * Use `GPIO` for regular LED
  * Use `LED strip` for addressable LED
* If the LED type is `LED strip`, select the backend peripheral
  * `RMT` is only available for ESP targets with RMT peripheral supported
  * `SPI` is available for all ESP targets
* Set the GPIO number used for the signal in the `Blink GPIO number` option.
* Set the blinking period in the `Blink period in ms` option.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the example, you will see both LEDs blinking:
- The regular red LED on GPIO 10 is controlled using Arduino's `digitalWrite()`
- The addressable LED on GPIO 2 can display different colors by calling `blink_led()` with RGB values from 0 to 255 in the [source file](main/main.cpp)

For example, `blink_led(0, 32, 64)` sets a blueish cyan color (R=0, G=32, B=64).

```text
[   518][I][main.cpp:27] loop(): Turning the RED LED ON
E (628) IDF_Component_BLINK: Turning the RGB LED OFF
[  1023][I][main.cpp:27] loop(): Turning the RED LED OFF
E (1133) IDF_Component_BLINK: Turning the RGB LED ON
[  1528][I][main.cpp:27] loop(): Turning the RED LED ON
E (1638) IDF_Component_BLINK: Turning the RGB LED OFF
[  2038][I][main.cpp:27] loop(): Turning the RED LED OFF
E (2148) IDF_Component_BLINK: Turning the RGB LED ON
[  2543][I][main.cpp:27] loop(): Turning the RED LED ON
E (2653) IDF_Component_BLINK: Turning the RGB LED OFF
[  3048][I][main.cpp:27] loop(): Turning the RED LED OFF
```

Note: The color order could be different according to the LED model.

The pixel number indicates the pixel position in the LED strip. For a single LED, use 0.

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.

For any technical queries, please open an [issue](https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you soon.
