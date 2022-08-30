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

    py::class_<HardwareMapService::HWInfo> py_hwmapservice_hwinfo(m, "HWInfo");
    py_hwmapservice_hwinfo.def(py::init());
    py_hwmapservice_hwinfo
        .def_readwrite("dro_source_id", &HardwareMapService::HWInfo::dro_source_id)
        .def_readwrite("det_link", &HardwareMapService::HWInfo::det_link)
        .def_readwrite("det_slot", &HardwareMapService::HWInfo::det_slot)
        .def_readwrite("det_crate", &HardwareMapService::HWInfo::det_crate)
        .def_readwrite("det_id", &HardwareMapService::HWInfo::det_id)
        .def_readwrite("dro_host", &HardwareMapService::HWInfo::dro_host)
        .def_readwrite("dro_card", &HardwareMapService::HWInfo::dro_card)
        .def_readwrite("dro_slr", &HardwareMapService::HWInfo::dro_slr)
        .def_readwrite("dro_link", &HardwareMapService::HWInfo::dro_link)
        .def_readwrite("is_valid", &HardwareMapService::HWInfo::is_valid)
        .def_readwrite("geo_id", &HardwareMapService::HWInfo::geo_id)
        ;

    py::class_<HardwareMapService::DROInfo> py_hwmapservice_droinfo(m, "DROInfo");
    py_hwmapservice_droinfo.def(py::init());
    py_hwmapservice_droinfo
        .def_readwrite("host", &HardwareMapService::DROInfo::host)
        .def_readwrite("card", &HardwareMapService::DROInfo::card)
        .def_readwrite("links", &HardwareMapService::DROInfo::links);

    py::class_<HardwareMapService::GeoInfo> py_hwmapservice_geoinfo(m, "GeoInfo");
    py_hwmapservice_geoinfo.def(py::init());
    py_hwmapservice_geoinfo.def_readwrite("det_link", &HardwareMapService::GeoInfo::det_link)
      .def_readwrite("det_slot", &HardwareMapService::GeoInfo::det_slot)
      .def_readwrite("det_crate", &HardwareMapService::GeoInfo::det_crate)
      .def_readwrite("det_id", &HardwareMapService::GeoInfo::det_id);

    py_hwmapservice.def(py::init<std::string>());

    py_hwmapservice.def("get_all_hw_info", &HardwareMapService::get_all_hw_info)
        .def("get_hw_info_from_source_id", &HardwareMapService::get_hw_info_from_source_id)
        .def("get_hw_info_from_geo_id", &HardwareMapService::get_hw_info_from_geo_id)
      .def("get_geo_id", &HardwareMapService::get_geo_id)
      .def("parse_geo_id", &HardwareMapService::parse_geo_id)
        .def("get_all_dro_info", &HardwareMapService::get_all_dro_info)
        .def("get_dro_info", &HardwareMapService::get_dro_info)
        ;
}

} // namespace python
} // namespace detchannelmaps
} // namespace dunedaq
