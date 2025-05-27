#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2HDTPCChannelMap :  public PD2HDChannelMapSPPluginBase
{
public:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 3;
  
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit PD2HDTPCChannelMap() :
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

    TLOG_DEBUG(10) << "PD2HDTPCChannelMap Created";
  }

};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::PD2HDTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
