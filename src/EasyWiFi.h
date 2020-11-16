/*
 * WDTZero.h - Library for watchdog on the SamD Zero series
 * Created by John V. - 2019 V 1.3.0
 * 
 * See ATSAMD2x datasheet, #18, page205 onwards
 * Defines Watchdog Class to Setup Watchdog timer in Normal mode with EarlyWarning interrupt.
 *  1. Sets Hardware WDT timer
 *     -> for stalled processor situations, generates a reset 
 *     -> 62ms upto 16s response
 *  2. Sets Software WDT using EarlyWarning timer (EWT) and software counter (Global Variable)
 *     -> for stalled software, generates a reset if software loop does not clear WDT on time
 *     -> Total soft-WDT intervals are 8,16,32 Seconds , 1,2,4,8,16 Minutes
 * 
 * V1.3.0 - added shutdown function for soft-watchdog : now possible to do an extra job before shutting down like saving your key data *thnks to Juraj
 * 
 * Released into the public domain.
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
