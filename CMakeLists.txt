cmake_minimum_required(VERSION 3.12)
project(detchannelmaps VERSION 1.2.4)

find_package(daq-cmake REQUIRED)
find_package(cetlib REQUIRED)   # Uses the daq-buildtools/cmake/Findcetlib.cmake
find_package(ers REQUIRED)
find_package(logging REQUIRED)

daq_setup_environment()

##############################################################################
# Main library

daq_add_library(*.cpp *.cxx LINK_LIBRARIES ${CETLIB} ${CETLIB_EXCEPT} ers::ers logging::logging)

##############################################################################
# Python bindings
daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME})

##############################################################################
# Plugins
daq_add_plugin( ProtoDUNESP1ChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( VDColdboxChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2HDChannelMap duneChannelMap LINK_LIBRARIES detchannelmaps )
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

##############################################################################

daq_install()
