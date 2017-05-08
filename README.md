![windy](./docs/windy.png)
# Windy

WiFi Fan Control for Corsair HD120 RGB LED High Performance 120mm PWM Fan

The goal is to make a group of Corsair HD120 fans programmable via WiFi

## Requirements

### Software

1. MQTT broker (Mosquitto..etc)
1. Node.js v6.9 LTS
1. Platform.IO IDE
1. (Optional) Docker

### Hardware

Below are the parts that I used in this project, feel free to use any equivalent parts you like.

1. ESP8266 (ESP-12F)
1. Arduino (Arduino Pro Mini 328 5V/16MHz)
1. Corsair HD120 Fan

## Hardware Schematic

TODO

## Getting Started

1. Hook up the circuit
1. Compile code
1. Download binaries to ESP8266 and Arduino
1. `npm start` or `docker build ./ -t windy-app && docker run --name windy-app -d -p 3000:3000 -p 1883:1883 windy-app`
1. Go to http://localhost:3000
