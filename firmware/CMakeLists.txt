# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

add_definitions(
  -DARDUINO_USB_MODE
  -DARDUINO_USB_CDC_ON_BOOT
)
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/rf24-port/components/mirf)
project(3mode-controller)
