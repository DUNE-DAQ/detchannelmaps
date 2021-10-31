#include "detchannelmaps/TPCChannelMap.hpp"
#include "VDColdboxChannelMapService.hpp"

namespace dunedaq {
namespace detchannelmaps {

class VDColdboxChannelMap :  public TPCChannelMap
{
public:
  explicit VDColdboxChannelMap() {
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_file = detchannelmaps_share + "/config/vdcoldbox/vdcbce_chanmap_v1_dcchan3456.txt";
    m_channel_map.reset(new VDColdboxChannelMapService(channel_map_file));
  }

  VDColdboxChannelMap(const VDColdboxChannelMap&) = delete;            ///< VDColdboxChannelMap is not copy-constructible
  VDColdboxChannelMap& operator=(const VDColdboxChannelMap&) = delete; ///< VDColdboxChannelMap is not copy-assignable
  VDColdboxChannelMap(VDColdboxChannelMap&&) = delete;                 ///< VDColdboxChannelMap is not move-constructible
  VDColdboxChannelMap& operator=(VDColdboxChannelMap&&) = delete;      ///< VDColdboxChannelMap is not move-assignable

  uint get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint fiber, uint fembchannel) final {
    if (crate != 1)
      return 0;

    return m_channel_map->getOfflChanFromSlotFiberChan(
        slot, fiber, fembchannel
    );
  }

  uint get_plane_from_offline_channel(uint offchannel) final {
    auto chan_info = m_channel_map->getChanInfoFromOfflChan(offchannel);

    switch(chan_info.stripid[0]) {
      case 'U':
        return 0;
      case 'Y':
        return 1;
      case 'Z':
        return 2;
      default:
        // code block
        throw std::logic_error(std::string("Unknown plane identifier")+chan_info.stripid[0]+" in stripid "+chan_info.stripid);
      }
  };

private:

  std::unique_ptr<VDColdboxChannelMapService> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::VDColdboxChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq