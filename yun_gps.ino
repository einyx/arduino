// Updated for Arduino YUN using Serial over Wireless
// Modifed by einyx

// Echoes the code from the serial to the monitor serial port


#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// YUN: Include these libraries to allow wireless serial
#include <Bridge.h>
#include <Console.h>

SoftwareSerial mySerial(2,3); // configure software serial port 

// If using hardware serial, comment
// out the above two lines and enable these two lines instead:
//HardwareSerial mySerial = Serial1;


TinyGPSPlus gps;

void setup() {
  Bridge.begin();
  Console.begin();
  while(!Console);

  mySerial.begin(9600);
  Console.println("Ready!");
 }


void loop() {

  byte a;
  a = mySerial.read();
  getgps(gps); 

  Console.write(a);
  
}


void getgps(TinyGPSPlus &gps)
{
  float latitude, longitude;
  int year;
  byte month, day, hour, minute, second, hundredths;
 
  //decode and display position data
  File dataFile = SD.open("DATA.TXT", FILE_WRITE);
  // if the file is ready, write to it
  //if (dataFile) 
  //{

  //}
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (mySerial.available())
      gps.encode(mySerial.read());
  } while (millis() - start < ms);
}
