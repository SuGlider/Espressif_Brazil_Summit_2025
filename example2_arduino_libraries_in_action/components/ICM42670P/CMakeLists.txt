cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp" "src/imu/*.c" "src/imu/*.cpp" "src/Invn/*.c" "src/Invn/*.cpp")

idf_component_register(
  SRCS ${SOURCES}
  INCLUDE_DIRS "src" "src/imu" "src/Invn"
  REQUIRES espressif__arduino-esp32
)

project(ICM42670P)
