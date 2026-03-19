#pragma once

#include "PD2HDChannelMapSP.h"
#include "logging/Logging.hpp" // NOLINT
#include "detchannelmaps/TPCChannelMap.hpp"

namespace dunedaq {
namespace detchannelmaps {

class PD2HDChannelMapSPPluginBase : public TPCChannelMap {
private:
  const uint m_det_id;
  std::unique_ptr<dune::PD2HDChannelMapSP> m_channel_map;
protected:
  std::function<uint(std::string)> m_elem_name_id_converter;
public:

  /**
   * @brief Construct a new PD2HDChannelMapSPPluginBase object
   * 
   * @param det_id 
   * @param channel_map_path 
   */
  explicit PD2HDChannelMapSPPluginBase(uint det_id, const std::string& channel_map_path ) :
    m_det_id(det_id) {

    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/" + channel_map_path;
    m_channel_map.reset(new dune::PD2HDChannelMapSP());
    m_channel_map->ReadMapFromFile(channel_map_file);

  }

  PD2HDChannelMapSPPluginBase(const PD2HDChannelMapSPPluginBase&) = delete;            ///< PD2HDChannelMapSPPluginBase is not copy-constructible
  PD2HDChannelMapSPPluginBase& operator=(const PD2HDChannelMapSPPluginBase&) = delete; ///< PD2HDChannelMapSPPluginBase is not copy-assignable
  PD2HDChannelMapSPPluginBase(PD2HDChannelMapSPPluginBase&&) = delete;                 ///< PD2HDChannelMapSPPluginBase is not move-constructible
  PD2HDChannelMapSPPluginBase& operator=(PD2HDChannelMapSPPluginBase&&) = delete;      ///< PD2HDChannelMapSPPluginBase is not move-assignable


  /**
   * @brief Get the offline channel from detector crate slot stream chan object
   * 
   * @param det 
   * @param crate 
   * @param slot 
   * @param stream 
   * @param channel 
   * 
   * @return offline channel identifier
   */
  uint 
  get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) final {

    // Must be a BDE channel 
    if( det != m_det_id) 
      return -1;

    // if stream number looks wrong (not 0,1,2,3 or 64,65,66,67)
    if( (stream & 0xbc) ) 
      return -1;
    
    constexpr uint n_chan_per_stream = 64;

    uint link = (stream >> 6) & 1;
    uint stream_in_link = (stream & 0x3);
    uint wibframechan = n_chan_per_stream*stream_in_link+channel;

    auto chan_info = m_channel_map->GetChanInfoFromWIBElements(
        crate, slot, link, wibframechan
    );

    if (!chan_info.valid) {
      return -1;
    }

    return chan_info.offlchan;    
  }


  /**
   * @brief Get the plane from offline channel object
   * 
   * @param offchannel 
   * @return plane id (0, 1 or 2) 
   */
  uint 
  get_plane_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return -1;
    }

    return chan_info.plane;
  };


  /**
   * @brief Get the element id from offline channel object
   * 
   * @param offchannel 
   * @return uint 
   */
  uint
  get_element_id_from_offline_channel( uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return -1;
    }

    return m_elem_name_id_converter(chan_info.APAName);

    // There is only one element
    return 0;
  }

  /**
   * @brief Get the tpc element name from offline channel object
   * 
   * @param offchannel 
   * @return std::string 
   */
  std::string 
  get_element_name_from_offline_channel( uint offchannel) final {
    auto chan_info = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if (!chan_info.valid) {
      return "";
    }

    return chan_info.APAName;
  }


  std::optional<TPCChannelMap::TPCChannelInfo> 
  get_channel_info_from_offline_channel(uint offchannel) final {
    auto ci = m_channel_map->GetChanInfoFromOfflChan(offchannel);

    if ( !ci.valid) {
      return std::nullopt;
    }
    constexpr uint n_chan_per_stream = 64;
    uint16_t slot_id = ci.wib-1;
    uint16_t stream_id = ci.link*n_chan_per_stream+ci.wibframechan/n_chan_per_stream;
    uint16_t chan_id = ci.wibframechan%n_chan_per_stream;

    return TPCChannelMap::TPCChannelInfo{m_det_id, ci.crate, slot_id, stream_id, chan_id, m_elem_name_id_converter(ci.APAName)};
  }

};
    
} // namespace detchannelmaps
} // namespace dunedaq
