/**
 * @file dummy_map_example.cxx
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/ChannelMap.hpp"

#include "logging/Logging.hpp" // NOLINT

#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace dunedaq::detchannelmaps;

int
main()
{
  TLOG() << "Creating Module instances...";
  std::shared_ptr<ChannelMap> dummy_map = make_map("DummyChannelMap");

  TLOG() << "Offile channel " << dummy_map->get_offline_channel_from_detector_elements(1, 2, 3, 4);

  TLOG() << "Test complete";
}
