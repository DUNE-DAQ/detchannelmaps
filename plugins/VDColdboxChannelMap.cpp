#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class VDColdboxChannelMap :  public PD2HDChannelMapSPPluginBase
{
public:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 10;
  
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit VDColdboxChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "vdcoldbox/vdcbce_chanmap_v4.txt" ) {

    m_elem_name_id_converter = [](const std::string& apa_name) -> uint {
      // Brute force approack
      return 0;
    };

    TLOG_DEBUG(10) << "VDColdboxChannelMap Created";
  }
  
};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::VDColdboxChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
