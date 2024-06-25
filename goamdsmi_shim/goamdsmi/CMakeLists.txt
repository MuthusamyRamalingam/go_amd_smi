# SPDX-License-Identifier: MIT

set(goamdsmi_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi_shim.h
  CACHE INTERNAL "")

set(goamdsmi_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi_shim.c
    CACHE INTERNAL "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${goamdsmi_includes})

add_library(goamdsmi_ OBJECT
            ${goamdsmi_sources}
            ${goamdsmi_headers})

### Shared libraries need PIC
set_property(TARGET ${goamdsmi_} PROPERTY POSITION_INDEPENDENT_CODE 1)

