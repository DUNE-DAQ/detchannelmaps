/**
 * @file hardwaremapservice.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/HardwareMapService.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iomanip>

namespace py = pybind11;

namespace dunedaq {
namespace detchannelmaps {
namespace python {

void
register_hw_map_service(py::module& m)
{
  py::class_<HardwareMapService> py_hwmapservice(m, "HardwareMapService");

  py::class_<hardwaremapservice::HWInfo> py_hwmapservice_hwinfo(m, "HWInfo");
  py_hwmapservice_hwinfo.def(py::init());
  py_hwmapservice_hwinfo.def_readwrite("dro_source_id", &hardwaremapservice::HWInfo::dro_source_id)
    .def_readwrite("det_link", &hardwaremapservice::HWInfo::det_link)
    .def_readwrite("det_slot", &hardwaremapservice::HWInfo::det_slot)
    .def_readwrite("det_crate", &hardwaremapservice::HWInfo::det_crate)
    .def_readwrite("det_id", &hardwaremapservice::HWInfo::det_id)
    .def_readwrite("dro_host", &hardwaremapservice::HWInfo::dro_host)
    .def_readwrite("dro_card", &hardwaremapservice::HWInfo::dro_card)
    .def_readwrite("dro_slr", &hardwaremapservice::HWInfo::dro_slr)
    .def_readwrite("dro_link", &hardwaremapservice::HWInfo::dro_link)
    .def_readwrite("from_file", &hardwaremapservice::HWInfo::from_file);

  py::class_<hardwaremapservice::DROInfo> py_hwmapservice_droinfo(m, "DROInfo");
  py_hwmapservice_droinfo.def(py::init());
  py_hwmapservice_droinfo.def_readwrite("host", &hardwaremapservice::DROInfo::host)
    .def_readwrite("card", &hardwaremapservice::DROInfo::card)
    .def_readwrite("links", &hardwaremapservice::DROInfo::links);

  py::class_<hardwaremapservice::GeoInfo> py_hwmapservice_geoinfo(m, "GeoInfo");
  py_hwmapservice_geoinfo.def(py::init());
  py_hwmapservice_geoinfo.def_readwrite("det_link", &hardwaremapservice::GeoInfo::det_link)
    .def_readwrite("det_slot", &hardwaremapservice::GeoInfo::det_slot)
    .def_readwrite("det_crate", &hardwaremapservice::GeoInfo::det_crate)
    .def_readwrite("det_id", &hardwaremapservice::GeoInfo::det_id);

  py::class_<hardwaremapservice::HardwareMap> py_hwmapservice_hardwaremap(m, "HardwareMap");
  py_hwmapservice_hardwaremap.def(py::init());
  py_hwmapservice_hardwaremap.def_readwrite("link_infos", &hardwaremapservice::HardwareMap::link_infos);

  py_hwmapservice.def(py::init<std::string>());
  py_hwmapservice.def(py::init<hardwaremapservice::HardwareMap>());

  py_hwmapservice.def("get_hardware_map", &HardwareMapService::get_hardware_map)
      .def("get_hardware_map_json", &HardwareMapService::get_hardware_map_json)
    .def("get_hw_info_from_source_id", &HardwareMapService::get_hw_info_from_source_id)
    .def("get_hw_info_from_geo_id", &HardwareMapService::get_hw_info_from_geo_id)
    .def("get_geo_id", py::overload_cast<hardwaremapservice::HWInfo>(&HardwareMapService::get_geo_id))
    .def("get_geo_id", py::overload_cast<const uint16_t, const uint16_t, const uint16_t, const uint16_t>(&HardwareMapService::get_geo_id))
    .def("parse_geo_id", &HardwareMapService::parse_geo_id)
    .def("get_all_dro_info", &HardwareMapService::get_all_dro_info)
    .def("get_dro_info", &HardwareMapService::get_dro_info);
}

} // namespace python
} // namespace detchannelmaps
} // namespace dunedaq
