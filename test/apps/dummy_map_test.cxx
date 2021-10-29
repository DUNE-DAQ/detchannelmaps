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

  TLOG() << "Dummy Offline channel " << dummy_map->get_offline_channel_from_detector_elements(1, 2, 3, 4);

  std::shared_ptr<ChannelMap> pdps1_map = make_map("ProtoDUNESP1ChannelMap");

  TLOG() << "ProtoDUNESP1 Offline channel " << pdps1_map->get_offline_channel_from_detector_elements(1, 1, 1, 127);

  std::shared_ptr<ChannelMap> vdcb_map = make_map("VDColdboxChannelMap");

  TLOG() << "VDColdbox Offline channel " << vdcb_map->get_offline_channel_from_detector_elements(1, 1, 1, 127);

  TLOG() << "Test complete";
}
