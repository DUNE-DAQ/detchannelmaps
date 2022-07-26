///////////////////////////////////////////////////////////////////////////////////////////////////
// Class:       HardwareMapService
// Module type: service
// File:        HardwareMapService.h
// Author:      Tom Junk, October 2021
//
// Implementation of hardware-offline channel mapping reading from a file.  
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DETCHANNELSMAP_HARDWAREMAPSERVICE_H_
#define DETCHANNELSMAP_HARDWAREMAPSERVICE_H_

#include <iostream>
#include <vector>
#include <map>

namespace dunedaq {
namespace detchannelmaps {

class HardwareMapService {

 public:

  HardwareMapService(std::string mapfile);

  struct HWInfo {
    uint32_t dro_source_id = 0;
    uint16_t det_link = 0;
    uint16_t det_slot = 0;
    uint16_t det_crate = 0;
    uint16_t det_id = 0;
    std::string dro_host = "";
    uint16_t dro_card = 0;
    uint16_t dro_slr = 0;
    uint16_t dro_link = 0;
    bool is_valid = false;
    uint64_t geo_id = 0;
  };

  struct DROInfo {
      std::string host = "";
      uint16_t card = 0;
      std::vector<HWInfo> links;
  };

  // Access methods

  // The function below gets hw info from DAQ source id.  

  std::vector<HWInfo> get_hw_info_from_source_id(const uint32_t dro_source_id);

  // The function below gets hw info from DAQ source id.  Sets valid to be false if 
  // there is no corresponding cold electronics channel

  HWInfo get_hw_info_from_geo_id(const uint64_t geo_id);

  uint64_t get_geo_id(const uint16_t det_link, const uint16_t det_slot, const uint16_t det_crate, const uint16_t det_id);

  std::vector<DROInfo> get_all_dro_info();
  DROInfo get_dro_info(const std::string host_name, const uint16_t dro_card);


 private:

  //  map so we can look up info by geo id number

  std::map<uint64_t,HWInfo> m_geo_id_to_info_map;

  // map so we can look up all geo id's by source id 

  std::map<uint32_t,std::vector<HWInfo>> m_source_id_to_geo_ids_map;

  // DROs map
   std::map<std::pair<std::string, uint16_t>, DROInfo> m_dro_info_map;
};

} // namespace detchannelmaps
} // namespace dunedaq

#endif /* DETCHANNELSMAP_HARDWAREMAPSERVICE_H_ */
