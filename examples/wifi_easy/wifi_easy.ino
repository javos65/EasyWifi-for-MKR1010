/*
Easy WiFi - build for MKR1010 / WIFININA using the uBlox NINA-W10 module Library

THIS PROGERAM SETUP WIFI BY USING 
- Load pre-stored Credentials (SSID/Password) stored on module (Cyphered)
- setup multiple attemps to setup your wifi connection
- if fails, scan exsisting networks, open an Access Point to ask for your network preferecne and your credentials
- store new Credentials to Module-Flash (Cyphered)

No need to keep your login details in the code

(C) jAY fOX 2020 / 
*************************************************************/
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <EasyWiFi.h>

/*********** Global Settings  **********/
EasyWiFi MyEasyWiFi;
char MyAPName[]= {"_*TestAP*_"};

//
// Setup / initialisation 
//
void setup()
{ 
/*********** Serial SETUP  **********/
int t=10;  //Initialize serial and wait for port to open, max 10 second waiting
Serial.begin(115200);
while (!Serial) {
    delay(1000);
    if ( (t--)== 0 ) break; // no serial, but continue program
    }
  
/*********** Check WifiShield  **********/
if (WiFi.status() == WL_NO_SHIELD) {   // check for the presence of the shield:
    Serial.println("WiFi shield not present");
    while (true);     // don't continue if no shield
    }
MyEasyWiFi.apname(MyAPName);
MyEasyWiFi.seed(0); 
} // endSetup



//
// Main SUPER Loop
//
void loop()
{
  if (WiFi.status()==WL_CONNECTED)
  {
    printWiFiStatus();
    delay(5000);
  }
  else
  {
    Serial.println("* Not Connected, starting EasyWiFi");
    MyEasyWiFi.start();     // Start Wifi login 
  }

} // end Main loop



// SERIALPRINT Wifi Status 
void printWiFiStatus() {

    // print the SSID of the network you're attached to:
    Serial.print("\nStatus: SSID: "); Serial.print(WiFi.SSID());
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP(); Serial.print(" - IPAddress: "); Serial.print(ip);
    // print the received signal strength:
    long rssi = WiFi.RSSI(); Serial.print("- Rssi: "); Serial.print(rssi); Serial.println("dBm");

}
