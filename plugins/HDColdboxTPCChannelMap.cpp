#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class HDColdboxTPCChannelMap :  public PD2HDChannelMapSPPluginBase {
private:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 3;
  
  public:
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit HDColdboxTPCChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "pd2hd/PD2HDChannelMap_v2.txt" ) {

    m_elem_name_id_converter = [](const std::string& apa_name) -> uint {
      // Brute force approack
      if(apa_name=="APA_P02SU") {
        return 1;
      } else if(apa_name=="APA_P01SU") {
        return 2;
      } else if(apa_name=="APA_P02NL") {
        return 3;
      } else if(apa_name=="APA_P01NL") {
        return 4;
      } else {
        return -1;
      }
    };



    TLOG_DEBUG(10) << "HDColdboxTPCChannelMap Created";
  }

  HDColdboxTPCChannelMap(const HDColdboxTPCChannelMap&) = delete;            ///< HDColdboxTPCChannelMap is not copy-constructible
  HDColdboxTPCChannelMap& operator=(const HDColdboxTPCChannelMap&) = delete; ///< HDColdboxTPCChannelMap is not copy-assignable
  HDColdboxTPCChannelMap(HDColdboxTPCChannelMap&&) = delete;                 ///< HDColdboxTPCChannelMap is not move-constructible
  HDColdboxTPCChannelMap& operator=(HDColdboxTPCChannelMap&&) = delete;      ///< HDColdboxTPCChannelMap is not move-assignable

  // /**
  //  * @brief Get the offline channel from detector crate slot stream chan object
  //  * 
  //  * @param det 
  //  * @param crate 
  //  * @param slot 
  //  * @param stream 
  //  * @param channel 
  //  * 
  //  * @return offline channel identifier
  //  */
  // uint 
  // get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) final {

  //   // Must be a BDE channel 
  //   if( det != kDetID) 
  //     return -1;

  //   // if stream number looks wrong (not 0,1,2,3 or 64,65,66,67)
  //   if( (stream & 0xbc) ) 
  //     return -1;
    
  //   constexpr uint n_chan_per_stream = 64;

  //   uint link = (stream >> 6) & 1;
  //   uint stream_in_link = (stream & 0x3);
  //   uint wibframechan = n_chan_per_stream*stream_in_link+channel;

  //   auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
  //       crate, slot, link, wibframechan
  //   );

  //   if (!chan_info.valid) {
  //     return -1;
  //   }

  //   return chan_info.offlchan;    
  // }


  // /**
  //  * @brief Get the plane from offline channel object
  //  * 
  //  * @param offchannel 
  //  * @return plane id (0, 1 or 2) 
  //  */
  // uint 
  // get_tpc_plane_from_offline_channel(uint offchannel) final {
  //   auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

  //   if (!chan_info.valid) {
  //     return -1;
  //   }

  //   return chan_info.plane;
  // };


  // /**
  //  * @brief Get the element id from offline channel object
  //  * 
  //  * @param offchannel 
  //  * @return uint 
  //  */
  // uint
  // get_tpc_element_id_from_offline_channel( uint offchannel) {
  //   auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

  //   if (!chan_info.valid) {
  //     return -1;
  //   }

  //   // Brute force approack
  //   if(chan_info.APAName=="APA_P02SU") return 1;
  //   if(chan_info.APAName=="APA_P01SU") return 2;
  //   if(chan_info.APAName=="APA_P02NL") return 3;
  //   if(chan_info.APAName=="APA_P01NL") return 4;

  //   // There is only one element
  //   return 0;
  // }

  // /**
  //  * @brief Get the tpc element name from offline channel object
  //  * 
  //  * @param offchannel 
  //  * @return std::string 
  //  */
  // std::string 
  // get_tpc_element_name_from_offline_channel( uint offchannel) {
  //   auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

  //   if (!chan_info.valid) {
  //     return "";
  //   }

  //   return chan_info.APAName;
  // }


  // std::optional<TPCChannelInfo> 
  // get_tpc_channel_info_from_offline_channel(uint offchannel) {
  //   auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

  //   if ( !ci.valid) {
  //     return std::nullopt;
  //   }
  //   return TPCChannelInfo{kDetID, ci.crate, ci.wib-1, ci.link, ci.wibframechan, 0};
  // }



  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::HDColdboxTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
