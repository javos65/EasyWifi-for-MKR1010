# EasyWifi-for-MKR1010
EasyWifi setup for Arduino MKR1010 modules with uBLox Nina (ESP32) wifi

EasyWifi means ifi setup without storing your credentials (SSID/Password) in your code, and have easy credential input by means of a Wifi AccessPoint entry by smartphone.

Based on Wifi-library for NINA uBlox.
This supports the class EasyWiFi
EasyWiFi.start(): starts wifi setup, reading credentials (if avaialble) from flash-disk on the Module and start Wifi login.
If wireless connection is not possible, start up AccessPoint with DNS-reply, forcing Mobile/Smartphone to open AP-webpage.
Enter your credentials by phone and store them back in Flash.

no Credentials in your code.
Credentials are Cyphered stored for  back-reading protection (simplistic, but ok)
use .SEED setting to change the Cyphering.
use .APNAME to set the AccessPoint name
use .ERASE to erase your credentials from the module

Feel free to add or modify for other Wifi module support, as lonmg as you have a Flash-file system.

V1.1.0 - JayFox 2020
