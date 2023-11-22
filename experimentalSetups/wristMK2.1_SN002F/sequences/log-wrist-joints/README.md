# Log wrist joints data
This Yarp application can be used to read the following information from the control boards of the wrist:

- Motor PID reference
- Motor PID error
- Motor PID output
- Roll, pitch, yaw angles 

## Compile the code
In order to compile the [code](src/main.cpp) do :

```console
mkdir build
cd build 
ccmake .. # select your preferred options
make
```

## Usage
First make sure that `yarpserver` is running.
Navigate to the `build` folder you created above, and in a terminal launch the binary with `./logwristjoints`.
The application accepts the following arguments:
- `--remote`: the remote port to connect to - default `/nfa_wrist/mc`
- `--period`: the period in seconds at which the logging thread runs - default 0.01sec
- `--file`: the file in which the logged data is stored - default `log.csv`

The file is saved to disk when you exit the application with ctrl-C (SIGINT).
The output file will be located in the `build` folder, and it will be made by records with comma-delimited columns. Each column has a properly defined header.

