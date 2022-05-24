///////////////////////////////////////////////////////////////////////////////////////////////////
// Class:       PD2HDChannelMapService
// Module type: service
// File:        PD2HDChannelMapService.h
// Author:      Tom Junk, May 2022
//
// Implementation of hardware-offline channel mapping reading from a file.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PD2HDChannelMapService.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

dune::PD2HDChannelMapService::PD2HDChannelMapService(std::string filename) {

  std::ifstream inFile(filename, std::ios::in);
  if (inFile.bad() || inFile.fail() || !inFile.is_open()) {
    throw std::runtime_error(std::string("Bad map file ") + std::string(filename));
  }

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
      >> chanInfo.asicchan; 

    chanInfo.valid = true;

    // fill maps.

    if (chanInfo.offlchan >= fNChans)
      {
	throw cet::exception("PD2HDChannelMapService") << "Ununderstood Offline Channel: " << chanInfo.offlchan << "\n";
      }

    DetToChanInfo[chanInfo.crate][chanInfo.wib][chanInfo.link][chanInfo.femb_on_link][chanInfo.plane][chanInfo.chan_in_plane] = chanInfo;
    OfflToChanInfo[chanInfo.offlchan] = chanInfo;

  }
  inFile.close();

}


dune::PD2HDChannelMapService::HDChanInfo_t dune::PD2HDChannelMapService::GetChanInfoFromDetectorElements(unsigned int crate, unsigned int slot, unsigned int link, unsigned int femb_on_link, unsigned int plane, unsigned int chan_in_plane ) const {

  unsigned int wib = slot + 1;

  HDChanInfo_t badInfo = {};
  badInfo.valid = false;

  auto fm1 = DetToChanInfo.find(crate);
  if (fm1 == DetToChanInfo.end()) return badInfo;
  auto& m1 = fm1->second;

  auto fm2 = m1.find(wib);
  if (fm2 == m1.end()) return badInfo;
  auto& m2 = fm2->second;

  auto fm3 = m2.find(link);
  if (fm3 == m2.end()) return badInfo;
  auto& m3 = fm3->second;

  auto fm4 = m3.find(femb_on_link);
  if (fm4 == m3.end()) return badInfo;
  auto& m4 = fm4->second;

  auto fm5 = m4.find(plane);
  if (fm5 == m4.end()) return badInfo;
  auto& m5 = fm5->second;

  auto fm6 = m5.find(chan_in_plane);
  if (fm6 == m5.end()) return badInfo;

  return fm6->second;
}


dune::PD2HDChannelMapService::HDChanInfo_t dune::PD2HDChannelMapService::GetChanInfoFromOfflChan(unsigned int offlineChannel) const {
  auto ci = OfflToChanInfo.find(offlineChannel);
  if (ci == OfflToChanInfo.end()) 
    {
      HDChanInfo_t badInfo = {};
      badInfo.valid = false;
      return badInfo;
    }
  return ci->second;

}


DEFINE_ART_SERVICE(dune::PD2HDChannelMapService)
