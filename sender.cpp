#include <SoftwareSerial.h>
 
SoftwareSerial HC12(8,7);
 
int PotPin1 = A2;
int PotPin2 = A3;
 
int PotVal1;
int PotVal2;

int angle1;
int angle2;

String input;

int boundLow;
int boundHigh;

const char delimiter = ',';
const char finald = '.';
 
int stupD = 500; //Setup Delay
 
void setup() {
  
  Serial.begin(9600);
 
  pinMode(PotPin1, INPUT);
  pinMode(PotPin2, INPUT);

   HC12.begin(9600);
   delay(stupD);

}
 
void loop() {
 
  PotVal1 = analogRead(PotPin1); 
  PotVal2 = analogRead(PotPin2); 
  
  angle1 = map(PotVal1, 0, 1023, 0, 180); 
  angle2 = map(PotVal2, 0, 1023, 0, 180);
   
  String angle1S = String(angle1);
  String angle2S = String(angle2);
  
  String message = "s" + angle1S + delimiter + angle2S + finald + "e";
 
  HC12.println(message);
  
  delay(100);

}
