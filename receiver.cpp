#include <Servo.h>
 
Servo Servo1;
Servo Servo2;
 
int J1 = 8;
int J2 = 9;

int J1H = 90;
int J2H = 110;
 
int angle1 = J1H;
int angle2 = J2H;
 
int angle1L = J1H;
int angle2L = J2H;

int boundLow;
int boundHigh;
int boundF;
const char delimiter = ',';
const char finald = '.';
 
char incomingByte;
String readBuffer = "";
int byteD = 5; 
int SMd = 250;
int stupD = 500;
 
void setup() {

  Serial.begin(9600);
 
  Servo1.attach(J1);
  Servo2.attach(J2);

  servoWriter(J1H, J2H);
  
  delay(stupD);

}
 
void loop() {

  servoWriter(angle1L, angle2L);
 
  readBuffer = "";
  boolean start = false;

  while (Serial.available()) {

    incomingByte = Serial.read();
    delay(byteD);
    
    if (start == true) {
      
      if (incomingByte != 'e') {
        readBuffer += char(incomingByte);
      } else {
        start = false;
      }
    } else if (incomingByte == 's'){
      start = true; //If true start reading the message
    }
    
  }
 
  String message = readBuffer; //Saves readBuffer contents to new String
  
   
  if(message == ""){
    
    angle1 = angle1L;
    angle2 = angle2L;
    servoWriter(angle1, angle2);
     
  } else {
    
    boundLow = message.indexOf(delimiter); //Locates index of first delimiter i.e. comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/indexof/
    angle1 = message.substring(0, boundLow).toInt(); //.substring creates a sub string of input string starting at index position zero up to but not including first comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/substring/
           
    boundHigh = message.indexOf(delimiter, boundLow+1); //This instance is going to search for the next delimiter i.e. comma starting at boundLow+1 i.e. one character after the previous comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/indexof/
    angle2 = message.substring(boundLow+1, boundHigh).toInt(); //Creates a substring of input starting one character after the first comma ending one character before the second comma
   
    servoWriter(angle1, angle2);
     
  }   
 
  //delay(SMd);
 
  angle1L = angle1;
  angle2L = angle2;
  
}

void servoWriter(int input1, int input2){
  
  Servo1.write(input1); //Moves Specified Servo to Specified Angle
  Servo2.write(input2); //Moves Specified Servo to Specified Angle

}