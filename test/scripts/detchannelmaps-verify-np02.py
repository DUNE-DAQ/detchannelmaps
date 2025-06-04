#!/usr/bin/env python

import detchannelmaps
from rich import print

def print_och( tpc_map, och: int):
    ci = tpc_map.get_channel_info_from_offline_channel(och)
    print(f"{och} -> ci det {ci.detector} crate {ci.crate} slot {ci.slot} stream {ci.stream} channel {ci.channel}")
    xxx = tpc_map.get_offline_channel_from_det_crate_slot_stream_chan(ci.detector, ci.crate, ci.slot, ci.stream, ci.channel);
    print(f"och {och} -> {xxx}")


np02vd_bot = detchannelmaps.make_tpc_map('PD2VDBottomTPCChannelMap')
for i in range(3400, 3500):
    print_och(np02vd_bot, i)

print("-"*80)

np02vd = detchannelmaps.make_tpc_map('PD2VDTPCChannelMap')
for i in range(3400, 3416):
    print_och(np02vd, i)

print("-"*80)


np02hd = detchannelmaps.make_tpc_map('PD2HDTPCChannelMap')
for i in range(1609, 1614):
    print_och(np02hd, i)