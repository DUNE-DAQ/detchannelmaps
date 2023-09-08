/**
 * @file wib.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/TPCChannelMap.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iomanip>

namespace py = pybind11;

namespace dunedaq {
namespace detchannelmaps {
namespace python {

void
register_maps(py::module& m)
{

  py::class_<TPCChannelMap::TPCCoords>(m, "TPCCoords")
    .def(py::init<uint, uint, uint, uint>())
    .def_readwrite("crate", &TPCChannelMap::TPCCoords::crate)
    .def_readwrite("slot", &TPCChannelMap::TPCCoords::slot)
    .def_readwrite("fiber", &TPCChannelMap::TPCCoords::fiber)
    .def_readwrite("channel", &TPCChannelMap::TPCCoords::channel)
  ;

  py::class_<TPCChannelMap, std::shared_ptr<TPCChannelMap>>(m, "TPCChannelMap")
    .def("get_plane_from_offline_channel", &TPCChannelMap::get_plane_from_offline_channel)
    .def("get_apa_from_offline_channel", &TPCChannelMap::get_apa_from_offline_channel)
    .def("get_offline_channel_from_crate_slot_fiber_chan", &TPCChannelMap::get_offline_channel_from_crate_slot_fiber_chan)
    .def("get_offline_channel_from_crate_slot_stream_chan", &TPCChannelMap::get_offline_channel_from_crate_slot_stream_chan)
    .def("get_crate_slot_fiber_chan_from_offline_channel", &TPCChannelMap::get_crate_slot_fiber_chan_from_offline_channel)
  ;

  m.def("make_map", &make_map);

}

} // namespace python
} // namespace detchannelmaps
} // namespace dunedaq
