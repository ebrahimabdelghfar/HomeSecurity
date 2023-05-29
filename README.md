## GIPO pins Testing

- head to https://www.pitunnel.com/devices
- login to the Raspberry Pi
- Then:

```bash
# cd to the code dir
cd Projects/HomeSecurity/code
# open the read_pins.cpp file & make your changes
nano read_pins.cpp
# compile the file
g++ -Wall -o read_pins read_pins.cpp -lwiringPi
# run 
./read_pins
```

## [Thingers-io](http://Thingers.io) client Testing