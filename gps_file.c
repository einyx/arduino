#include <SD.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial shield(2,3); // configure software serial port 
 
// Create an instance of the TinyGPS object
TinyGPS gps;
 
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
 
void getgps(TinyGPS &gps)
{
  float latitude, longitude;
  int year;
  byte month, day, hour, minute, second, hundredths;
 
  //decode and display position data
  gps.f_get_position(&latitude, &longitude); 
  File dataFile = SD.open("DATA.TXT", FILE_WRITE);
  // if the file is ready, write to it
  if (dataFile) 
  {
    dataFile.print("Lat: "); 
    dataFile.print(latitude,5); 
    dataFile.print(" ");
    dataFile.print("Long: "); 
    dataFile.print(longitude,5);
    dataFile.print(" ");  
    // decode and display time data
    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
    // correct for your time zone as in Project #45
    hour=hour+11; 
    if (hour>23)
    {
      hour=hour-24;
    }
   if (hour<10)
    {
      dataFile.print("0");
    }  
    dataFile.print(hour, DEC);
    dataFile.print(":");
    if (minute<10) 
    {
      dataFile.print("0");
    }
    dataFile.print(minute, DEC);
    dataFile.print(":");
    if (second<10)
    {
      dataFile.print("0");
    }
    dataFile.print(second, DEC);
    dataFile.print(" ");
    dataFile.print(gps.f_speed_kmph());
    dataFile.println("km/h");     
    dataFile.close(); // this is mandatory   
    delay(10000); // record a measurement about every 10 seconds
  }
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
