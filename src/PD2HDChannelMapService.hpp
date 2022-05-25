///////////////////////////////////////////////////////////////////////////////////////////////////
// Class:       PD2HDChannelMapService
// Module type: service
// File:        PD2HDChannelMapService.h
// Author:      Tom Junk, May 2022
//
// Implementation of hardware-offline channel mapping reading from a file.  
// ProtoDUNE-2 Horizontal Drift APA wire to offline channel map
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DETCHANNELSMAP_PD2HDCHANNELMAPSERVICE_H_
#define DETCHANNELSMAP_PD2HDCHANNELMAPSERVICE_H_

#include <map>
#include <vector>
#include <limits>
#include <unordered_map>


namespace dune {
  class PD2HDChannelMapService;
}

class dune::PD2HDChannelMapService {

public:

  PD2HDChannelMapService(std::string mapfile);

  typedef struct HDChanInfo {
    unsigned int offlchan;        // in gdml and channel sorting convention
    unsigned int crate;           // crate number
    std::string APAName;          // Descriptive APA name
    unsigned int wib;             // 1, 2, 3, 4 or 5  (slot number +1?)
    unsigned int link;            // link identifier: 0 or 1
    unsigned int femb_on_link;    // which of two FEMBs in the WIB frame this FEMB is:  0 or 1
    unsigned int cebchan;         // cold electronics channel on FEMB:  0 to 127
    unsigned int plane;           // 0: U,  1: V,  2: X
    unsigned int chan_in_plane;   // which channel this is in the plane in the FEMB:  0:39 for U and V, 0:47 for X
    unsigned int femb;            // which FEMB on an APA -- 1 to 20
    unsigned int asic;            // ASIC:   1 to 8
    unsigned int asicchan;        // ASIC channel:  0 to 15
    unsigned int wibframechan;    // channel index in WIB frame (used with get_adc in detdataformats/WIB2Frame.hh).  0:255
    bool valid;          // true if valid, false if not
  } HDChanInfo_t;

  /////////////////////////\ ProtoDUNE-SP channel map functions //////////////////////////////

  // TPC channel map accessors

  // Map instrumentation numbers (crate:slot:link:FEMB:plane) to offline channel number.  FEMB is 0 or 1 and indexes the FEMB in the WIB frame.
  // plane = 0 for U, 1 for V and 2 for X

  HDChanInfo_t GetChanInfoFromDetectorElements(
   unsigned int crate,
   unsigned int slot,
   unsigned int link,
   unsigned int femb_on_link,
   unsigned int plane,
   unsigned int chan_in_plane) const;

  HDChanInfo_t GetChanInfoFromWIBElements(
   unsigned int crate,
   unsigned int slot,
   unsigned int link,
   unsigned int wibframechan) const;

  HDChanInfo_t GetChanInfoFromOfflChan(unsigned int offlchan) const;

private:

  const unsigned int fNChans = 2560*4;

  // map of crate, slot, link, femb_on_link, plane, chan to channel info struct

  std::unordered_map<unsigned int,   // crate
    std::unordered_map<unsigned int, // wib
    std::unordered_map<unsigned int, // link
    std::unordered_map<unsigned int, // wibframechan
    HDChanInfo_t > > > > DetToChanInfo;

  // map of chan info indexed by offline channel number

  std::unordered_map<unsigned int, HDChanInfo_t> OfflToChanInfo;

  //-----------------------------------------------

  void check_offline_channel(unsigned int offlineChannel) const
  {
  if (offlineChannel >= fNChans)
    {      
      throw std::range_error("PD2HDChannelMapService: Offline TPC Channel Number out of range: "+ std::to_string(offlineChannel)); 
    }
  };

};

#endif