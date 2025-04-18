# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(color_sensor_i2c)

target_sources(app PRIVATE src/main.c)
