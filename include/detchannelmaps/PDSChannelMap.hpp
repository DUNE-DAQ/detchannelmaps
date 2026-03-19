#ifndef DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_
#define DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_

#include "ers/Issue.hpp"
#include "logging/Logging.hpp" // NOTE: if ISSUES ARE DECLARED BEFORE include logging/Logging.hpp, TLOG_DEBUG<<issue wont work.
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>


// Helper macros for unique struct names that survive __LINE__ expansion
// NOLINTNEXTLINE(build/define_used)
#define DUNE_PDSMAP_DETAIL_CAT(a, b) a##b
// NOLINTNEXTLINE(build/define_used)
#define DUNE_PDSMAP_REGISTRAR(line) DUNE_PDSMAP_DETAIL_CAT(DunePDSMapRegistrar_, line)

/**
 * @brief Register a PDSChannelMap implementation with the factory.
 * @param klass Fully-qualified or unqualified concrete class to register
 *              (must be default-constructible)
 *
 * The registration key is the simple class name (everything after the last "::").
 */
// NOLINTNEXTLINE(build/define_used)
#define DEFINE_DUNE_DET_PDSCHANNEL_MAP(klass)                                        \
  namespace {                                                                         \
  struct DUNE_PDSMAP_REGISTRAR(__LINE__)                                              \
  {                                                                                   \
    DUNE_PDSMAP_REGISTRAR(__LINE__)()                                                 \
    {                                                                                 \
      std::string full_name = #klass;                                                 \
      auto pos = full_name.rfind("::");                                               \
      std::string name = (pos != std::string::npos)                                  \
                           ? full_name.substr(pos + 2)                                \
                           : full_name;                                               \
      dunedaq::detchannelmaps::PDSChannelMapFactory::instance().register_creator(     \
        name,                                                                         \
        []() -> std::shared_ptr<dunedaq::detchannelmaps::PDSChannelMap> {             \
          return std::make_shared<klass>();                                           \
        });                                                                           \
    }                                                                                 \
  };                                                                                  \
  static DUNE_PDSMAP_REGISTRAR(__LINE__) DUNE_PDSMAP_DETAIL_CAT(s_pdsmap_reg_, __LINE__); \
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

    struct PDSChannelInfo
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

  virtual uint get_element_from_offline_channel(uint ) = 0;
  virtual std::string get_element_name_from_offline_channel(uint ) = 0;
  virtual std::optional<PDSChannelInfo> get_det_crate_slot_fiber_chan_from_offline_channel(uint offchannel) = 0;
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
 * @brief Self-registering factory for PDSChannelMap implementations.
 *
 * Concrete implementations register themselves at static-init time via
 * DEFINE_DUNE_DET_PDSCHANNEL_MAP(klass).  Callers use make_pds_map(name).
 */
class PDSChannelMapFactory
{
public:
  using Creator = std::function<std::shared_ptr<PDSChannelMap>()>;

  static PDSChannelMapFactory& instance()
  {
    static PDSChannelMapFactory s;
    return s;
  }

  void register_creator(const std::string& name, Creator creator)
  {
    m_registry[name] = std::move(creator);
  }

  std::shared_ptr<PDSChannelMap> make(const std::string& name) const
  {
    auto it = m_registry.find(name);
    if (it == m_registry.end()) {
      throw PDSChannelMapCreationFailed(ERS_HERE, name);
    }
    return it->second();
  }

private:
  std::map<std::string, Creator> m_registry;
};

/**
 * @brief Instantiate a PDSChannelMap by name.
 * @param plugin_name Name of the registered implementation, e.g. "SimplePDSChannelMap"
 * @return shared_ptr to the created instance
 */
inline std::shared_ptr<PDSChannelMap>
make_pds_map(std::string const& plugin_name)
{
  return PDSChannelMapFactory::instance().make(plugin_name);
}

} // namespace detchannelmaps

} // namespace dunedaq

#endif // DETCHANNELMAPS_INCLUDE_DETCHANNELMAPS_PDSCHANNELMAP_HPP_
