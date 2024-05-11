# HomeKit Soil Moisture Sensor

## About
This project creates a HomeKit-compatible accessory with a NodeMCU that measures soil moisture levels and sends the information to Apple's HomeKit app. Since HomeKit does not natively support a soil moisture sensor, the humidity sensor representation is used to display soil moisture levels.

## Installation
1. If you haven't worked with an ESP8266 before, please follow the [Installing ESP8266 Board in Arduino IDE guide](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/).
2. Install the [Arduino HomeKit ESP8266 library](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) in the Arduino IDE.
3. Download this repository or copy its contents to your Sketch.
4. Update `wifi_info.h` with your Wi-Fi credentials.
5. Upload files to your NodeMCU.
6. Add the accessory to HomeKit App using the code 111-11-111 (edit `my_accessory.c` if you want to change) 

## Components
* NodeMCU (ESP8266)
* Soil Moisture Sensor
* USB Power Adapter 
* Optionally: Breadboard power supply

## Circuit Diagram
![Image](circuit%20design_updated.png)
I didn't use the original breadboard power supply, and the NodeMCU is powered directly via a USB power adapter. You may add the breadboard power supply to the circuit without any adjustments to the scripts.

## Moisture Levels Details
The soil moisture sensor outputs data ranging from 0 to 1024, where 0 represents maximum moisture and 1024 represents no moisture. This data is converted to a percentage scale from 0 to 100 to be compatible with HomeKit, where 0% indicates no moisture and 100% indicates maximum moisture.

## Thanks
* Thanks to [Mixiaoxiao](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) for providing the HomeKit library that enables the integration of the NodeMCU with Apple HomeKit.

### Original Project
* This project is a fork of the [original HomeKit Soil Moisture Sensor project](https://github.com/shubhsheth/iot-moisture-sensor) by shubhsheth.

#### Summary of Changes
- Refactoring the variable names for clarity and streamlined scripts.
- Detailed README and installation instructions
- Applied without the original breadboard power supply

