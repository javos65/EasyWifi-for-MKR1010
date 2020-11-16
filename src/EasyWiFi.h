 /*
 * EasyWiFi
 * Created by John V. - 2020 V 1.1.0
 * 
 * 
 * 
 * 
 * Released into the public domain on github: https://github.com/javos65/EasyWifi-for-MKR1010
 */
#ifndef EASYWIFI_H
#define EASYWIFI_H

#include "Arduino.h"
#include <WiFiNINA.h>
#include <WiFiUdp.h>

// Define AP Wifi-Client parameters
#define MAXSSID 10                         // MAX number of SSID's listed after search
#define SSIDBUFFERSIZE 32                  // SSID name BUFFER size
#define APCHANNEL  5                       // AP wifi channel
#define SECRET_SSID "UnKnownWireless"		   // Backup SSID - not required
#define SECRET_PASS "NoPassword"	         // Backup Pass - not required
#define CREDENTIALFILE "/fs/credfile"
#define APNAME "EasyWiFi_AP"

// Define UDP settings for DNS 
#define UDP_PACKET_SIZE 1024          // UDP packet size time out, preventign too large packet reads
#define DNSHEADER_SIZE 12             // DNS Header
#define DNSANSWER_SIZE 16             // DNS Answer = standard set with Packet Compression
#define DNSMAXREQUESTS 32             // trigger first DNS requests, to redirect to own web-page
#define UDPPORT  53                   // local port to listen for UDP packets

//void WiFi_Handler(void);      // ISR HANDLER FOR WiFi
//extern int WDTZeroCounter;      // SOFT COUNTER FOR EXTENDING WDT TIME VIA EW INTERRUPT

class EasyWiFi
{
  public:
    EasyWiFi();
    void start();
    byte erase();
    byte apname(char * name);  
    void seed(int value);

    
  private:                      
  void SimpleDecypher(char * textin, char * textout);
  void SimpleCypher(char * textin, char * textout);
  byte Check_Credentials();
  byte Erase_Credentials();
  byte Write_Credentials(char * buf1,int size1,char * buf2,int size2);
  byte Read_Credentials(char * buf1,char * buf2);
  void APWiFiClientCheck();
  void APDNSScan();
  void listNetworks();
  void APSetup();
  void printWiFiStatus();
  
};

#endif
