#
# Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(smmu C)

set(configure_string "")
config_option(
    AppSmmuBench
    APP_SMMUBENCH
    "Application to benchmark smmu."
    DEFAULT
    ON
    DEPENDS
    "DefaultBenchDeps"
)
add_config_library(sel4benchsmmu "${configure_string}")

file(GLOB deps src/*.c)
list(SORT deps)
add_executable(smmu EXCLUDE_FROM_ALL ${deps})
target_link_libraries(
    smmu
    sel4_autoconf
    sel4benchsmmu_Config
    sel4
    muslc
    cpio
    sel4vka
    sel4vspace
    sel4allocman
    sel4utils
    sel4muslcsys
    elf
    sel4simple
    sel4bench
    sel4benchsupport
    sel4debug
    platsupport
    sel4platsupport
)

if(AppSmmuBench)
    set_property(GLOBAL APPEND PROPERTY sel4benchapps_property "$<TARGET_FILE:smmu>")
endif()
