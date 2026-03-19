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
    PD2HDChannelMapSPPluginBase( kDetID, "hdcoldbox/hdcb_chanmap_v1.txt" ) {

    m_elem_name_id_converter = [](const std::string& apa_name) -> uint {
      // Brute force approack
      if(apa_name=="APA0") {
        return 0;
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
  
};

DEFINE_DUNE_DET_TPCCHANNEL_MAP(dunedaq::detchannelmaps::HDColdboxTPCChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
