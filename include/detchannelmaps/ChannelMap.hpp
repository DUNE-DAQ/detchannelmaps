#ifndef DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_CHANNELMAP_HPP_
#define DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_CHANNELMAP_HPP_

#include "cetlib/BasicPluginFactory.h"
#include "cetlib/compiler_macros.h"
#include "ers/Issue.hpp"


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
  std::shared_ptr<dunedaq::detchannelmaps::ChannelMap> make()                                                                  \
  {                                                                                                                    \
    return std::shared_ptr<dunedaq::detchannelmaps::ChannelMap>(new klass());                                                  \
  }                                                                                                                    \
  }


namespace dunedaq {

// Disable coverage collection LCOV_EXCL_START
/**
 * @brief A ERS Issue for ChannelMap creation failure
 */
ERS_DECLARE_ISSUE(detchannelmaps,                  ///< Namespace
                  ChannelMapCreationFailed, ///< Type of the Issue
                  "Failed to create ChannelMap of type " << plugin_name,          ///< Log Message from the issue
                  ((std::string)plugin_name) ///< Message parameters
)

namespace detchannelmaps {

class ChannelMap
{
public:

  /**
   * @brief      Gets the offline channel from detector elements.
   *
   * @param[in]  crate        The crate
   * @param[in]  slot         The slot
   * @param[in]  fiber        The fiber
   * @param[in]  fembchannel  The fembchannel
   *
   * @return     The offline channel from detector elements.
   */
  virtual uint get_offline_channel_from_detector_elements(uint crate, uint slot, uint fiber, uint fembchannel) = 0;

  /**
   * @brief ChannelMap destructor
   */
  virtual ~ChannelMap() noexcept = default;
    
protected:
   /*
   * @brief ChannelMap Constructor
   * @param name Name of the ChannelMap
   */
  explicit ChannelMap(){}
};

/**
 * @brief Load a ChannelMap plugin and return a shared_ptr to the contained
 * ChannelMap class
 * @param plugin_name Name of the plugin, e.g. DebugLoggingChannelMap
 * @param instance_name Name of the returned ChannelMap instance, e.g.
 * DebugLogger1
 * @return shared_ptr to created ChannelMap instance
 */
inline std::shared_ptr<ChannelMap>
make_map(std::string const& plugin_name)
{
  static cet::BasicPluginFactory bpf("duneChannelMap", "make");

  std::shared_ptr<ChannelMap> mod_ptr;
  try {
    mod_ptr = bpf.makePlugin<std::shared_ptr<ChannelMap>>(plugin_name);
  } catch (const cet::exception& cexpt) {
    throw ChannelMapCreationFailed(ERS_HERE, plugin_name, cexpt);
  }
  return mod_ptr;
}

} // namespace detchannelmaps

} // namespace dunedaq

#endif // DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_CHANNELMAP_HPP_
