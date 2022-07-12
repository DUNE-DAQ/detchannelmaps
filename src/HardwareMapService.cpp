///////////////////////////////////////////////////////////////////////////////////////////////////
// Class:       HardwareMapService
// Module type: service
// File:        HardwareMapService.cpp
// Author:      G. Lehmann Miotto, July 2022
//
// Implementation of hardware  mapping reading from a file.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "detchannelmaps/HardwareMapService.hpp"

#include <fstream>
#include <sstream>

namespace dunedaq {
namespace detchannelmaps {

HardwareMapService::HardwareMapService(std::string filename) {

  std::ifstream inFile(filename, std::ios::in);
  if (inFile.bad() || inFile.fail() || !inFile.is_open()) {
    throw std::runtime_error(std::string("HardwareMapService: Invalid map file ") + std::string(filename));
  }

  std::string line;
  while (std::getline(inFile,line)) {
    HWInfo hw_info;
    std::stringstream linestream(line);
    linestream >>
      hw_info.dro_source_id >>
      hw_info.det_link >>
      hw_info.det_slot >>
      hw_info.det_crate >>
      hw_info.det_id >>
      hw_info.dro_host >>
      hw_info.dro_card >>
      hw_info.dro_slr >>
      hw_info.dro_link;
    hw_info.is_valid = true;
    hw_info.geo_id = get_geoid(hw_info.det_link, hw_info.det_slot, hw_info.det_crate, hw_info.det_id);
    m_geo_id_to_info_map[hw_info.geo_id] = hw_info;
    auto sid = m_source_id_to_geo_ids_map.find(hw_info.dro_source_id);
    if(sid != m_source_id_to_geo_ids_map.end()) {
        sid->second.push_back(hw_info);
    }
    else {
        std::vector<HWInfo> vec;
	vec.push_back(hw_info);
	    m_source_id_to_geo_ids_map[hw_info.dro_source_id] = vec;
    }
  }
  inFile.close();

}

std::vector<HardwareMapService::HWInfo> HardwareMapService::get_hw_info_from_source_id(uint32_t dro_source_id) {
     auto sid = m_source_id_to_geo_ids_map.find(dro_source_id);
     if(sid != m_source_id_to_geo_ids_map.end()) {
	     return sid->second;
     }
     return std::vector<HWInfo>();
}

HardwareMapService::HWInfo HardwareMapService::get_hw_info_from_geo_id(uint64_t geo_id) {
     auto gid = m_geo_id_to_info_map.find(geo_id);
     if(gid != m_geo_id_to_info_map.end()) {
	return gid->second;
     }
     HWInfo hw_info;
     hw_info.is_valid = false;
     return hw_info;
}

uint64_t HardwareMapService::get_geoid(uint16_t det_link, uint16_t det_slot, uint16_t det_crate, uint16_t det_id) {
    uint64_t geoid= det_link << 48 | det_slot << 32 | det_crate << 16 | det_id;
    std::cout << "geoid " << std::hex << geoid << std::dec << std::endl;
    return geoid;

}


} // namespace detchannelsmap
} // namespace dunedaq

