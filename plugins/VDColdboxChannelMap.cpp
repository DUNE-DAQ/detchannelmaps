#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class VDColdboxChannelMap :  public TPCChannelMap
{
public:
  explicit VDColdboxChannelMap() {
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/vdcoldbox/vdcbce_chanmap_v4.txt";
    m_channel_map.reset(new dune::PD2HDChannelMapSP());
    m_channel_map->ReadMapFromFile(channel_map_file);
    TLOG_DEBUG(10) << "VDColdboxChannelMap Created";
  }

  VDColdboxChannelMap(const VDColdboxChannelMap&) = delete;            ///< VDColdboxChannelMap is not copy-constructible
  VDColdboxChannelMap& operator=(const VDColdboxChannelMap&) = delete; ///< VDColdboxChannelMap is not copy-assignable
  VDColdboxChannelMap(VDColdboxChannelMap&&) = delete;                 ///< VDColdboxChannelMap is not move-constructible
  VDColdboxChannelMap& operator=(VDColdboxChannelMap&&) = delete;      ///< VDColdboxChannelMap is not move-assignable

  uint get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint link, uint wibframechan) final {

    auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
        crate, slot, link, wibframechan
    );

    if (!chan_info.valid) {
      return -1;
    }

    return chan_info.offlchan;

  }

  uint get_plane_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return 9999;
    }

    return chan_info.plane;
  };

private:

  std::unique_ptr<dune::PD2HDChannelMapSP> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::VDColdboxChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
