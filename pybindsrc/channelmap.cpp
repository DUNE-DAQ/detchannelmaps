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

  py::class_<TPCChannelMap::TPCChannelInfo>(m, "TPCChannelInfo")
    .def(py::init<uint, uint, uint, uint>())
    .def_readwrite("detector", &TPCChannelMap::TPCChannelInfo::detector)
    .def_readwrite("crate", &TPCChannelMap::TPCChannelInfo::crate)
    .def_readwrite("slot", &TPCChannelMap::TPCChannelInfo::slot)
    .def_readwrite("fiber", &TPCChannelMap::TPCChannelInfo::fiber)
    .def_readwrite("channel", &TPCChannelMap::TPCChannelInfo::channel)
    .def_readwrite("tpc_element", &TPCChannelMap::TPCChannelInfo::tpc_element)
  ;

  py::class_<TPCChannelMap, std::shared_ptr<TPCChannelMap>>(m, "TPCChannelMap")
    .def("get_offline_channel_from_det_crate_slot_stream_chan", &TPCChannelMap::get_offline_channel_from_det_crate_slot_stream_chan)
    .def("get_plane_from_offline_channel", &TPCChannelMap::get_plane_from_offline_channel)
    .def("get_element_id_from_offline_channel", &TPCChannelMap::get_element_id_from_offline_channel)
    .def("get_element_name_from_offline_channel", &TPCChannelMap::get_element_name_from_offline_channel)
    .def("get_channel_info_from_offline_channel", &TPCChannelMap::get_channel_info_from_offline_channel)
  ;

  m.def("make_tpc_map", &make_tpc_map);

}

} // namespace python
} // namespace detchannelmaps
} // namespace dunedaq
