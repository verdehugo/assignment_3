# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Machine_Vending)

target_sources(app PRIVATE app/main.c)

target_sources(app PRIVATE src/main.c ../VendMachine/src-gen/VM.c)

target_include_directories(app PRIVATE ../VendMachine/src-gen ../VendMachine/src)
