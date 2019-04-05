# QlikSense-IOT
Connect an Esp8266 / NodeMCU with Neopixel as a visualisation device to a QlikSense application


Material needed :
================
- Node MCU / ESP8266
- 2x 330 ohm resistor
- a red led
- a 1mF capacitor
- a breadboard
- a 24 neopixel rig

Installation :
==============

On QlikSense
------------

Qlik Sense desktop 

  Copy the IOT-Graph folder in extensions folder (i.e.  C:\Users\<username>\Documents\Qlik\Sense\Extensions).

Qlik Sense Server
  
  Import IOT-Graph folder in extensions folder.
  See instructions <a href="http://help.qlik.com/en-US/sense/February2019/Subsystems/ManagementConsole/Content/Sense_QMC/import-extensions.htm">Importing extensions</a>

  
On Esp8266 / NodeMCU
--------------------

Install Arduino Ide & configure it for Esp8266:
Just folow the introduction of (before step1): <a href="https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/">Quick Start to Nodemcu / ESP8266 on Arduino IDE</a>


![Alt text](/Esp8266/Schema_schema.png?raw=true "Schema")

Assemble the parts as folowing:
![Alt text](/Esp8266/Schema_bb.png?raw=true "Breadboard schema")

Edit the Esp8266.ino file and configure this part:

```
//set here the wifi mode:
//AP: access point (Pc conected directly throught wifi to the Esp8266)
//Normal: connect the Esp8266 to the wifi of your network
const char* wifimode = "AP";

//WIFI
const char* ssid = "YourWifiSSID";
const char* password = "YourWifiPassword";

//WIFI Access Point
const char* ssid_AP = "QlikSense-IOT";
const char* password_AP = "APWifiPassword";
```

Connect the Esp8266 board to the computer and upload Esp8266.ino to the Esp8266 Board

  
Usage :
=======
Add Extension to the Qlik Sense App
![Alt text](/img/img1.png?raw=true "Add Extension to the Qlik Sense App")

Configure the extension:
Add a mesure with a decimal value between 0 and 1 (or 0% and 100%)
![Alt text](/img/img2.png?raw=true "Configure the extension")

Configure the extension (ip of the Esp8266)
![Alt text](/img/img3.png?raw=true "Configure the extension")





