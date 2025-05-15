#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2HDChannelMap :  public PD2HDChannelMapSPPluginBase
{
public:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 3;
  
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit PD2HDChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "pd2hd/PD2HDChannelMap_v6.txt" ) {

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

    TLOG_DEBUG(10) << "PD2HDChannelMap Created";
  }
//   explicit PD2HDChannelMap() {
  
//     const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
//     if (!detchannelmaps_share_cstr) {
//       throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
//     }
//     std::string detchannelmaps_share(detchannelmaps_share_cstr);
//     std::string channel_map_file = detchannelmaps_share + "/config/pd2hd/PD2HDChannelMap_v6.txt";
//     m_channel_map.reset(new dune::PD2HDChannelMapSP());
//     m_channel_map->ReadMapFromFile(channel_map_file);
//     TLOG_DEBUG(10) << "PD2HDChannelMap Created";
//   }

//   PD2HDChannelMap(const PD2HDChannelMap&) = delete;            ///< PD2HDChannelMap is not copy-constructible
//   PD2HDChannelMap& operator=(const PD2HDChannelMap&) = delete; ///< PD2HDChannelMap is not copy-assignable
//   PD2HDChannelMap(PD2HDChannelMap&&) = delete;                 ///< PD2HDChannelMap is not move-constructible
//   PD2HDChannelMap& operator=(PD2HDChannelMap&&) = delete;      ///< PD2HDChannelMap is not move-assignable


//   uint 
//   get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint link, uint wibframechan) final {

//     auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
//         crate, slot, link, wibframechan
//     );

//     if (!chan_info.valid) {
//       return -1;
//     }

//     return chan_info.offlchan;

//   }


//   uint 
//   get_plane_from_offline_channel(uint offchannel) final {
//     auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

//     if (!chan_info.valid) {
//       return 9999;
//     }

//     return chan_info.plane;
//   };

//   std::string 
//   get_tpc_element_from_offline_channel(uint offchannel) final {
//     auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

//     if (!chan_info.valid) {
//       return "";
//     }

//     return chan_info.APAName;
//   };

//   std::optional<TPCCoords> 
//   get_crate_slot_fiber_chan_from_offline_channel(uint offchannel) {
//     auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

//     if ( !ci.valid) {
//       return std::nullopt;
//     }
//     return TPCCoords{ci.crate, ci.wib-1, ci.link, ci.wibframechan};
//   }



// private:

//   std::unique_ptr<dune::PD2HDChannelMapSP> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::PD2HDChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
