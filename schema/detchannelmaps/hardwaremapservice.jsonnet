local moo = import "moo.jsonnet";
local ns = "dunedaq.detchannelmaps.hardwaremapservice";
local s = moo.oschema.schema(ns);

local types = {
    short: s.number("DetId_t", "u2", doc="A link identifier"),
    sid: s.number("SourceID_t", "u4", doc="A Source ID"),
    geo_id: s.number("GeoID_t", "u8", doc="A geographic ID for a channel"),
    hostname: s.string("Hostname_t", doc="A host name"),
    flag: s.boolean("Flag", doc="Indicates a true or false condition"),

    hwinfo: s.record("HWInfo", [
      s.field("dro_source_id", self.sid, 0, doc="Source ID of this link"),
      s.field("det_link", self.short, 0, doc="Link ID"),
      s.field("det_slot", self.short, 0, doc="Slot ID"),
      s.field("det_crate", self.short, 0, doc="Crate ID"),
      s.field("det_id", self.short, 0, doc="Detector ID"),
      s.field("dro_host", self.hostname, "", doc="Reaout hostname"),
      s.field("dro_card", self.short, 0, doc="Card ID in readout host"),
      s.field("dro_slr", self.short, 0, doc="SuperLogicRegion of reaodut card"),
      s.field("dro_link", self.short, 0, doc="Link within SLR"),
      s.field("from_file", self.flag, 0, doc="Whether this entry was loaded from the file or created from a GeoID"),
    ], doc="A single readout channel"),
    hwinfos: s.sequence("HWInfos_t", self.hwinfo),
    
    droinfo: s.record("DROInfo", [
      s.field("host", self.hostname, "", doc="Host of this readout unit"),
      s.field("card", self.short, 0, doc="Card ID for this readout unit"),
      s.field("links", self.hwinfos, doc="Links read out by this unit"),
    ], doc="One readout application"),

    geoinfo: s.record("GeoInfo", [
      s.field("det_link", self.short, 0, doc="Link of this channel"),
      s.field("det_slot", self.short, 0, doc="Slot for this channel"),
      s.field("det_crate", self.short, 0, doc="Crate ID for this channel"),
      s.field("det_id", self.short, 0, doc="Detector ID for this channel"),
    ], doc="Hardware coordinates for a channel"),

    hwmap: s.record("HardwareMap", [
      s.field("link_infos", self.hwinfos, doc="Links in the map"),
    ], doc="Locations of all channels within a DAQ Session"),

};

moo.oschema.sort_select(types, ns)
