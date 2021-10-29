#include "detchannelmaps/ChannelMap.hpp"
#include "PdspChannelMapService.hpp"

namespace dunedaq {
namespace detchannelmaps {

class ProtoDUNESP1ChannelMap :  public ChannelMap
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

  uint get_offline_channel_from_detector_elements(uint crate, uint slot, uint fiber, uint fembchannel) final {
    return m_channel_map->GetOfflineNumberFromDetectorElements(
        crate, slot, fiber, fembchannel, PdspChannelMapService::kFELIX
    );
  }

private:

  std::unique_ptr<PdspChannelMapService> m_channel_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::ProtoDUNESP1ChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq