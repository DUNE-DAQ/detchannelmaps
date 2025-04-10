#ifndef DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_
#define DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_

#include "cetlib/BasicPluginFactory.h"
#include "cetlib/compiler_macros.h"
#include "ers/Issue.hpp"
#include "logging/Logging.hpp" // NOTE: if ISSUES ARE DECLARED BEFORE include logging/Logging.hpp, TLOG_DEBUG<<issue wont work.
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
#define DEFINE_DUNE_DET_PDSCHANNEL_MAP(klass)                                                                                  \
  EXTERN_C_FUNC_DECLARE_START                                                                                          \
  std::shared_ptr<dunedaq::detchannelmaps::PDSChannelMap> make()                                                                  \
  {                                                                                                                    \
    return std::shared_ptr<dunedaq::detchannelmaps::PDSChannelMap>(new klass());                                                  \
  }                                                                                                                    \
  }


namespace dunedaq {

// Disable coverage collection LCOV_EXCL_START
/**
 * @brief A ERS Issue for PDSChannelMap creation failure
 */
ERS_DECLARE_ISSUE(detchannelmaps,              ///< Namespace
                  PDSChannelMapCreationFailed, ///< Type of the Issue
                  "Failed to create PDSChannelMap of type " << plugin_name,          ///< Log Message from the issue
                  ((std::string)plugin_name) ///< Message parameters
)
ERS_DECLARE_ISSUE(detchannelmaps,   ///< Namespace
                  PDSInvalidStream, ///< Type of the Issue
                  "Invalid stream number " << stream,          ///< Log Message from the issue
                  ((uint)stream) ///< Message parameters
)

namespace detchannelmaps {

class PDSChannelMap
{
public:

  struct PDSCoords
  {
    uint det;
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
  virtual uint get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) = 0;

  virtual uint get_element_from_offline_channel(uint ) = 0;
  virtual std::optional<PDSCoords> get_det_crate_slot_fiber_chan_from_offline_channel(uint offchannel) = 0;
  /**
   * @brief PDSChannelMap destructor
   */
  virtual ~PDSChannelMap() noexcept = default;
    
protected:
   /*
   * @brief PDSChannelMap Constructor
   * @param name Name of the PDSChannelMap
   */
  explicit PDSChannelMap(){}
};

/**
 * @brief Load a PDSChannelMap plugin and return a shared_ptr to the contained
 * PDSChannelMap class
 * @param plugin_name Name of the plugin, e.g. DebugLoggingChannelMap
 * @param instance_name Name of the returned PDSChannelMap instance, e.g.
 * DebugLogger1
 * @return shared_ptr to created PDSChannelMap instance
 */
inline std::shared_ptr<PDSChannelMap>
make_pds_map(std::string const& plugin_name)
{
  static cet::BasicPluginFactory bpf("dunePDSChannelMap", "make");

  std::shared_ptr<PDSChannelMap> mod_ptr;
  try {
    mod_ptr = bpf.makePlugin<std::shared_ptr<PDSChannelMap>>(plugin_name);
  } catch (const cet::exception& cexpt) {
    throw PDSChannelMapCreationFailed(ERS_HERE, plugin_name, cexpt);
  }
  return mod_ptr;
}

} // namespace detchannelmaps

} // namespace dunedaq

#endif // DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_
