#ifndef DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_
#define DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_

#include "cetlib/BasicPluginFactory.h"
#include "cetlib/compiler_macros.h"
#include "ers/Issue.hpp"
#include <optional>


#ifndef EXTERN_C_FUNC_DECLARE_START
// NOLINTNEXTLINE(build/define_used)
#define EXTERN_C_FUNC_DECLARE_START                                                                                    \
  extern "C"                                                                                                           \
  {
#endif
/**
 * @brief Declare the function that will be called by the plugin loader
 * @param klass Class to be defined as a DUNE DAQ Module
 */
// NOLINTNEXTLINE(build/define_used)
#define DEFINE_DUNE_DET_CHANNEL_MAP(klass)                                                                                  \
  EXTERN_C_FUNC_DECLARE_START                                                                                          \
  std::shared_ptr<dunedaq::detchannelmaps::TPCChannelMap> make()                                                                  \
  {                                                                                                                    \
    return std::shared_ptr<dunedaq::detchannelmaps::TPCChannelMap>(new klass());                                                  \
  }                                                                                                                    \
  }


namespace dunedaq {

// Disable coverage collection LCOV_EXCL_START
/**
 * @brief A ERS Issue for TPCChannelMap creation failure
 */
ERS_DECLARE_ISSUE(detchannelmaps,                  ///< Namespace
                  ChannelMapCreationFailed, ///< Type of the Issue
                  "Failed to create TPCChannelMap of type " << plugin_name,          ///< Log Message from the issue
                  ((std::string)plugin_name) ///< Message parameters
)
ERS_DECLARE_ISSUE(detchannelmaps,                  ///< Namespace
                  InvalidStream, ///< Type of the Issue
                  "Invalid stream number " << stream,          ///< Log Message from the issue
                  ((uint)stream) ///< Message parameters
)

namespace detchannelmaps {

class TPCChannelMap
{
public:

  struct TPCCoords
  {
    uint crate;
    uint slot;
    uint fiber;
    uint channel;
  };

  /**
   * @brief      Gets the offline channel from detector elements.
   *
   * @param[in]  crate        The crate
   * @param[in]  slot         The slot
   * @param[in]  fiber        The fiber
   * @param[in]  fembchannel  The channel
   *
   * @return     The offline channel from detector elements.
   */
  virtual uint get_offline_channel_from_crate_slot_fiber_chan(uint crate, uint slot, uint fiber, uint channel) = 0;
  virtual uint get_offline_channel_from_crate_slot_stream_chan(uint crate, uint slot, uint stream, uint channel) {

    //if stream number looks wrong (not 0,1,2,3 or 64,65,66,67)
    if( (stream & 0xbc) ) throw InvalidStream(ERS_HERE, stream);
    
    constexpr uint n_chan_per_stream = 64;

    uint link = (stream >> 6) & 1;
    uint locstream = (stream & 0x3);
    uint ch = n_chan_per_stream*locstream+channel;
    return this->get_offline_channel_from_crate_slot_fiber_chan(crate, slot, link, ch);

  };
  virtual uint get_plane_from_offline_channel(uint offchannel) = 0;
  virtual std::optional<TPCCoords> get_crate_slot_fiber_chan_from_offline_channel(uint offchannel) = 0;
  /**
   * @brief TPCChannelMap destructor
   */
  virtual ~TPCChannelMap() noexcept = default;
    
protected:
   /*
   * @brief TPCChannelMap Constructor
   * @param name Name of the TPCChannelMap
   */
  explicit TPCChannelMap(){}
};

/**
 * @brief Load a TPCChannelMap plugin and return a shared_ptr to the contained
 * TPCChannelMap class
 * @param plugin_name Name of the plugin, e.g. DebugLoggingChannelMap
 * @param instance_name Name of the returned TPCChannelMap instance, e.g.
 * DebugLogger1
 * @return shared_ptr to created TPCChannelMap instance
 */
inline std::shared_ptr<TPCChannelMap>
make_map(std::string const& plugin_name)
{
  static cet::BasicPluginFactory bpf("duneChannelMap", "make");

  std::shared_ptr<TPCChannelMap> mod_ptr;
  try {
    mod_ptr = bpf.makePlugin<std::shared_ptr<TPCChannelMap>>(plugin_name);
  } catch (const cet::exception& cexpt) {
    throw ChannelMapCreationFailed(ERS_HERE, plugin_name, cexpt);
  }
  return mod_ptr;
}

} // namespace detchannelmaps

} // namespace dunedaq

#endif // DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_
