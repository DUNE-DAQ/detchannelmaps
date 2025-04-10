#include "detchannelmaps/PDSChannelMap.hpp"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class DummyHDPDSChannelMap :  public PDSChannelMap
{
public:

  static constexpr uint kHD_PDS_DetId = 2;

  explicit DummyHDPDSChannelMap() {
  
    // const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    // if (!detchannelmaps_share_cstr) {
    //   throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    // }
    // std::string detchannelmaps_share(detchannelmaps_share_cstr);
    // std::string channel_map_file = detchannelmaps_share + "/config/50L/50LChannelMap_v1.txt";
    // m_channel_map.reset(new dune::PD2HDChannelMapSP());
    // m_channel_map->ReadMapFromFile(channel_map_file);
    // TLOG_DEBUG(10) << "FiftyLChannelMap Created";
  }

  DummyHDPDSChannelMap(const DummyHDPDSChannelMap&) = delete;            ///< DummyHDPDSChannelMap is not copy-constructible
  DummyHDPDSChannelMap& operator=(const DummyHDPDSChannelMap&) = delete; ///< DummyHDPDSChannelMap is not copy-assignable
  DummyHDPDSChannelMap(DummyHDPDSChannelMap&&) = delete;                 ///< DummyHDPDSChannelMap is not move-constructible
  DummyHDPDSChannelMap& operator=(DummyHDPDSChannelMap&&) = delete;      ///< DummyHDPDSChannelMap is not move-assignable

  uint get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) final {
    if (det != kHD_PDS_DetId) {
      return 9999;
    }
    return det*10000+crate*100+channel;
  }

  std::optional<PDSCoords> 
  get_det_crate_slot_fiber_chan_from_offline_channel(uint offchannel) final {

    if ((uint)(offchannel/10000) != kHD_PDS_DetId) {
      return std::nullopt;
    }
    return PDSCoords{(uint)(offchannel / 10000), (uint)((offchannel % 10000) / 100), 0, offchannel % 100};
  }


  uint get_element_from_offline_channel(uint offchannel) final 
  {
    return (uint)((offchannel % 10000) / 100);
  }

};

DEFINE_DUNE_DET_PDSCHANNEL_MAP(dunedaq::detchannelmaps::DummyHDPDSChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
