/**
 * @file TPCChannelMap_test.cxx  TPCChannelMap class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/TPCChannelMap.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TPCChannelMap_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>

using namespace dunedaq;

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(Basics)
{
  auto ptr = detchannelmaps::make_map("HDColdboxChannelMap");
  BOOST_REQUIRE(ptr != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
