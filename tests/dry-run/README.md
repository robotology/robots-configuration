CI Dry-Run of `yarprobotinterface`
==================================

The CI can perform two types of dry-run:
1. XML dry-run, to check the consistency of the XML files: e.g., missing files, malformed syntax...
2. DEV dry-run, to check the consistency of the devices: e.g., missing parameters, deprecated devices...

The output of the dry-run is stored as artifact within the CI workflow to enable later inspection.

### Invoking `ctest`

#### List available tests
```console
ctest -N
```

#### Run specific tests
```console
ctest -R test_name
ctest -R "test.*"
```

#### Run tests associated to specific labels
```console
ctest -L "label_1;label_2"
```

#### Run all available tests
```console
ctest
```

### Tests skipped
Tests that have to be excluded are listed in `skip_tests.txt` file.
