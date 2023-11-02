#include <IRremote.h>

int led1 = 5;
int led2 = 6;
int led3 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  IrReceiver.begin(12);
  
}

void loop() {
  if(IrReceiver.decode()){
      IrReceiver.resume();
     
     Serial.println(IrReceiver.decodedIRData.command);
     long int info = IrReceiver.decodedIRData.command;
      if(info == 12){
        digitalWrite(led1, HIGH);  
      }
      if(info == 24){
        digitalWrite(led1, LOW);
      }
      
    
  }
  //delay(100);
}
/* 
  tasta 1 = aprindem ledul 1 12
  tasta 2 = stingem ledul 1 24
  tasta 3 = aprindem ledul 2 94
  tasta 4 = stingem ledul 2 8
  tasta 5 = aprindem ledul 3 28
  tasta 6 = stingem ledul 3 90

 *  
 */
