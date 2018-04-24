/*
  SD card basic file example

 This example shows how to create and destroy an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
//pinMode(53, OUTPUT);

  Serial.print("Initializing SD card...");
//
// ** MOSI - pin 11
// ** MISO - pin 12
// ** CLK - pin 13
// ** CS - pin 10
pinMode(10, OUTPUT);
  // boolean begin(uint8_t csPin = SD_CHIP_SELECT_PIN, int8_t mosi = -1, int8_t miso = -1, int8_t sck = -1);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

 if (SD.exists("CONFIG.TXT")) {
    Serial.println("CONFIG.TXT exists.");
  } else {
    Serial.println("CONFIG.TXT doesn't exist.");
  }


  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example1.txt", FILE_WRITE);
  if ( myFile ) {
  myFile.println("testing 1. ---------------");
  myFile.println("testing 2, 3.");
  } else {
     Serial.println("Failed to Creating example.txt...");
  }
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

   myFile = SD.open("example.txt");
   if (myFile) {
      Serial.println("reading example.txt:");
 
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
         Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
   } else {
      // if the file didn't open, print an error:
      Serial.println("error opening example.txt");
   }



  // delete the file:
//  Serial.println("Removing example.txt...");
//  SD.remove("example.txt");
//
//  if (SD.exists("example.txt")) {
//    Serial.println("example.txt exists.");
//  } else {
//    Serial.println("example.txt doesn't exist.");
//  }
}

void loop() {
  // nothing happens after setup finishes.
}



