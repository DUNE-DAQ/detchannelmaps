/**
 * @file DummyModule.hpp
 *
 * DummyModule is a simple ChannelMap implementation that responds to a "stuff" command with a log message.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DETCHANNELMAPS_TEST_PLUGINS_DUMMYCHANNELMAP_HPP_
#define DETCHANNELMAPS_TEST_PLUGINS_DUMMYCHANNELMAP_HPP_

#include "detchannelmaps/TPCChannelMap.hpp"

#include "ers/Issue.hpp"

#include <string>
#include <vector>

namespace dunedaq {

// Disable coverage collection LCOV_EXCL_START
// ERS_DECLARE_ISSUE_BASE(detchannelmaps,
//                        DummyModuleUpdate,
//                        detchannelmaps::GeneralChannelMapIssue,
//                        message,
//                        ((std::string)name),
//                        ((std::string)message))
// Re-enable coverage collection LCOV_EXCL_STOP

namespace detchannelmaps {

class DummyChannelMap : public TPCChannelMap
{
public:
  explicit DummyChannelMap() {}
  DummyChannelMap(const DummyChannelMap&) = delete;            ///< DummyChannelMap is not copy-constructible
  DummyChannelMap& operator=(const DummyChannelMap&) = delete; ///< DummyChannelMap is not copy-assignable
  DummyChannelMap(DummyChannelMap&&) = delete;                 ///< DummyChannelMap is not move-constructible
  DummyChannelMap& operator=(DummyChannelMap&&) = delete;      ///< DummyChannelMap is not move-assignable

  uint get_offline_channel_from_crate_slot_fiber_chan(uint /*crate*/,
                                                      uint /*slot*/,
                                                      uint /*fiber*/,
                                                      uint /*fembchannel*/) final
  {
    return 5678;
  }

  uint get_plane_from_offline_channel(uint /*offchannel*/) final { return 2; }
};

} // namespace detchannelmaps
} // namespace dunedaq

#endif // DETCHANNELMAPS_TEST_PLUGINS_DUMMYCHANNELMAP_HPP_

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::DummyChannelMap)