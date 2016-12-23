#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial shield(2,3); // configure software serial port 
 
// Create an instance of the TinyGPS object
TinyGPSPlus gps;
 
void setup()
{
  pinMode(10, OUTPUT);
  shield.begin(9600);
  Serial.begin(9600);
  // check that the microSD card exists and can be used v
  if (!SD.begin(10)) {
    Serial.println("Card failed, or not present");
    // stop the sketch
    return;
  }
  Serial.println("SD card is ready");
}
 
void getgps(TinyGPSPlus &gps)
{

  File dataFile = SD.open("data.txt", FILE_WRITE);
  // if the file is ready, write to it
    Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
    Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
    dataFile.print("Lat: "); 
    dataFile.print(gps.location.lat(), 6); 
    dataFile.print(" ");
    dataFile.print("Long: "); 
    dataFile.print(gps.location.lng(), 6); 
    dataFile.print(" ");  
    dataFile.print(gps.time.value());
    Serial.println(gps.time.value());
}
 
void loop() 
{
  byte a;
  if ( shield.available() > 0 )  // if there is data coming into the serial line
  {
    a = shield.read();          // get the byte of data
    if(gps.encode(a))           // if there is valid GPS data...
    {
      getgps(gps);              // grab the data and display it on the LCD
    }
  }
}
