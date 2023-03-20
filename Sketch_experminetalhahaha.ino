/* TMP36 analog temperature sensor with Arduino example code. More info: https://www.makerguides.com */

// Define to which pin of the Arduino the output of the TMP36 is connected:
#define sensorPin A0
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

File myFile;
RTC_DS3231 rtc;

char t[32];
char d[32];
void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

  //SD printing
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt......");
    /*myFile.println("testing 1, 2, 3.");*/
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // Get a reading from the temperature sensor:
  int reading = analogRead(sensorPin);

  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);

  // Convert the voltage into the temperature in Celsius:
  float temperature = (voltage - 500) / 10;
  
  // Print the temperature IN CELCIUS in the Serial Monitor:
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");

  // Print the temperature IN FARENHEIT in the Serial Monitor:
  double temperatureF = (temperature * 1.8) + 32;
  Serial.print(temperatureF);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("F");

  Serial.println("------------------------------------");

  DateTime now = rtc.now();
  sprintf(t, "%02d:%02d:%02d", now.hour(), now.minute(), now.second() );  
  sprintf(d, "%02d/%02d/%02d", now.day(), now.month(), now.year());

  Serial.print(F("Date/Time: "));
  Serial.print(d);
  Serial.print(", ");
  Serial.print(t);


  //
  //copied from setup code and altered to fit in date time temp
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    /*Serial.println("Writing to test.txt...");
    myFile.println("Date/Time: ");
    myFile.println(t);
    myFile.println("Temp in C and F");
    myFile.print(temperature);
   myFile.print(" \xC2\xB0"); // shows degree symbol
   myFile.println("C");
   myFile.print(temperatureF);
   myFile.print(" \xC2\xB0"); // shows degree symbol
   myFile.println("F");
   myFile.println("------------------------------------------------");*/
    
    myFile.print(t);
    myFile.print(",");
    myFile.print(temperature);
    myFile.print(",");
    myFile.println(temperatureF);
    
    // close the file:
    myFile.close();
    Serial.println(" ");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }



  // re-open the file for reading:
  /*
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  } */
  //



  delay(1000); // wait a second between readings



  //in this loop, tell it to print the temp values to the SD card & file
}