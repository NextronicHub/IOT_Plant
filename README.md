# IOT_Plant

/*****************************************************************
IOT_Plant.ino
Post data to data.nextronic's  stream server, using
an ESP8266.
Ahmed Kousta @ Nextronic
Date:  29/08/2014

This sketch uses an ESP8266 to POST sensor readings to 
nextronic's data logging streams (data.nextronic.ma). 
A post will be sent every 3 seconds.

Before uploading this sketch, there are a number of global vars
that need adjusting:
  1. WIFI Setting: Fill in your wifi network ssid and password 
  2. data stream inputs: Fill in your data stream's public, private, and 
     data FIELDS names before uploading!

Hardware Hookup:
  * These components are connected to the ESP8266's I/O pins:
    * D1 - DHT22 sensor for moisture and temperature
    * A0 - soil moisture sensor.

Development environment specifics:
    IDE: Arduino 1.6.9
    Hardware Platform: ESP8266


