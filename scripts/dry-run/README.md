CI Dry-Run of `yarprobotinterface`
==================================

The CI can perform two types of dry-run:
1. XML dry-run, to check the consistency of the XML files: e.g., missing files, malformed syntax...
2. DEV dry-run, to check the consistency of the devices: e.g., missing parameters, deprecated devices...

The output of the dry-run is stored as artifact within the CI workflow to enable later inspection.
