# Dummies Guide to writing HardwareMap files

12-Oct-2022, KAB: we can/should add to this document as we think of more things that users should know when they attempt to write valid HardwareMap files, but I wanted to start with a couple of notes that I (re)learned today.

Things to keep in mind:

1. Each row in the HardwareMap file will result in a DataLinkHandler (module) instance being created in the resulting system.
2. The number of Readout Apps is controlled by the unique combinations of DRO_Host and DRO_Card.  Given this, one needs to be careful to specify different DRO_Card values when creating HardwareMap files for smaller tests environments, on which several Readout Apps are desired on the same computer.
