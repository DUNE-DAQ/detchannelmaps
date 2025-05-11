#include "detchannelmaps/TPCChannelMap.hpp"
#include "TPCChannelMapSP.h"
#include "fmt/core.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2VDTPCChannelMap :  public TPCChannelMap
{
public:

  explicit PD2VDTPCChannelMap() {
  
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/pd2vd/PD2VDTPCChannelMap_v1.txt";
    m_channel_map.reset(new dune::TPCChannelMapSP());
    m_channel_map->ReadMapFromFile(channel_map_file);
    TLOG_DEBUG(10) << "PD2VDTPCChannelMap Created";
  }

  PD2VDTPCChannelMap(const PD2VDTPCChannelMap&) = delete;            ///< PD2VDTPCChannelMap is not copy-constructible
  PD2VDTPCChannelMap& operator=(const PD2VDTPCChannelMap&) = delete; ///< PD2VDTPCChannelMap is not copy-assignable
  PD2VDTPCChannelMap(PD2VDTPCChannelMap&&) = delete;                 ///< PD2VDTPCChannelMap is not move-constructible
  PD2VDTPCChannelMap& operator=(PD2VDTPCChannelMap&&) = delete;      ///< PD2VDTPCChannelMap is not move-assignable


  /**
   * @brief Get the offline channel from detector crate slot stream chan object
   * 
   * @param det 
   * @param crate 
   * @param slot 
   * @param stream 
   * @param channel 
   * 
   * @return offline channel identifier
   */
  uint 
  get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) final {
  
    auto ch_info = m_channel_map->GetChanInfoFromElectronicsIDs(det, crate, slot, stream, channel );
    return ( ch_info.valid ? ch_info.offlchan : 9999 );
  }


  /**
   * @brief Get the plane from offline channel object
   * 
   * @param offchannel 
   * @return plane id (0, 1 or 2) 
   */
  uint 
  get_tpc_plane_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return 9999;
    }

    return chan_info.plane;
  };


  /**
   * @brief Get the element id from offline channel object
   * 
   * @param offchannel 
   * @return uint 
   */
  uint
  get_tpc_element_id_from_offline_channel( uint offchannel) {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return 9999;
    }

    return chan_info.detelement;
  }

  /**
   * @brief Get the tpc element name from offline channel object
   * 
   * @param offchannel 
   * @return std::string 
   */
  std::string 
  get_tpc_element_name_from_offline_channel( uint offchannel) {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return "xxx";
    }

    return fmt::format("CRP{:d}", chan_info.detelement);
  }

  std::optional<TPCChannelInfo> 
  get_tpc_channel_info_from_offline_channel(uint offchannel) {
    auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if ( !ci.valid) {
      return std::nullopt;
    }
    return TPCChannelInfo{ci.detid, ci.crate, ci.slot, ci.stream, ci.streamchan, ci.detelement};
  }



private:

  std::unique_ptr<dune::TPCChannelMapSP> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::PD2VDTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
