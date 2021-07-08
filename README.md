Robots Configuration
====================

[![ZenHub](https://img.shields.io/badge/Shipping_faster_with-ZenHub-435198.svg)](https://zenhub.com)
[![Community](https://img.shields.io/badge/Join-Robotology_Community-blue?style=plastic&logo=github)](https://github.com/robotology/community)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)

## Maintainers
This repository is maintained by:

| | |
|:---:|:---|
| [<img src="https://github.com/pattacini.png" width="40">](https://github.com/pattacini) | [@pattacini](https://github.com/pattacini) |

## Installation

### Dependencies
Make sure you have available the following resources:
- [YARP](https://github.com/robotology/yarp)
- [icub-contrib-common](https://github.com/robotology/icub-contrib-common)

### Setting up your Robot
Unless you aim to install the configurations of all robots, you have to specify
the name of your own robot by means of the environment variable **`YARP_ROBOT_NAME`**.
Example:
```sh
export YARP_ROBOT_NAME=iCubGenova01
```

### Build
From the repository root level do:
```sh
$ mkdir build
$ cd build
$ cmake ../
$ make install
```
As result, the configurations files of your own robot should be placed in `$ICUBcontrib_DIR/share/ICUBcontrib/robots/$YARP_ROBOT_NAME`.

From this location you may want to tune/modify certain parameters by first copying
out the installed files into user local directories. To this end, rely on the command below:
```sh
$ yarp-config robot --import $YARP_ROBOT_NAME
```

You should end up finding the local copies under `~/.local/share/yarp/robots/$YARP_ROBOT_NAME`.

## Contributing
We accept contributions via [forks and pull-requests](https://guides.github.com/activities/forking).

**Working on your first Pull Request?** You can learn how from this *free* series [How to Contribute to an Open Source Project on GitHub](https://kcd.im/pull-request)

## License
Material included here is Copyright of _iCub Facility - Istituto Italiano di
Tecnologia_ and is released under the terms of the GPL v2.0 or later.
See the file LICENSE for details.
