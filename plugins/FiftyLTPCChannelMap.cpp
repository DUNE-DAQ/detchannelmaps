#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class FiftyLTPCChannelMap :  public PD2HDChannelMapSPPluginBase
{
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 10;
  
  public:
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit FiftyLTPCChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "50L/50LChannelMap_v1.txt" ) {

    m_elem_name_id_converter = [](const std::string& /* apa_name */ ) -> uint {
      return 0;
    };

    TLOG_DEBUG(10) << "FiftyLTPCChannelMap Created";
  }
  
};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::FiftyLTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
