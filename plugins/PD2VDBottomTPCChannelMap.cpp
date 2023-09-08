#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2VDBottomTPCChannelMap :  public TPCChannelMap
{
public:

  explicit PD2VDBottomTPCChannelMap() {
  
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/pd2vd/PD2VDBottomTPCChannelMap_v1.txt";
    m_channel_map.reset(new dune::PD2HDChannelMapSP());
    m_channel_map->ReadMapFromFile(channel_map_file);
    TLOG_DEBUG(10) << "PD2VDBottomTPCChannelMap Created";
  }

  PD2VDBottomTPCChannelMap(const PD2VDBottomTPCChannelMap&) = delete;            ///< PD2VDBottomTPCChannelMap is not copy-constructible
  PD2VDBottomTPCChannelMap& operator=(const PD2VDBottomTPCChannelMap&) = delete; ///< PD2VDBottomTPCChannelMap is not copy-assignable
  PD2VDBottomTPCChannelMap(PD2VDBottomTPCChannelMap&&) = delete;                 ///< PD2VDBottomTPCChannelMap is not move-constructible
  PD2VDBottomTPCChannelMap& operator=(PD2VDBottomTPCChannelMap&&) = delete;      ///< PD2VDBottomTPCChannelMap is not move-assignable


  uint 
  get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint link, uint wibframechan) final {

    auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
        crate, slot, link, wibframechan
    );

    if (!chan_info.valid) {
      return -1;
    }

    return chan_info.offlchan;

  }


  uint 
  get_plane_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return 9999;
    }

    return chan_info.plane;
  };

  std::string 
  get_apa_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return "";
    }

    return chan_info.APAName;
  };

  std::optional<TPCCoords> 
  get_crate_slot_fiber_chan_from_offline_channel(uint offchannel) {
    auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if ( !ci.valid) {
      return std::nullopt;
    }
    return TPCCoords{ci.crate, ci.wib-1, ci.link, ci.wibframechan};
  }



private:

  std::unique_ptr<dune::PD2HDChannelMapSP> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::PD2VDBottomTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
