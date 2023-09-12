cmake_minimum_required(VERSION 3.12)
project(detchannelmaps VERSION 1.5.1)

find_package(daq-cmake REQUIRED)
find_package(cetlib REQUIRED)   # Uses the daq-buildtools/cmake/Findcetlib.cmake
find_package(ers REQUIRED)
find_package(logging REQUIRED)
find_package(serialization REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

daq_setup_environment()

daq_codegen( *.jsonnet TEMPLATES Structs.hpp.j2 Nljs.hpp.j2 )

##############################################################################
# Main library

daq_add_library(*.cpp LINK_LIBRARIES ${CETLIB} ${CETLIB_EXCEPT} ers::ers logging::logging serialization::serialization)

##############################################################################
# Python bindings
daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME})

##############################################################################
# Plugins
daq_add_plugin( ProtoDUNESP1ChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( VDColdboxChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2HDChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2VDBottomTPCChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( HDColdboxChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )

##############################################################################
# Integration tests

# ##############################################################################
# Test plugins
daq_add_plugin( DummyChannelMap duneChannelMap TEST LINK_LIBRARIES detchannelmaps )

daq_add_application( dummy_map_test dummy_map_test.cxx TEST LINK_LIBRARIES detchannelmaps )

##############################################################################
# Unit Tests

# daq_add_unit_test(... LINK_LIBRARIES ...)
daq_add_unit_test(TPCChannelMap_test LINK_LIBRARIES detchannelmaps)

##############################################################################

daq_install()
