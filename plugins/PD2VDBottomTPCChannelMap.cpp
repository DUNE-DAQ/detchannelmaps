#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2VDBottomTPCChannelMap :  public TPCChannelMap {
private:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 10;
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

    // Must be a BDE channel 
    if( det != kDetID) 
      return -1;

    // if stream number looks wrong (not 0,1,2,3 or 64,65,66,67)
    if( (stream & 0xbc) ) 
      return -1;
    
    constexpr uint n_chan_per_stream = 64;

    uint link = (stream >> 6) & 1;
    uint stream_in_link = (stream & 0x3);
    uint wibframechan = n_chan_per_stream*stream_in_link+channel;

    auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
        crate, slot, link, wibframechan
    );

    if (!chan_info.valid) {
      return -1;
    }

    return chan_info.offlchan;    
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
      return -1;
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
      return -1;
    }


    // Brute force approack
    if(chan_info.APAName=="4") return 4;
    if(chan_info.APAName=="5") return 5;

    // There is only one element
    return 0;
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
      return "";
    }

    return chan_info.APAName;
  }


  std::optional<TPCChannelInfo> 
  get_tpc_channel_info_from_offline_channel(uint offchannel) {
    auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if ( !ci.valid) {
      return std::nullopt;
    }
    return TPCChannelInfo{kDetID, ci.crate, ci.wib-1, ci.link, ci.wibframechan, 0};
  }


private:

  std::unique_ptr<dune::PD2HDChannelMapSP> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::PD2VDBottomTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
