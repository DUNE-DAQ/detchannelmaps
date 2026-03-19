cmake_minimum_required(VERSION 3.12)
project(detchannelmaps VERSION 1.10.0)

find_package(daq-cmake REQUIRED)
find_package(ers REQUIRED)
find_package(logging REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

daq_setup_environment()

#daq_codegen( *.jsonnet TEMPLATES Structs.hpp.j2 Nljs.hpp.j2 )

##############################################################################
# Main library

daq_add_library(src/tpc/*.cpp src/pds/*.cpp LINK_LIBRARIES ers::ers logging::logging fmt::fmt)

##############################################################################
# Python bindings
daq_add_python_bindings(*.cpp)

##############################################################################
# Integration tests

daq_add_application( detchannelmaps_tpcmap_test tpcmap_test.cxx TEST LINK_LIBRARIES detchannelmaps fmt::fmt )
# DummyTPCChannelMap is a test-only implementation; compile it directly into the test binary
target_sources( detchannelmaps_tpcmap_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/plugins/DummyTPCChannelMap.cpp )

##############################################################################
# Unit Tests

# daq_add_unit_test(... LINK_LIBRARIES ...)
daq_add_unit_test(TPCChannelMap_test LINK_LIBRARIES detchannelmaps)

##############################################################################

daq_install()
