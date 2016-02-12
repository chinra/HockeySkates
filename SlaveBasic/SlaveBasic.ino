//This Code is for the Slave Arduino Uno
//Written by Rachel Chin and Chris Canal

//Include libraries for SD Card
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

//Set up datastring for top row of the csv file
//These are the labels for the first row
String labelString = "Microseconds, Bridge1 in Millivolts, Bridge2 in Millivolts, Bridge3 in Millivolts, Bridge4 in Millivolts, Bridge5 in Millivolts, Bridge6 in Millivolts";

//This is the variable for the name of the file on the SD Card
//This variable name will be changed
String filename = "YourCodeIsMessedUp.txt";

int i = 0;
int dataLength = 0;
char* dataString = "qwertyuiopasdfghjklzxcvbnm123";
String SDcardData = "";

//Initialize the Switch Variable on Pin 8
int readDataSwitchPin = 9;
int readDataSwitch = 0;

//SPI Settings for SD Card
int CS_pin = 10;

void setup()
{
 Wire.begin(4);                // join i2c bus with address #4
 Wire.onReceive(receiveEvent); // register event
 Serial.begin(9600);           // start serial for output
 
 Serial.println("slave setup");

 //Initialize the sd Card
    Serial.println ("Initializing Card");
    //CS Pin is an output
    pinMode (CS_pin, OUTPUT);
    
    // Check if card is ready
    if(!SD.begin(CS_pin))
    {
        Serial.println("Card Failed");
        return;
    }
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if(dataFile)
  {
    dataFile.println(labelString);
    dataFile.close ();
    Serial.println(labelString);
  }
  else
  {
    Serial.println("Couldn't access file");
  }
    Serial.println(SDcardData);


 
}

void loop()
{
  
     Wire.onReceive(receiveEvent); // register event
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
   i = 0;
 while(0 < Wire.available()) // loop through all but the last
 {
   char c = Wire.read(); // receive byte as a character
   dataString[i] = c;
 
   i++;
    }
    SDcardData = String(micros())+", "+dataString;
      // Open a file to write to
  // Only one file can be open at a time 
  readDataSwitch = digitalRead(readDataSwitchPin);
  Serial.println(readDataSwitch);
   if(readDataSwitch){
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if(dataFile)
  {
    dataFile.println(SDcardData);
    dataFile.close ();
    Serial.println(SDcardData);
  }
  else
  {
    Serial.println("Couldn't access file");
  }
    Serial.println(SDcardData);
   }
}

