# IR remote translator
Translates IR basic commands from LG remote to Samsung home cinema

| Command  | LG   ==> | Samsung  |
| -------- | -------- | -------- |
| ON/OFF   | 20DF10EF | C2CA807F |
| Vol+     | 20DF40BF | C2CACC33 |
| Vol-     | 20DFC03F | C2CADC23 |
| Mute     | 20DF906F | C2CA9C63 |


## Prerequisites
Arduino libraries used in this project:

- [IRremote](https://github.com/z3t0/Arduino-IRremote)

## Usage

Connect IR receiver to pin 11 and IR led to pin 3

## Credits

* **Henry's Bench** - *IR Remote tutorial* - [henrysbench](http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-xinda-keyes-infrared-remote-tutorial/)