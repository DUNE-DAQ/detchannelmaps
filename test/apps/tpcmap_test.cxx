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
#include "fmt/core.h"

using namespace dunedaq::detchannelmaps;

void test_tpc_map(const std::string& map_name, int det_id, int crate_id, int slot_id, int stream_id, int chan_id ) {

  TLOG() << "----------------------------------------------------";
  TLOG() << fmt::format("Testing '{}', det={}, crate={}, slot={}, stream={}, channel={}", map_name, det_id, crate_id, slot_id, stream_id, chan_id);

  std::shared_ptr<TPCChannelMap> the_map = make_tpc_map(map_name);

  uint oc, plane, elem_id;
  std::string elem_name;

  oc = the_map->get_offline_channel_from_det_crate_slot_stream_chan(det_id, crate_id, slot_id, stream_id, chan_id);
  plane = the_map->get_plane_from_offline_channel(oc);
  elem_id = the_map->get_element_id_from_offline_channel(oc);
  elem_name = the_map->get_element_name_from_offline_channel(oc);
  auto ci = the_map->get_channel_info_from_offline_channel(oc); 

  if (ci) {
    TLOG() << fmt::format("{} offline channel={}: det={}, crate={}, slot={}, stream={}, channel={}", map_name, oc, ci->detector, ci->crate, ci->slot, ci->stream, ci->channel);
  } else {
    TLOG() << fmt::format("{} channel not found", map_name);
  }
  
  TLOG() << fmt::format("{} offline channel={}: plane={}, element={}, name={}", map_name, oc, plane, elem_id, elem_name);
}

int
main()
{
  TLOG() << "Creating Module instances...";

  uint oc, plane, elem_id;
  std::string elem_name;
 
  test_tpc_map("DummyTPCChannelMap", 1, 2, 3, 4, 5);

  test_tpc_map("VDColdboxChannelMap", 10, 6, 1, 1, 63);

  test_tpc_map("VDColdboxChannelMap", 10, 6, 1, 1, 63);

  test_tpc_map("HDColdboxTPCChannelMap", 3, 1, 1, 1, 45);

  test_tpc_map("PD2VDBottomTPCChannelMap", 10, 10, 0, 0, 52);

  test_tpc_map("PD2VDTPCChannelMap", 10, 10, 0, 0, 52);
  test_tpc_map("PD2VDTPCChannelMap", 11, 8, 0, 0, 52);

  TLOG() << "Test complete";
}
