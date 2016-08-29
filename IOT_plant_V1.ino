/*****************************************************************

IOT_Plant.ino Post data to data.nextronic's stream server, using an ESP8266. Ahmed Kousta @ Nextronic Date: 29/08/2014

This sketch uses an ESP8266 to POST sensor readings to nextronic's data logging streams (data.nextronic.ma). A post will be sent every 3 seconds.

Before uploading this sketch, there are a number of global vars that need adjusting:

WIFI Setting: Fill in your wifi network ssid and password
data stream inputs: Fill in your data stream's public, private, and data FIELDS names before uploading!
Hardware Hookup:

These components are connected to the ESP8266's I/O pins:
D1 - DHT22 sensor for moisture and temperature
A0 - soil moisture sensor.
Development environment specifics: IDE: Arduino 1.6.9 Hardware Platform: ESP8266

**********************************************************************/



#include <ESP8266WiFi.h>

/////////////////////
// DHT Definitions //
/////////////////////
#include "DHT.h"
#define DHTPIN D1     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);


//////////////////////
// WiFi Definitions //
//////////////////////
const char* ssid     = "ssid";
const char* password = "password";


////////////////////////////
// data.nextronic.ma Keys //
////////////////////////////
const String publicKey = "qLaEer6mqLhlB2M0pl1PU0qXNgj";
const String privateKey = "n8ZdLYaPp8H7GYKWj7qMh06Qbrv";
char server[] = "nextdata.northeurope.cloudapp.azure.com"; 
const byte NUM_FIELDS = 3;
const String fieldNames[NUM_FIELDS] = {"humidity", "soilmoisture", "temperature"};
String fieldData[NUM_FIELDS];





void setup() {
  
  Serial.begin(9600);



  dht.begin();


    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
   // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
    WiFi.begin(ssid, password);
    // Use the WiFi.status() function to check if the ESP8266
    // is connected to a WiFi network.
    while (WiFi.status() != WL_CONNECTED) 
    {
        // Delays allow the ESP8266 to perform critical tasks
        // defined outside of the sketch. These tasks include
        // setting up, and maintaining, a WiFi connection.
         delay(500);
         Serial.print(".");
     }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}




void loop() {
  
  // Read Humidity 
  float h = dht.readHumidity();
  // Read temperature 
  float t = dht.readTemperature();
  //read soil moisture sensor
  int s = analogRead(A0);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 

  
    fieldData[0] = String(h);
    fieldData[1] = String(s);
    fieldData[2] = String(t);

    //send data to data.nextronic.ma
    postData();
    
    delay(1000);
    delay(1000);
    delay(1000);
}



WiFiClient client;

void postData()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
 if (client.connect(server, 80)) {

    
    // Make a HTTP request:
    Serial.println("connected");
    client.print("GET /input/");
    client.print(publicKey);
    client.print("?private_key=");
    client.print(privateKey);
    for (int i=0; i<NUM_FIELDS; i++)
    {
      client.print("&");
      client.print(fieldNames[i]);
      client.print("=");
      client.print(fieldData[i]);
    }
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    

    
  } else {

    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    
  }
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
   
  }
    client.stop();
    
}
