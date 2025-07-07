cmake_minimum_required(VERSION 3.12)
project(detchannelmaps VERSION 1.9.0)

find_package(daq-cmake REQUIRED)
find_package(cetlib REQUIRED)   # Uses the daq-buildtools/cmake/Findcetlib.cmake
find_package(ers REQUIRED)
find_package(logging REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

daq_setup_environment()

#daq_codegen( *.jsonnet TEMPLATES Structs.hpp.j2 Nljs.hpp.j2 )

##############################################################################
# Main library

daq_add_library(*.cpp LINK_LIBRARIES ${CETLIB} ${CETLIB_EXCEPT} ers::ers logging::logging fmt::fmt) 

##############################################################################
# Python bindings
daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME})

##############################################################################
# Plugins
daq_add_plugin( FiftyLTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( ICEBERGChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )

daq_add_plugin( HDColdboxTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2HDTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )

daq_add_plugin( VDColdboxTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2VDBottomTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )
daq_add_plugin( PD2VDTPCChannelMap duneTPCChannelMap LINK_LIBRARIES detchannelmaps )


daq_add_plugin( SimplePDSChannelMap dunePDSChannelMap LINK_LIBRARIES detchannelmaps )

##############################################################################
# Integration tests

# ##############################################################################
# Test plugins
daq_add_plugin( DummyTPCChannelMap duneTPCChannelMap TEST LINK_LIBRARIES detchannelmaps )

daq_add_application( detchannelmaps_tpcmap_test tpcmap_test.cxx TEST LINK_LIBRARIES detchannelmaps fmt::fmt )

##############################################################################
# Unit Tests

# daq_add_unit_test(... LINK_LIBRARIES ...)
daq_add_unit_test(TPCChannelMap_test LINK_LIBRARIES detchannelmaps)

##############################################################################

daq_install()
