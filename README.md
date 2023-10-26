[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things)
![Project](https://img.shields.io/badge/Project-Bot%20of%20Things-light.svg?style=flat&logo=github&logoColor=white&color=bcbcbc)
![Platform-IoT-Blynk-Thingsboard](https://img.shields.io/badge/Platform-Blynk-%2DThingsboard-light.svg?style=flat&logo=GoogleChrome&logoColor=white&color=bcbcbc)
![Bot-IoT](https://img.shields.io/badge/Based-Telegram%20Bot-light.svg?style=flat&logo=telegram&logoColor=white&color=bcbcbc)
![Arduino](https://img.shields.io/badge/Tools-Arduino%20IDE-light.svg?style=flat&logo=arduino&logoColor=white&color=bcbcbc)

# Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things
<strong>IoT Master Class Indobot 2022 Final Project</strong><br>
This project is closely related to agricultural technology, where this tool is used to perform automatic watering and to monitor changes in conditions that exist in the environment around Echeveria Peacockii plants in real time from a distance anytime and anywhere. This tool is equipped with a Bot of Things (BoT) based interface that aims to facilitate users in caring for these ornamental plants. Echeveria Peacockii is a type of plant that has a kinship with cacti, but the body of this plant is not found in the presence of thorns, so it is very attractive among ornamental plant lovers.

<br>

## Features / Framework / Tools
| Media | Description |
| --- | --- |
| IoT Broker | Blynk & ThingsBoard |
| MCU | DOIT ESP32 DEVKIT V1 |
| Arduino Library | WiFi, WiFiClient, PubSubClient, BlynkSimpleEsp32, ArduinoJson, Wire, ESP32_FC28, CTBot, DHT, & LiquidCrystal I2C |
| Telegram | Telegram Bot API |
| Actuators | Submersible pump |
| Sensor | FC-28 (Resistive Soil Moisture), LDR (Light Dependent Resistor), DHT22 (Air Temperature & Humidity) |
| Display | LCD I2C |
| Switch | Electrical relay 2 channel |
| Other Components | ESP32 Expansion Board, Breadboard/Projectboard, Adaptor DC, Resistor, & Casing box |

<br>

## Download & Install
Download Arduino IDE :
```bash
https://www.arduino.cc/en/software
```

<br>

## Settings
1. Open the Arduino IDE first, then enter the Boards Manager Url by copying the following link:
```bash
https://dl.espressif.com/dl/package_esp32_index.json
```
2. Board Setup in Arduino IDE
   <ul>
      <li>Method: click Boards Manager -> ESP32 Arduino -> DOIT ESP32 DEVKIT V1.</li>
   </ul>
3. Port Setup in Arduino IDE
   <ul>
      <li>Method: click Port -> Choose according to your device port (you can see in device manager).</li>
   </ul>
4. Install Library in Arduino IDE
   <ul>
      <li>Method: click Tools -> Manage Libraries -> Install Library according to project needs.</li>
   </ul>

<br>

## Hardware Design


<br>

## Software Design


<br>

## Running
1. Download this Repository.
2. Make sure you have the necessary electronic components.
3. Make sure your components have been designed according to the diagram.
4. Make sure the components are well connected (Adjust Board and Port settings).
5. It is recommended to create a Broker account along with this service.
6. Make sure to change the arduino program code in the "Router" section according to the device you are using.
7. If you do not apply points 2 and 3 for the purposes of project development, it is fine, but please note that some things need to be changed in order to function properly.
8. Done, good luck.

<br>

## Preview: Product
![IMG20221230182747](https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/88b94f07-953e-4cdb-84f8-a4849ff031e8)

<br>

## Preview: Telegram Bot Interface
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/d57ba0a1-895b-4d49-99b0-22931c8f99bb" width=200 height=450>&emsp;&emsp;
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/37cef7d6-f2b2-4e94-8ed6-d696780e13a5" width=200 height=450>&emsp;&emsp;
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/ce29156a-5f1b-4231-a1d9-4ba03e28bea5" width=200 height=450>
   
<br>

Notes: This project requires internet and electricity supply to run the application.

<br><br>

## LICENSE
MIT License - Copyright (c) 2023 - Devan C. M. Wijaya, S.Kom

Permission is hereby granted without charge to any person obtaining a copy of this software and the software-related documentation files to deal in them without restriction, including without limitation the right to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons receiving the Software to be furnished therewith on the following terms:

The above copyright notice and this permission notice must accompany all copies or substantial portions of the Software.

IN ANY EVENT, THE AUTHOR OR COPYRIGHT HOLDER HEREIN RETAINS FULL OWNERSHIP RIGHTS. THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, THEREFORE IF ANY DAMAGE, LOSS, OR OTHERWISE ARISES FROM THE USE OR OTHER DEALINGS IN THE SOFTWARE, THE AUTHOR OR COPYRIGHT HOLDER SHALL NOT BE LIABLE, AS THE USE OF THE SOFTWARE IS NOT COMPELLED AT ALL, SO THE RISK IS YOUR OWN.
