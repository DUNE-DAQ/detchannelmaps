/**
 * @file dummy_map_example.cxx
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detchannelmaps/TPCChannelMap.hpp"

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
  std::shared_ptr<TPCChannelMap> dummy_map = make_map("DummyChannelMap");

  uint oc, plane;

  oc = dummy_map->get_offline_channel_from_crate_slot_fiber_chan(1, 2, 3, 4);
  plane = dummy_map->get_plane_from_offline_channel(oc);
  TLOG() << "Dummy Offline channel " << oc << " plane " << plane;

  std::shared_ptr<TPCChannelMap> pdps1_map = make_map("ProtoDUNESP1ChannelMap");

  oc = pdps1_map->get_offline_channel_from_crate_slot_fiber_chan(1, 1, 1, 127);
  plane = pdps1_map->get_plane_from_offline_channel(oc);
  TLOG() << "ProtoDUNESP1 Offline channel " << oc << " plane " << plane;

  std::shared_ptr<TPCChannelMap> vdcb_map = make_map("VDColdboxChannelMap");

  oc = vdcb_map->get_offline_channel_from_crate_slot_fiber_chan(1, 1, 1, 127);
  plane = vdcb_map->get_plane_from_offline_channel(oc);
  TLOG() << "VDColdbox Offline channel " << oc << " plane " << plane;

  std::shared_ptr<TPCChannelMap> pd2hd_map = make_map("PD2HDChannelMap");

  oc = pd2hd_map->get_offline_channel_from_crate_slot_fiber_chan(1, 1, 1, 127);
  plane = pd2hd_map->get_plane_from_offline_channel(oc);
  TLOG() << "PD2HD Offline channel " << oc << " plane " << plane;

  TLOG() << "Test complete";
}
