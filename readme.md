# Dingus (name is work in progress)

Dingus is a project made as an assignment for the course "Projeto em Eletrônica" at the University of Santa Catarina. The project consists of a device that can be used to read useful data from a car's OBD-II port trough a bluetooth ELM327 module.

## Features

- Read and display RPM, speed, coolant temperature, throttle position, intake air temperature, fuel level, fuel pressure, intake manifold pressure, engine load, fuel consumption, battery voltage, and more.
- Display data in a user-friendly interface on a 16x2 LCD screen.
- Send custom commands to the ELM327 module to read any data available.
- Save data to an SD card for later analysis. (maybe)

## Hardware

- ESP32 microcontroller (WROOM-32 in a NodeMCU-32S devkit board)
- 16x2 LCD I2C Display (with a PCF8574 I2C expander)
- ELM327 bluetooth module
- 16 buttons (4x4 matrix)
- Built-in battery charger and voltage regulator
- SD card module (maybe)

## Software

- PlatformIO
- Arduino framework
- Arduino libraries: LiquidCrystal_I2C, BluetoothSerial, SD (maybe), ELMduino, etc.
- Custom libraries for interfacing with the buttons and the LCD display
- Arduino IDE for newer versions of some libraries that are not available in PlatformIO (specifically BluetoothSerial):
  - We had to use the newer version of the library to be able to remove all previously paired devices from the ESP32's memory, as the older version did not have this feature.
  - The newer version of the library is not available in PlatformIO, so we had to use the Arduino IDE to install it.

## Authors

- João Assoni
- [Leonardo Henrique Dill Bruxel](https://github.com/brxxxl/)
- Rafaella Rivello Dal Pont
