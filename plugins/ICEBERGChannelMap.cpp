#include "detchannelmaps/TPCChannelMap.hpp"
#include "PD2HDChannelMapSPPluginBase.hpp"
#include "PD2HDChannelMapSP.h"

#include "logging/Logging.hpp" // NOLINT

namespace dunedaq {
namespace detchannelmaps {

class ICEBERGChannelMap :  public PD2HDChannelMapSPPluginBase
{
public:
  // TODO: Use detdataformats::kHD_TPC instead
  const static uint kDetID = 3;
  
  public:
  /**
   * @brief Construct a new HDColdboxTPCChannelMap object
   * 
   */
  explicit ICEBERGChannelMap() :
    PD2HDChannelMapSPPluginBase( kDetID, "iceberg/iceberg_wibeth_chanmap_v1.txt" ) {

    m_elem_name_id_converter = [](const std::string& /* apa_name */ ) -> uint {
      return 0;
    };

    TLOG_DEBUG(10) << "ICEBERGChannelMap Created";
  }

};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::ICEBERGChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
