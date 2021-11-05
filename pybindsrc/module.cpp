/**
 * @file module.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
namespace detchannelmaps {
namespace python {

    extern void register_maps(py::module &);

PYBIND11_MODULE(_daq_detchannelmaps_py, m) {

    m.doc() = "c++ implementation of the dunedaq detchannelmaps modules"; // optional module docstring

    register_maps(m);
}

} // namespace python
} // namespace detchannelmaps
} // namespace dunedaq