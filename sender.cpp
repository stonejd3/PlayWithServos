#include <SoftwareSerial.h>

/** 
  Pre-processor directives 
  (not stored in Arduino memory)
**/

#define potPin1 A6
#define potPin2 A1
#define setupDelay 500

/** 
  Other program variables
  (stored in Arduino memory)
**/

int angle1,     potVal1;
int angle2,     potVal2;
int boundLow,   boundHigh;

unsigned long   lastTimestamp;
unsigned long   timeDelay   =   100;

String input;
const char delimiter = ',';
const char finald = '.';

SoftwareSerial HC12(9,8);

void setup() {
   
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);

  HC12.begin(115200);
  Serial.begin(115200);
  delay(setupDelay);
  
  lastTimestamp = millis();

}

void updatePotReadings(){
  
  potVal1 = analogRead(potPin1);
  potVal2 = analogRead(potPin2);

}

String buildMessagePayload(int angles[2]){
  
  String message = "s";
  
  for(uint8_t i=0; i < 2; i++){
    
    message += String(angles[i]);
  
    if(i == (2-1))
      break;

    message += String(delimiter);
  
  }
  
  message += finald;
  message += "e";
  
  return message;

}

void runProcedure(){
  
  updatePotReadings();
  
  int angles[2];
  
  angles[0] = map(potVal1, 0, 1023, 1000, 2000); 
  angles[1] = map(potVal2, 0, 1023, 1000, 2000);
   
  String message = buildMessagePayload(angles);

  Serial.println(message);
  HC12.println(message);
  
  lastTimestamp = millis();
  
}
 
void loop() {
  
  unsigned long currentTime = millis();
  
  if(currentTime < (lastTimestamp + timeDelay))
    return;
  
  runProcedure();

}
