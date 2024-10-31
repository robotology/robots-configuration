This setup uses two motors: one motor is controlled by the `amc` and the other by the `amcbldc`.
The first joint, the one linked to the `amcbldc` has the encoder `aea3` connected to the connector `J5_X1` and the motor linked to the board itself.
The `amcbldc` is connected to the `amc` on `CAN1:1`.
The second joint is linked to the `amc` and has the encoder on the connector `J5_X2`.
This setup is configured to be used with `yarprobotinterface` and `yarpmotorgui`.
This setup works with motors that have a `Gearbox_M2J` of 196.
All this parameters can be changed in the configuration files.
See pictures in setup media for additional help.
