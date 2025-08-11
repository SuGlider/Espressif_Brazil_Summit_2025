cmake_minimum_required(VERSION 3.5)

# add all source files in this directory
idf_component_register(SRCS "Adafruit_SHTC3.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES espressif__arduino-esp32
                       PRIV_REQUIRES Adafruit_BusIO
                       PRIV_REQUIRES Adafruit_Sensor
                       )

project(Adafruit_SHTC3)
