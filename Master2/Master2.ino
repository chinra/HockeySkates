
#include <Wire.h>

char* dataString = "                                ";
char* dataStringEdited = "                                ";
String data = "                                ";
int bridge1reading = 0;
int bridge2reading = 0;
int bridge3reading = 0;
int bridge4reading = 0;
int bridge5reading = 0;
int bridge6reading = 0;
int bridge1mV = 0;
int bridge2mV = 0;
int bridge3mV = 0;
int bridge4mV = 0;
int bridge5mV = 0;
int bridge6mV = 0;

int i = 0; 
int dataLength = 0;

void setup()
{
 Serial.begin(9600); 
 Wire.begin(); // join i2c bus (address optional for master)
 Serial.println("master setup");
}

byte x = 0;

void loop()
{
  //bridge readings from analog inputs
bridge1reading = analogRead(A0);
bridge2reading = analogRead(A1);
bridge3reading = analogRead(A2);
bridge4reading = analogRead(A3);
bridge5reading = analogRead(A4);
bridge6reading = analogRead(A5);

//convert bridgereading to bridgemV
bridge1mV = bridge1reading * 5;
bridge2mV = bridge2reading * 5;
bridge3mV = bridge3reading * 5;
bridge4mV = bridge4reading * 5;
bridge5mV = bridge5reading * 5;
bridge6mV = bridge6reading * 5;

//datastring time and mV values
data = String(bridge1mV) + "," + String(bridge2mV) + "," + String(bridge3mV)  + "," + String(bridge4mV)  + "," + String(bridge5mV)  + "," + String(bridge6mV);
i = 0; 
dataLength = data.length();
while(i < dataLength ){
 dataString[i] = data[i];
 i++; 
}

 Wire.beginTransmission(4); // transmit to device #4
 Wire.write(dataStringEdited);              // sends one byte  
 Wire.endTransmission();    // stop transmitting
 Serial.println(dataStringEdited);

}
