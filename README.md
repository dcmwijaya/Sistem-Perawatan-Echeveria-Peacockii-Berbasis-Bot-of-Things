[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?logo=github&color=%23F7DF1E)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things)
![Project](https://img.shields.io/badge/Project-Bot%20of%20Things-light.svg?style=flat&logo=arduino&logoColor=white&color=%23F7DF1E)

# Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things
<strong>IoT Master Class Indobot 2022 Final Project</strong><br>
This project is closely related to agricultural technology, where this tool is used to perform automatic watering and to monitor changes in conditions that exist in the environment around Echeveria Peacockii plants in real time from a distance anytime and anywhere. This tool is equipped with a Bot of Things (BoT) based interface that aims to facilitate users in caring for these ornamental plants. Echeveria Peacockii is a type of plant that has a kinship with cacti, but the body of this plant is not found in the presence of thorns, so it is very attractive among ornamental plant lovers.

<br><br>

## Features / Framework / Tools
| Media | Description |
| --- | --- |
| Board Development | DOIT ESP32 DEVKIT V1 |
| Code Editor | Arduino IDE |
| Driver | USB-Serial CP210X |
| IoT Platform | Blynk & ThingsBoard |
| IoT Protocol | MQTT & TCP/IP |
| Architecture | 3 Layer |
| Telegram | Telegram Bot API |
| Arduino Library | WiFi, WiFiClient, PubSubClient, BlynkSimpleEsp32, ArduinoJson, Wire, ESP32_FC28, CTBot, DHT, & LiquidCrystal I2C |
| Actuators | Submersible pump |
| Sensor | FC-28 (Resistive Soil Moisture), LDR (Light Dependent Resistor), DHT22 (Air Temperature & Humidity) |
| Display | LCD I2C |
| Switch | Electrical relay 2 channel |
| Other Components | ESP32 Expansion Board, Breadboard/Projectboard, Adaptor DC, Resistor, & Casing box |

<br><br>

## Download & Install
1. Arduino IDE

   ```
   https://www.arduino.cc/en/software
   ```
<br>

2. USB-Serial CP210X

   ```
   https://bit.ly/CP210X_Driver
   ```
   
<br><br>

## Project Requirements
<table>
<tr>
<th colspan="2">Hardware Design</th>
</tr>
<tr>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/5b54e9a0-2972-46b9-a06b-d8a093266ee9" alt="pictorial-diagram"></td>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3fffa52b-5e16-465a-987a-fba5074de658" alt="schematic-diagram"></td>
</tr>
</table>
<table>
<tr>
<th colspan="2">Software Design</th>
</tr>
<tr>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3c6af705-8d0b-4291-9825-d633338e1f67" alt="flowchart-blynk"></td>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/45c85d49-59ff-4f20-98ce-9405e0c07fe5" alt="flowchart-thingsboard"></td>
</tr>
</table>

<br><br>

## Arduino IDE Setup
1. Open the ``` Arduino IDE ``` first, then open the project by clicking: ``` File ``` -> ``` Open ``` -> ``` SistemPerawatanEcheveriaBlynkIoT.ino ``` or ``` SistemPerawatanEcheveriaThingsboardIoT.ino ```.<br><br>
   
2. Fill in the ``` Additional Board Manager URLs ``` in Arduino IDE<br><br>
   • Method: click ``` File ``` -> ``` Preferences ``` -> enter the ``` Boards Manager Url ``` by copying the following link:
   
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
   
3. ``` Board Setup ``` in Arduino IDE<br><br>
   • Method: click ``` Tools ``` -> ``` Board ``` -> ``` Boards Manager ``` -> Install ``` esp32 ```. Then selecting a Board by clicking: ``` Tools ``` -> ``` Board ``` -> ``` ESP32 Arduino ``` -> ``` DOIT ESP32 DEVKIT V1 ```.<br><br>
   
4. ``` Change the Board Speed ``` in Arduino IDE<br><br>
   • Method: click ``` Tools ``` -> ``` Upload Speed ``` -> ``` 115200 ```.<br><br>
   
5. ``` Install Library ``` in Arduino IDE<br><br>
   • Method: download all the library zip files. Then paste it in the: ``` C:\Users\Computer_Username\Documents\Arduino\libraries ```.<br><br>

6. ``` Port Setup ``` in Arduino IDE<br><br>
   • Method: click ``` Port ``` -> Choose according to your device port ``` (you can see in device manager) ```.<br><br>

7. Change the ``` WiFi Name ```, ``` WiFi Password ```, and so on according to what you are currently using.<br><br>

8. Before uploading the program please click: ``` Verify ```.<br><br>

9. If there is no error in the program code, then please click: ``` Upload ```.

<br><br>

## Get Started
1. Download and extract this repository.
    
2. Make sure you have the necessary electronic components.
   
3. Make sure your components are designed according to the diagram.
      
4. Create an account for the IoT Platform and its services.
    
5. If you don't apply points 2 and 3 for project development purposes, that's fine, but be aware that some things need to be changed according to your needs for the system to work properly.

6. Make sure all things have been created. 
 
7. Please enjoy [Done].

<br><br>

## Highlights
<table>
<tr>
<th width="840">Product</th>
</tr>
<tr>
<td><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/88b94f07-953e-4cdb-84f8-a4849ff031e8" alt="product"></td>
</tr>
</table>
<table>
<tr>
<th colspan="3">Telegram Bot Interface</th>
<th colspan="1">Monitoring via Blynk Mobile</th>
</tr>
<tr>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/d57ba0a1-895b-4d49-99b0-22931c8f99bb" alt="interfacebot-1"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/37cef7d6-f2b2-4e94-8ed6-d696780e13a5" alt="interfacebot-2"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/ce29156a-5f1b-4231-a1d9-4ba03e28bea5" alt="interfacebot-3"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/e3d0fb05-4668-4e33-a186-002f538d8ddb" alt="blynk-mobile"></td>
</tr>
</table>
<table>
<tr>
<th width="840">Monitoring via Thingsboard</th>
</tr>
<tr>
<td><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/48380dd7-cb7c-4c7d-ae1c-e637bf9adacf" alt="thingsboard"></td>
</tr>
</table>

<br><br>

## Disclaimer
This application has been created by including third-party sources. Third parties here are service providers, whose services are in the form of libraries, frameworks, and others. I thank you very much for the service. It has proven to be very helpful and implementable.

<br><br>

## LICENSE
MIT License - Copyright (c) 2023 - Devan C. M. Wijaya, S.Kom

Permission is hereby granted without charge to any person obtaining a copy of this software and the software-related documentation files to deal in them without restriction, including without limitation the right to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons receiving the Software to be furnished therewith on the following terms:

The above copyright notice and this permission notice must accompany all copies or substantial portions of the Software.

IN ANY EVENT, THE AUTHOR OR COPYRIGHT HOLDER HEREIN RETAINS FULL OWNERSHIP RIGHTS. THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, THEREFORE IF ANY DAMAGE, LOSS, OR OTHERWISE ARISES FROM THE USE OR OTHER DEALINGS IN THE SOFTWARE, THE AUTHOR OR COPYRIGHT HOLDER SHALL NOT BE LIABLE, AS THE USE OF THE SOFTWARE IS NOT COMPELLED AT ALL, SO THE RISK IS YOUR OWN.
