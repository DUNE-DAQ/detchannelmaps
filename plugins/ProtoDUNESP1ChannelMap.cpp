#include "detchannelmaps/TPCChannelMap.hpp"
#include "PdspChannelMapService.hpp"

namespace dunedaq {
namespace detchannelmaps {

class ProtoDUNESP1ChannelMap :  public TPCChannelMap
{
public:
  explicit ProtoDUNESP1ChannelMap() {
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_rce = detchannelmaps_share + "/config/protodunesp1/protoDUNETPCChannelMap_RCE_v4.txt";
    std::string channel_map_felix = detchannelmaps_share + "/config/protodunesp1/protoDUNETPCChannelMap_FELIX_v4.txt";
    m_channel_map.reset(new PdspChannelMapService(channel_map_rce, channel_map_felix));
  }

  ProtoDUNESP1ChannelMap(const ProtoDUNESP1ChannelMap&) = delete;            ///< ProtoDUNESP1ChannelMap is not copy-constructible
  ProtoDUNESP1ChannelMap& operator=(const ProtoDUNESP1ChannelMap&) = delete; ///< ProtoDUNESP1ChannelMap is not copy-assignable
  ProtoDUNESP1ChannelMap(ProtoDUNESP1ChannelMap&&) = delete;                 ///< ProtoDUNESP1ChannelMap is not move-constructible
  ProtoDUNESP1ChannelMap& operator=(ProtoDUNESP1ChannelMap&&) = delete;      ///< ProtoDUNESP1ChannelMap is not move-assignable

  uint get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint fiber, uint cechan) final {
      int fembchannel = cechan;
      int wc = fiber*2 - 1;
      if (fembchannel>127)
        {
          fembchannel -= 128;
          wc++;
        }

    return m_channel_map->GetOfflineNumberFromDetectorElements(
        crate, slot+1, wc, fembchannel, PdspChannelMapService::kFELIX
    );
  }

  uint get_plane_from_offline_channel(uint offchannel) final {
    return m_channel_map->PlaneFromOfflineChannel(offchannel);
  };

private:

  std::unique_ptr<PdspChannelMapService> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::ProtoDUNESP1ChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq