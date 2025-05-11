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

int
main()
{
  TLOG() << "Creating Module instances...";
  std::shared_ptr<TPCChannelMap> dummy_map = make_tpc_map("DummyTPCChannelMap");

  uint oc, plane, elem_id;
  std::string elem_name;

  oc = dummy_map->get_offline_channel_from_det_crate_slot_stream_chan(0, 1, 2, 3, 4);
  plane = dummy_map->get_tpc_plane_from_offline_channel(oc);
  elem_id = dummy_map->get_tpc_element_id_from_offline_channel(oc);
  elem_name = dummy_map->get_tpc_element_name_from_offline_channel(oc);
  TLOG() << "Dummy Offline channel " << oc << " plane " <<  plane << " element " << elem_id << " name '" << elem_name << "'";
 
  // std::shared_ptr<TPCChannelMap> pdps1_map = make_tpc_map("ProtoDUNESP1ChannelMap");

  // oc = pdps1_map->get_offline_channel_from_det_crate_slot_stream_chan(10, 1, 1, 1, 127);
  // plane = pdps1_map->get_tpc_plane_from_offline_channel(oc);
  // TLOG() << "ProtoDUNESP1 Offline channel " << oc << " plane " << plane;

  // std::shared_ptr<TPCChannelMap> vdcb_map = make_tpc_map("VDColdboxChannelMap");

  // oc = vdcb_map->get_offline_channel_from_det_crate_slot_stream_chan(10, 1, 1, 1, 127);
  // plane = vdcb_map->get_tpc_plane_from_offline_channel(oc);
  // TLOG() << "VDColdbox Offline channel " << oc << " plane " << plane;

  // std::shared_ptr<TPCChannelMap> pd2hd_map = make_tpc_map("PD2HDChannelMap");

  // oc = pd2hd_map->get_offline_channel_from_det_crate_slot_stream_chan(10, 1, 1, 1, 127);
  // plane = pd2hd_map->get_tpc_plane_from_offline_channel(oc);
  // TLOG() << "PD2HD Offline channel " << oc << " plane " << plane;

  std::shared_ptr<TPCChannelMap> hdcb_map = make_tpc_map("HDColdboxTPCChannelMap");

  oc = hdcb_map->get_offline_channel_from_det_crate_slot_stream_chan(3, 1, 1, 1, 127);
  plane = hdcb_map->get_tpc_plane_from_offline_channel(oc);
  elem_id = hdcb_map->get_tpc_element_id_from_offline_channel(oc);
  elem_name = hdcb_map->get_tpc_element_name_from_offline_channel(oc);
  TLOG() << "HDColdbox Offline channel " << oc << " plane " << plane << " element " << elem_id << " name '" << elem_name << "'";

  std::shared_ptr<TPCChannelMap> pdvd2_map = make_tpc_map("PD2VDTPCChannelMap");

  oc = pdvd2_map->get_offline_channel_from_det_crate_slot_stream_chan(10, 10, 0, 0, 52);
  plane = pdvd2_map->get_tpc_plane_from_offline_channel(oc);
  elem_id = pdvd2_map->get_tpc_element_id_from_offline_channel(oc);
  elem_name = pdvd2_map->get_tpc_element_name_from_offline_channel(oc);
  TLOG() << "PD2VD Offline channel " << oc << " plane " <<  plane << " element " << elem_id << " name '" << elem_name << "'";


  TLOG() << "Test complete";
}
