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

HardwareMapService::HardwareMapService(const std::string filename) {

  std::ifstream inFile(filename, std::ios::in);
  if (inFile.bad() || inFile.fail() || !inFile.is_open()) {
    throw std::runtime_error(std::string("HardwareMapService: Invalid map file ") + std::string(filename));
  }

  std::string line;
  while (std::getline(inFile,line)) {
    HWInfo hw_info;
    if (line.size() == 0 || line[0] == '#') continue;
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
    hw_info.geo_id = get_geo_id(hw_info.det_link, hw_info.det_slot, hw_info.det_crate, hw_info.det_id);
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

    // DRO is defined by a host-card pair!
    std::map<std::pair<std::string, uint16_t>, DROInfo> map;

    for (auto& gid : m_geo_id_to_info_map) {
        auto hwi = gid.second;
        auto key = std::make_pair(hwi.dro_host, hwi.dro_card);

        if (m_dro_info_map.count(key)) {
            m_dro_info_map[key].links.push_back(hwi);
        }
        else {
            m_dro_info_map[key] = DROInfo{ hwi.dro_host, hwi.dro_card, {hwi} };
        }
    }

}

std::vector<HardwareMapService::HWInfo> HardwareMapService::get_hw_info_from_source_id(const uint32_t dro_source_id) {
     auto sid = m_source_id_to_geo_ids_map.find(dro_source_id);
     if(sid != m_source_id_to_geo_ids_map.end()) {
	     return sid->second;
     }
     return std::vector<HWInfo>();
}

HardwareMapService::HWInfo HardwareMapService::get_hw_info_from_geo_id(const uint64_t geo_id) {
     auto gid = m_geo_id_to_info_map.find(geo_id);
     if(gid != m_geo_id_to_info_map.end()) {
	return gid->second;
     }
     HWInfo hw_info;
     hw_info.is_valid = false;
     return hw_info;
}

uint64_t HardwareMapService::get_geo_id(const uint16_t det_link, const uint16_t det_slot, const uint16_t det_crate, const uint16_t det_id) {
  uint64_t geoid = static_cast<uint64_t>(det_link) << 48 | static_cast<uint64_t>(det_slot) << 32 | static_cast<uint64_t>(det_crate) << 16 | det_id;
  return geoid;
}

HardwareMapService::GeoInfo HardwareMapService::parse_geo_id(const uint64_t geo_id) {
  GeoInfo geo_info;
  geo_info.det_link = 0xffff & (geo_id >> 48);
  geo_info.det_slot = 0xffff & (geo_id >> 32);
  geo_info.det_crate = 0xffff & (geo_id >> 16);
  geo_info.det_id = 0xffff & geo_id;
  return geo_info;
}

std::vector<HardwareMapService::DROInfo> HardwareMapService::get_all_dro_info() {

    std::vector<DROInfo> output;

    for (auto& entry : m_dro_info_map) {
        output.push_back(entry.second);
    }
    return output;
}

HardwareMapService::DROInfo HardwareMapService::get_dro_info(const std::string host_name, const uint16_t dro_card) {
    auto key = std::make_pair(host_name, dro_card);
     
    auto dro = m_dro_info_map.find(key);
    if(dro != m_dro_info_map.end())
	  return dro->second;

    std::ostringstream s;
    s<< "HardwareMapService: Invalid DRO host/card pair " << host_name << "/" << dro_card;
    throw std::runtime_error(s.str());  
}

} // namespace detchannelsmap
} // namespace dunedaq

