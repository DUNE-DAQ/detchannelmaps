#ifndef DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_
#define DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_

#include "ers/Issue.hpp"
#include "logging/Logging.hpp" // NOTE: if ISSUES ARE DECLARED BEFORE include logging/Logging.hpp, TLOG_DEBUG<<issue wont work.
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>


// Helper macros for unique struct names that survive __LINE__ expansion
// NOLINTNEXTLINE(build/define_used)
#define DUNE_TPCMAP_DETAIL_CAT(a, b) a##b
// NOLINTNEXTLINE(build/define_used)
#define DUNE_TPCMAP_REGISTRAR(line) DUNE_TPCMAP_DETAIL_CAT(DuneTPCMapRegistrar_, line)

/**
 * @brief Register a TPCChannelMap implementation with the factory.
 * @param klass Fully-qualified or unqualified concrete class to register
 *              (must be default-constructible)
 *
 * The registration key is the simple class name (everything after the last "::"),
 * so callers always use e.g. make_tpc_map("VDColdboxTPCChannelMap") regardless
 * of how the class is namespaced.
 */
// NOLINTNEXTLINE(build/define_used)
#define DEFINE_DUNE_DET_TPCCHANNEL_MAP(klass)                                        \
  namespace {                                                                         \
  struct DUNE_TPCMAP_REGISTRAR(__LINE__)                                              \
  {                                                                                   \
    DUNE_TPCMAP_REGISTRAR(__LINE__)()                                                 \
    {                                                                                 \
      std::string full_name = #klass;                                                 \
      auto pos = full_name.rfind("::");                                               \
      std::string name = (pos != std::string::npos)                                  \
                           ? full_name.substr(pos + 2)                                \
                           : full_name;                                               \
      dunedaq::detchannelmaps::TPCChannelMapFactory::instance().register_creator(     \
        name,                                                                         \
        []() -> std::shared_ptr<dunedaq::detchannelmaps::TPCChannelMap> {             \
          return std::make_shared<klass>();                                           \
        });                                                                           \
    }                                                                                 \
  };                                                                                  \
  static DUNE_TPCMAP_REGISTRAR(__LINE__) DUNE_TPCMAP_DETAIL_CAT(s_tpcmap_reg_, __LINE__); \
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

ERS_DECLARE_ISSUE(detchannelmaps,                         ///< Namespace
                  InvalidStreamID,                        ///< Type of the Issue
                  "Invalid stream identifier " << stream, ///< Log Message from the issue
                  ((uint)stream)                          ///< Message parameters
)

ERS_DECLARE_ISSUE(detchannelmaps,                           ///< Namespace
                  InvalidDetectorID,                        ///< Type of the Issue
                  "Invalid detector identifier " << stream, ///< Log Message from the issue
                  ((uint)stream)                            ///< Message parameters
)


namespace detchannelmaps {

class TPCChannelMap
{
public:

  struct TPCChannelInfo
  {
    static constexpr uint16_t kUndefined=0xffff;

    uint16_t detector = kUndefined;
    uint16_t crate = kUndefined;
    uint16_t slot = kUndefined;
    uint16_t stream = kUndefined;
    uint16_t channel = kUndefined;
    uint16_t element = kUndefined;
  };

  /**
   * @brief      Gets the offline channel from detector elements.
   *
   * @param[in]  det            The detector
   * @param[in]  crate          The crate
   * @param[in]  slot           The slot
   * @param[in]  stream         The stream
   * @param[in]  stream_channel The channel in the stream
   *
   * @return     The offline channel from detector elements.
   */
  virtual uint get_offline_channel_from_det_crate_slot_stream_chan(uint det, uint crate, uint slot, uint stream, uint channel) = 0;

  virtual uint get_plane_from_offline_channel(uint offchannel) = 0;
  virtual uint get_element_id_from_offline_channel( uint ) = 0;
  virtual std::string get_element_name_from_offline_channel(uint ) = 0;
  virtual std::optional<TPCChannelInfo> get_channel_info_from_offline_channel(uint offchannel) = 0;
  /**
   * @brief TPCChannelMap destructor
   */
  virtual ~TPCChannelMap() noexcept = default;

protected:
   /**
   * @brief TPCChannelMap Constructor
   * @param name Name of the TPCChannelMap
   */
  explicit TPCChannelMap(){}
};

/**
 * @brief Self-registering factory for TPCChannelMap implementations.
 *
 * Concrete implementations register themselves at static-init time via
 * DEFINE_DUNE_DET_TPCCHANNEL_MAP(klass).  Callers use make_tpc_map(name).
 */
class TPCChannelMapFactory
{
public:
  using Creator = std::function<std::shared_ptr<TPCChannelMap>()>;

  static TPCChannelMapFactory& instance()
  {
    static TPCChannelMapFactory s;
    return s;
  }

  void register_creator(const std::string& name, Creator creator)
  {
    m_registry[name] = std::move(creator);
  }

  std::shared_ptr<TPCChannelMap> make(const std::string& name) const
  {
    auto it = m_registry.find(name);
    if (it == m_registry.end()) {
      throw ChannelMapCreationFailed(ERS_HERE, name);
    }
    return it->second();
  }

private:
  std::map<std::string, Creator> m_registry;
};

/**
 * @brief Instantiate a TPCChannelMap by name.
 * @param plugin_name Name of the registered implementation, e.g. "VDColdboxTPCChannelMap"
 * @return shared_ptr to the created instance
 */
inline std::shared_ptr<TPCChannelMap>
make_tpc_map(std::string const& plugin_name)
{
  return TPCChannelMapFactory::instance().make(plugin_name);
}

} // namespace detchannelmaps

} // namespace dunedaq

#endif // DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_TPCCHANNELMAP_HPP_
