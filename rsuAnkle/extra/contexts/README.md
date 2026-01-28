# Additional Context

To enable the yarpmanager context please add this line in your `.bashrc`

```bash
export YARP_DATA_DIRS=${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/src/robots-configuration/${YARP_ROBOT_NAME}/extra:${YARP_DATA_DIRS:+${YARP_DATA_DIRS}:}
```

