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
  while (!Serial); // wait for leo to be ready

  mySerial.begin(9600);
  Console.println("Get version!");
  mySerial.println("test");

  if (!SD.begin(10)) {
    Console.println("Card failed, or not present");
    // stop the sketch
    return;
  }
  Console.println("SD card is ready");

 }


void loop() {
  if (Console.available()) {
   char c = Console.read();
   Console.write(c);
   mySerial.write(c);
  }
  if (mySerial.available()) {
    char c = mySerial.read();
    Console.write(c);
  }
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
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printInt(gps.hdop.value(), gps.hdop.isValid(), 5);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.value()) : "*** ", 6);
  //}
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

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}

 
