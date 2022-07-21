///////////////////////////////////////////////////////////////////////////////////////////////////
// Class:       PD2HDChannelMapSP
// Module type: standalone algorithm
// File:        PD2HDChannelMapSP.cxx
// Author:      Tom Junk, May 2022
//
// Implementation of hardware-offline channel mapping reading from a file.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PD2HDChannelMapSP.h"

#include <iostream>
#include <fstream>
#include <sstream>

// so far, nothing needs to be done in the constructor

dune::PD2HDChannelMapSP::PD2HDChannelMapSP()
{
}

void dune::PD2HDChannelMapSP::ReadMapFromFile(std::string &fullname)
{
  std::ifstream inFile(fullname, std::ios::in);
  std::string line;

  while (std::getline(inFile,line)) {
    std::stringstream linestream(line);

    HDChanInfo_t chanInfo;
    linestream 
      >> chanInfo.offlchan 
      >> chanInfo.crate 
      >> chanInfo.APAName
      >> chanInfo.wib 
      >> chanInfo.link 
      >> chanInfo.femb_on_link 
      >> chanInfo.cebchan 
      >> chanInfo.plane 
      >> chanInfo.chan_in_plane 
      >> chanInfo.femb 
      >> chanInfo.asic 
      >> chanInfo.asicchan
      >> chanInfo.wibframechan; 

    chanInfo.valid = true;

    // fill maps.

    check_offline_channel(chanInfo.offlchan);

    DetToChanInfo[chanInfo.crate][chanInfo.wib][chanInfo.link][chanInfo.wibframechan] = chanInfo;
    OfflToChanInfo[chanInfo.offlchan] = chanInfo;

  }
  inFile.close();

}

dune::PD2HDChannelMapSP::HDChanInfo_t dune::PD2HDChannelMapSP::GetChanInfoFromWIBElements(
    unsigned int crate,
    unsigned int slot,
    unsigned int link,
    unsigned int wibframechan ) const {

  unsigned int wib = slot + 1;

  HDChanInfo_t badInfo = {};
  badInfo.valid = false;

// a hack -- ununderstood crates are mapped to crate 2
// for use in the Coldbox
// crate 2 has the lowest-numbered offline channels
// data with two ununderstood crates, or an ununderstood crate and crate 2,
// will have duplicate channels.

  auto fm1 = DetToChanInfo.find(crate);
  if (fm1 == DetToChanInfo.end()) 
    {
      unsigned int substituteCrate = 2;  
      fm1 = DetToChanInfo.find(substituteCrate);
      if (fm1 == DetToChanInfo.end()) return badInfo;
    }
  auto& m1 = fm1->second;

  auto fm2 = m1.find(wib);
  if (fm2 == m1.end()) return badInfo;
  auto& m2 = fm2->second;

  auto fm3 = m2.find(link);
  if (fm3 == m2.end()) return badInfo;
  auto& m3 = fm3->second;

  auto fm4 = m3.find(wibframechan);
  if (fm4 == m3.end()) return badInfo;
  return fm4->second;
}


dune::PD2HDChannelMapSP::HDChanInfo_t dune::PD2HDChannelMapSP::GetChanInfoFromOfflChan(unsigned int offlineChannel) const {
  auto ci = OfflToChanInfo.find(offlineChannel);
  if (ci == OfflToChanInfo.end()) 
    {
      HDChanInfo_t badInfo = {};
      badInfo.valid = false;
      return badInfo;
    }
  return ci->second;

}
