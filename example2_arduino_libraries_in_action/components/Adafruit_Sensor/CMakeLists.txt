cmake_minimum_required(VERSION 3.5)

# add all source files in this directory
idf_component_register(SRCS "Adafruit_Sensor.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES espressif__arduino-esp32
                       )

project(Adafruit_Sensor)