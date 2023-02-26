#include "detchannelmaps/TPCChannelMap.hpp"
#include "PdspChannelMapService.hpp"

namespace dunedaq {
namespace detchannelmaps {

class ProtoDUNESP1ChannelMap :  public TPCChannelMap
{
public:



  explicit ProtoDUNESP1ChannelMap() {

    // Find the map configuration file
    const char* detchannelmaps_share_cstr = getenv("DETCHANNELMAPS_SHARE");
    if (!detchannelmaps_share_cstr) {
      throw std::runtime_error("Environment variable DETCHANNELMAPS_SHARE is not set");
    }
    // Create search paths
    std::string detchannelmaps_share(detchannelmaps_share_cstr);
    std::string channel_map_rce = detchannelmaps_share + "/config/protodunesp1/protoDUNETPCChannelMap_RCE_v4.txt";
    std::string channel_map_felix = detchannelmaps_share + "/config/protodunesp1/protoDUNETPCChannelMap_FELIX_v4.txt";
    // Instantiate paths
    m_channel_map.reset(new PdspChannelMapService(channel_map_rce, channel_map_felix));

    // Create reverse maps
    // Loop over crates (0-5)
    for (uint i_crate(0); i_crate < m_n_crates; ++i_crate) {
      // Loop over (0-4)
      for (uint i_slots(0); i_slots < m_n_slots; ++i_slots) {
        // Loop over fibres (1,2)
        for (uint i_fiber(1); i_fiber <= m_n_fibers; ++i_fiber) {
          // Loop over channels (0-255)
          for (uint i_chan(0); i_chan < m_n_chans; ++i_chan) {

            uint off_chan = get_offline_channel_from_crate_slot_fiber_chan(i_crate, i_slots, i_fiber, i_chan);
            
            // std::cout << off_chan << "   " << i_crate << "   " <<  i_slots <<  "   " << i_fiber << std::endl;
            m_offchan_to_coords_map[off_chan] = TPCCoords{i_crate, i_slots, i_fiber, i_chan};
          }
        }
      }
    }
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
        crate+1, slot, wc, fembchannel, PdspChannelMapService::kFELIX
    );
  }

  uint get_plane_from_offline_channel(uint offchannel) final {
    return m_channel_map->PlaneFromOfflineChannel(offchannel);
  };

  std::optional<TPCCoords> 
  get_crate_slot_fiber_chan_from_offline_channel(uint offchannel) {

    auto it = m_offchan_to_coords_map.find(offchannel);

    if ( it == m_offchan_to_coords_map.end() )
      return std::nullopt;

    return it->second;
  }

private:
  
  const size_t m_tot_chans = 15360;
  const size_t m_n_crates = 6;
  const size_t m_n_slots = 5;
  const size_t m_n_fibers = 2;
  const size_t m_n_chans = 256;

  std::unique_ptr<PdspChannelMapService> m_channel_map;
  std::map<uint, TPCCoords> m_offchan_to_coords_map;

  
};

DEFINE_DUNE_DET_CHANNEL_MAP(dunedaq::detchannelmaps::ProtoDUNESP1ChannelMap)


} // namespace detchannelmaps
} // namespace dunedaq