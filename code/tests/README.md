## GPIO pins Testing

- head to https://www.pitunnel.com/devices
- login to the Raspberry Pi
- Then:

```bash
# cd to the code dir
cd Projects/HomeSecurity/code/tests/read_pins
# open the read_pins.cpp file & make your changes
nano read_pins.cpp
# compile the file
g++ -Wall -o read_pins read_pins.cpp -lwiringPi
# run 
./read_pins
```

## [Thingers-io](http://Thingers.io) client Testing
**Test thinger client with the test circuit**

> [Guide Link](https://www.whitelist1.com/2017/08/thingerio-iot-platform-ii-controlling.html)

```bash
cd Projects/HomeSecurity/code/tests/thinger_client
./run.sh
```

## Testing Notes
- We can use the gpio utility to check pins
- Reference [GPIO Docs](http://wiringpi.com/the-gpio-utility/)
```bash
gpio read pin_num # reads pin state
gpio readall # shows all pins
gpio mode pin_num state # set pin mode in/out/up(Pullup)/down
```

## Project Structure
```bash
.
├── code
│   ├── ss.txt
│   ├── tests
│   │   ├── README.md
│   │   ├── read_pins
│   │   │   └── read_pins.cpp
│   │   └── thinger_client
│   │       ├── build
│   │       ├── cmake
│   │       ├── CMakeLists.txt
│   │       ├── install
│   │       ├── README.md
│   │       ├── run.sh
│   │       ├── src
│   │       └── WiringPi
│   └── thinger_client
│       ├── cmake
│       │   └── modules
│       ├── CMakeLists.txt
│       ├── install
│       │   ├── intel_edison
│       │   └── raspberry
│       ├── README.md
│       ├── run.sh
│       └── src
│           ├── main.cpp
│           ├── thinger
│           └── wiringPi.h
├── docs
│   └── s.txt
└── Schematic
    └── sssss.txt

```

