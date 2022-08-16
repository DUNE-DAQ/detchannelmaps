/**
 * @file HardwareMapService_test.cxx  HardwareMapService class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/HardwareMapService.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE HardwareMapService_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>

using namespace dunedaq;

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

std::string
GetTestFileName()
{
  // HACK, ELF 15-Aug-2022: We always install built code, so that's the best place to look for the test file
  auto install_dir = getenv("DBT_INSTALL_DIR");
  std::string filename = "TestHardwareMap.txt";
  if (install_dir != nullptr) {
    filename = std::string(install_dir) + "/detchannelmaps/share/test/config/TestHardwareMap.txt";
  }
  return filename;
}

BOOST_AUTO_TEST_CASE(Basics)
{
  detchannelmaps::HardwareMapService ms(GetTestFileName());
}

BOOST_AUTO_TEST_CASE(GeoInfo)
{
  uint16_t original_det_link = 0x0f;
  uint16_t original_det_slot = 0xf0;
  uint16_t original_det_crate = 0xa5;
  uint16_t original_det_id = 0x5a;

  uint64_t geo_id = detchannelmaps::HardwareMapService::get_geo_id(original_det_link, original_det_slot, original_det_crate, original_det_id);
  detchannelmaps::HardwareMapService::GeoInfo geo_info = detchannelmaps::HardwareMapService::parse_geo_id(geo_id);

  BOOST_REQUIRE_EQUAL(geo_info.det_link, original_det_link);
  BOOST_REQUIRE_EQUAL(geo_info.det_slot, original_det_slot);
  BOOST_REQUIRE_EQUAL(geo_info.det_crate, original_det_crate);
  BOOST_REQUIRE_EQUAL(geo_info.det_id, original_det_id);
}

BOOST_AUTO_TEST_SUITE_END()
