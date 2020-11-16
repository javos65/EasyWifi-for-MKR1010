/*
  This example shows how to interact with NiNa internal memory partition
  APIs are modeled on SerialFlash library (not on SD) to speedup operations and avoid buffers.

  Read / Write / Erase an SSID and a Password to flash file

  2020 - jAy fOx
*/

#include <WiFiNINA.h>
#define CREDENTIALFILE "/fs/credfile"
#define DEBUG_X 1                         // Debug mode for serial momitor, leave it and no Seriall is spammed
#define SEED 4

char G_Ssid[32] = "ExampleSSID";
char G_Pass[32] = "ThisisNOTaPassword";
char G_code1[32]="xxxx",G_code2[32]="yyyy";
    
void setup() {

Serial.begin(115200); while (!Serial);
  // check for the presence of the shield:
if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NINA WiFi shield not present");
// don't continue:
    while (true);
  }

/*Test Cypher 
SimpleCypher(G_Ssid,G_code1);
Serial.print("SSid:[");Serial.print(G_Ssid);Serial.print("] cypher to [");Serial.print(G_code1);Serial.print("]\n" ); 
SimpleCypher(G_Pass,G_code2);
Serial.print("SSid:[");Serial.print(G_Pass);Serial.print("] cypher to [");Serial.print(G_code2);Serial.print("]\n" ); 
SimpleDecypher(G_code1, G_Ssid);
Serial.print("SSid:[");Serial.print(G_Ssid);Serial.print("] cypher from [");Serial.print(G_code1);Serial.print("]\n" ); 
SimpleDecypher(G_code2,G_Pass);
Serial.print("SSid:[");Serial.print(G_Pass);Serial.print("] cypher from [");Serial.print(G_code2);Serial.print("]\n" ); 
Serial.print("\n" ); 
*/

/*Test Flash*/ 
Read_Credentials(G_code1,G_code2);
Serial.print("SSid:[");Serial.print(G_code1);Serial.print("] Pass:[");Serial.print(G_code2);Serial.print("]\n" ); 

Serial.print("To Save to Flash : SSid:[");Serial.print(G_Ssid);Serial.print("] Pass:[");Serial.print(G_Pass);Serial.print("]\n" ); 
Write_Credentials(G_Ssid,sizeof(G_Ssid),G_Pass,sizeof(G_Pass) );
Read_Credentials(G_code1,G_code2);
Serial.print("Read Back Flash : SSid:[");Serial.print(G_code1);Serial.print("] Pass:[");Serial.print(G_code2);Serial.print("]\n" ); 
Erase_Credentials();
}

void loop() {
  // put your main code here, to run repeatedly:
}



/* Read credentials ID,pass to Flash file , Comma separated style*/
byte Read_Credentials(char * buf1,char * buf2)
{
  int u,t,c=0;
  char buf[68],comma=1, zero=0;
  char bufc[68];
  WiFiStorageFile file = WiFiStorage.open(CREDENTIALFILE);
  if (file) {
    file.seek(0);
    if (file.available()) {  // read file buffer into memory, max size is 64 bytes for 2 char-strings
      c= file.read(buf, 68);  //Serial.write(buf, c);
    }
    if (c!=0)
    {
      t=0;u=0;
      while(buf[t] != comma) {  // read ID till comma
        bufc[u++]=buf[t++];
        if (u>31) break;
        }
        bufc[u]=0;
        SimpleDecypher(bufc,buf1);
        u=0;t++;                // move to second part: pass
      while(buf[t] != zero) {   // read till zero
        bufc[u++]=buf[t++];
        if (u>31)  break;
        }
        bufc[u]=0;
        SimpleDecypher(bufc,buf2);
    }
#if DEBUG_X
   Serial.print("* Read Credentials : ");Serial.println(c);
#endif    
   file.close(); return(c);
 }
 else {
#if DEBUG_X
   Serial.println("* Cant read Credentials :");
#endif    
  file.close();return(0);
 }

}

/* Write credentials ID,pass to Flash file , Comma separated style*/
byte Write_Credentials(char * buf1,int size1,char * buf2,int size2)
{
  int c=0;
  char comma=1, zero=0;
  char buf[32];
  WiFiStorageFile file = WiFiStorage.open(CREDENTIALFILE);
  if (file) {
    file.erase();     // erase content bnefore writing
  }  
    SimpleCypher(buf1,buf);
    c=c+file.write(buf, size1);
    file.write(&comma, 1); c++;
    SimpleCypher(buf2,buf);
   c=c+file.write(buf, size2);
   file.write(&zero, 1); c++;
   if(c!=0) {
#if DEBUG_X
 Serial.print("* Written Credentials : ");Serial.println(c);
#endif
   file.close(); return(c);
 }
 else {
#if DEBUG_X
   Serial.println("* Cant write Credentials");
#endif  
  file.close(); return(0);
 }

}

/* Erase credentials in flkash file */
byte Erase_Credentials()
{
char empty[16]="0empty0o0empty0";  
  WiFiStorageFile file = WiFiStorage.open(CREDENTIALFILE);
  if (file) {
  file.seek(0);
  file.write(empty,16); //overwrite flash
  file.erase();
#if DEBUG_X
 Serial.println("* Erased Credentialsfile : ");
#endif  
  file.close(); return(1);
 }
 else {
  #if DEBUG_X
 Serial.println("* Could not erased Credentialsfile : ");
#endif  
  file.close(); return(0);
 }
}

/* Check credentials file */
byte Check_Credentials()
{
  WiFiStorageFile file = WiFiStorage.open(CREDENTIALFILE);
  if (file) {
#if DEBUG_X
 Serial.println("* Found Credentialsfile : ");
#endif  
  file.close(); return(1);
 }
 else {
  #if DEBUG_X
 Serial.println("* Could not find Credentialsfile : ");
#endif  
  file.close(); return(0);
 }
}



/* Simple Cyphering the text code */
void SimpleCypher(char * textin, char * textout)
{
int c,t=0;
while(textin[t]!=0) {
   textout[t]=textin[t]+SEED%17-t%7;
   t++;
  }
  textout[t]=0;
#if DEBUG_X
// Serial.print("* Cyphered ");Serial.print(t);Serial.print(" - ");Serial.println(textout);
#endif
}

/* Simple DeCyphering the text code */
void SimpleDecypher(char * textin, char * textout)
{
int c,t=0;
while(textin[t]!=0) {
   textout[t]=textin[t]-SEED%17+t%7;
   t++;
  }
  textout[t]=0;
#if DEBUG_X
// Serial.print("* Decyphered ");Serial.print(t);Serial.print(" - ");Serial.println(textout);
#endif
}
