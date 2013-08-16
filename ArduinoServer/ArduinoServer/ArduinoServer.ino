/*
 Chat  Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 
 Circuit:
 * WiFi shield attached
 
 created 18 Dec 2009
 by David A. Mellis
 modified 31 May 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <WiFi.h>

IPAddress ip(192, 168, 1, 177);  
char ssid[] = "SHS-AW"; //  your network SSID (name) 
char pass[] = "0F4194EBD7B8844D";    // your network password (use for WPA, or use as key for WEP)


int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;

WiFiServer server(23);

boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  //Initialize serial and wait for port to open:
  pinMode(A0, OUTPUT);  
  pinMode(A1, OUTPUT);  
  pinMode(A2, OUTPUT);  
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.config(ip);
    status = WiFi.begin(ssid, pass);
   // wait 10 seconds for connection:
    delay(5000);
  } 
  // start the server:
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
 }


void loop() {
  // wait for a new client:
  WiFiClient client = server.available();


  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
      Serial.println("Connected with client");
      client.println("Hello, client!"); 
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
     
      switch (thisChar){
      
        case '1':
          TurnOnLED(A0); 
          Serial.println("LED 1");
          break;       
       
       case '2':
          TurnOnLED(A1);
          Serial.println("LED 2");        
          break;          

       case '3':
          TurnOnLED(A2);        
          Serial.println("LED 3");
          break;        
      
      }     
      Serial.write(thisChar);
    }
  }
}

void TurnOnLED(int sLed){
  digitalWrite(sLed, HIGH);
  delay(1000);
  digitalWrite(sLed, LOW);

}



void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


