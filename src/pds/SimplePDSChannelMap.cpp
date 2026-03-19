#include "detchannelmaps/PDSChannelMap.hpp"

#include "logging/Logging.hpp" // NOLINT

#include <format>

namespace dunedaq {
namespace detchannelmaps {

class SimplePDSChannelMap :  public PDSChannelMap
{
public:

  explicit SimplePDSChannelMap() {}

  SimplePDSChannelMap(const SimplePDSChannelMap&) = delete;            ///< SimplePDSChannelMap is not copy-constructible
  SimplePDSChannelMap& operator=(const SimplePDSChannelMap&) = delete; ///< SimplePDSChannelMap is not copy-assignable
  SimplePDSChannelMap(SimplePDSChannelMap&&) = delete;                 ///< SimplePDSChannelMap is not move-constructible
  SimplePDSChannelMap& operator=(SimplePDSChannelMap&&) = delete;      ///< SimplePDSChannelMap is not move-assignable

  uint get_offline_channel_from_det_crate_slot_stream_chan(uint , //det
                                                           uint , //crate
                                                           uint slot,
                                                           uint , //stream
                                                           uint channel) final {
    return slot*100+channel;
  }

  std::optional<PDSChannelInfo>
  get_det_crate_slot_fiber_chan_from_offline_channel(uint offchannel) final {

    PDSChannelInfo pds_ch_info;
    pds_ch_info.channel = offchannel%100;
    pds_ch_info.slot = offchannel/100;
    pds_ch_info.element = offchannel/100;

    return pds_ch_info;
  }


  uint get_element_from_offline_channel(uint offchannel) final
  {
    return offchannel/100;
  }

  std::string get_element_name_from_offline_channel(uint offchannel) final
  {
    return std::format("PDSModule{}",offchannel/100);
  }

};

DEFINE_DUNE_DET_PDSCHANNEL_MAP(dunedaq::detchannelmaps::SimplePDSChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq
