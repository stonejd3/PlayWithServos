#include <Servo.h>
 
/** 
  Pre-processor directives 
  (not stored in Arduino memory)
**/

#define J1 8
#define J2 9
#define J1H 1500
#define J2H 1611

/** 
  Other program variables
  (stored in Arduino memory)
**/

Servo Servo1, Servo2;

int angle1 = J1H, angle2 = J2H;
int boundLow, boundHigh, boundF;

uint8_t angle1ValuesIndex = 0, angle2ValuesIndex = 0;

int angle1Values[10] = {
  J1H,J1H,J1H,J1H,
  J1H,J1H,J1H,J1H,
  J1H,J1H
};

int angle2Values[10] = {
  J2H,J2H,J2H,J2H,
  J2H,J2H,J2H,J2H,
  J2H,J2H
};

const char delimiter  = ',';
const char finald     = '.';
 
char incomingByte;
String readBuffer     = "";

int byteDelay   = 5; 
int setupDelay  = 500;
 
int average(int inputArray[10]){

  int sum = 0;
  
  for(uint8_t i = 0; i < 10; i++)
    sum += inputArray[i];
  
  return sum / 10;

}
  
void setup() {

  Serial.begin(115200);
 
  Servo1.attach(J1);
  Servo2.attach(J2);

  servoWriter(J1H, J2H);
  
  delay(setupDelay);

}
 
void loop() {

  servoWriter(average(angle1Values), average(angle2Values));
 
  readBuffer = "";
  boolean start = false;

  while (Serial.available()) {

    incomingByte = Serial.read();
    delay(byteDelay);
    
    if (start == true) {
      
      if (incomingByte != 'e') {
        readBuffer += char(incomingByte);
      } else {
        start = false;
      }
    } else if (incomingByte == 's'){
      start = true;
    }
    
  }
 
  String message = readBuffer;
  
   
  if(message != ""){
    
    boundLow = message.indexOf(delimiter);
    angle1 = message.substring(0, boundLow).toInt();
    
    angle1ValuesIndex += 1;
    angle1ValuesIndex %= 10;
    
    angle1Values[angle1ValuesIndex] = angle1;
    
    boundHigh = message.indexOf(delimiter, boundLow+1); 
    angle2 = message.substring(boundLow+1, boundHigh).toInt();

    angle2ValuesIndex += 1;
    angle2ValuesIndex %= 10;
    
    angle2Values[angle2ValuesIndex] = angle2;
   
  }
  
  servoWriter(average(angle1Values), average(angle2Values));
  
}

void servoWriter(int input1, int input2){
  
  Servo1.writeMicroseconds(input1);
  Servo2.writeMicroseconds(input2);

}
