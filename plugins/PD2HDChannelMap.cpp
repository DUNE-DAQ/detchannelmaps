#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2HDChannelMap :  public TPCChannelMap
{
public:
  explicit PD2HDChannelMap() {
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/pd2hd/PD2HDChannelMap_v2.txt";
    m_channel_map.reset(new dune::PD2HDChannelMapSP());
    m_channel_map->ReadMapFromFile(channel_map_file);
    TLOG() << "PD2HDChannelMap Created";
  }

  PD2HDChannelMap(const PD2HDChannelMap&) = delete;            ///< PD2HDChannelMap is not copy-constructible
  PD2HDChannelMap& operator=(const PD2HDChannelMap&) = delete; ///< PD2HDChannelMap is not copy-assignable
  PD2HDChannelMap(PD2HDChannelMap&&) = delete;                 ///< PD2HDChannelMap is not move-constructible
  PD2HDChannelMap& operator=(PD2HDChannelMap&&) = delete;      ///< PD2HDChannelMap is not move-assignable

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

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::PD2HDChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
