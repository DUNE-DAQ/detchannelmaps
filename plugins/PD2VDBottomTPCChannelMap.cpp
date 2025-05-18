#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class PD2VDBottomTPCChannelMap :  public PD2HDChannelMapSPPluginBase {
private:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 10;
public:

  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit PD2VDBottomTPCChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "pd2vd/PD2VDBottomTPCChannelMap_v1.txt" ) {

    m_elem_name_id_converter = [](const std::string& apa_name) -> uint {
      // Brute force approack
      if(apa_name=="4") {
        return 4;
      } else if(apa_name=="5") {
        return 5;
      } else {
        return -1;
      }
    };

    TLOG_DEBUG(10) << "PD2VDBottomTPCChannelMap Created";
  }
  
};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::PD2VDBottomTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
