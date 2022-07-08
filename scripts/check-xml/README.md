# check-xml
This folder contains tools dedicated to `XML` files check.

## Content
Available tools are :

- [`check-nws-nwc-xml`](./check-nws-nwc-xml/README.md)

___
### check-nws-nwc-xml
This tool has been developed due to the need to check `xml` files consistency for `CAN` based robots after manual modification due to the new `NWS/NWC` layers implemented in `YARP-3.5`.

in fact, while for ethernet based robots, we have the possibility to run `yarprobotinterface` in dry-run mode (without having the phisical robot connected), as for now this is not possible on `CAN` based robots.

Considering the effort to update the parser in order to allow the dry-run mode also for `CAN` based robots, we opted to proceed writing a dedicated program using both `XSD` and `XPATH` technologies.
