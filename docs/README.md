# DUNE Detectors Channel Maps

This repository contains the implementations of hardware-offline channel mappings. It defines a plugin called `TPCChannelMap` which consists of two functions:
* `get_offline_channel_from_crate_slot_fiber_chan`: this translates from crate, slot, fiber and FEMB channel numbers into the offline channel number
* `get_plane_from_offline_channel`: this translates from offline channel number into plane number

A table of available channel map plugins is listed [here](channel-maps-table.md). One can use
```bash
cat CMakeLists.txt | sed -n "s/.*( \([^ ]*ChannelMap\).*/\1/p"
```
to see the channel maps that are being built (this may be a useful cross-check).
