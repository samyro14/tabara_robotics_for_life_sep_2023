#include <IRremote.hpp>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <dht.h> // librarie pentru temperatura si umiditate
#include <IRremote.h>
//variables and objects
Servo motor; // servomotor 
int primit = 48; // ce cod primim de la telefon
bool deschis = 0; // inchis
int pos = 180, raining = A2;
int temp = 7;
int relay4 = 4;
int mic = 12;
dht tempmodule;
bool verificare_ploua = false;
//functions
void ploua();
void sound();
void temperature();
///pentru deschis == 1 - atunci geamul este deschis, altfel este inchis
void setup() {
  pinMode(raining, INPUT);
  pinMode(mic, INPUT);
  Serial.begin(9600);
  motor.attach(8); // va fi atasat de pinul 8
  motor.write(180);
  //IrReceiver.begin(12); 
}

void loop() {

  /*if(IrReceiver.decode()){
      IrReceiver.resume();
     
     Serial.println(IrReceiver.decodedIRData.command);
     long int info = IrReceiver.decodedIRData.command;
     Serial.println(info);
      if(info == 12){
        deschis = 1;
         if(pos >= 90){
       motor.write(pos), pos--;
      // delay(15);
     }
      }
      if(info == 24){
         if(pos <= 180){
         motor.write(pos), pos++;
          delay(15);
        }  
       if(!pos) deschis = 0; // asta inseamna ca geamul este inchis
      }
      
    
  }*/
  
  if(Serial.available()){
      primit = Serial.read();
   }
   if(primit == 49){ // trebuie sa deschid fereastra
    deschis = 1;
    if(pos >= 90){
       motor.write(pos), pos--;
      // delay(15);
     }
   }
    if(primit == 52){ //trebuie sa inchid
      if(pos <= 180){
         motor.write(pos), pos++;
          delay(15);
        }  
       if(!pos) deschis = 0; // asta inseamna ca geamul este inchis
    }
  
  ploua(); //in cazul in care ploua trebuie sa inchid geamul
  delay(15);
  /*if(!verificare_ploua)
  temperature(); // verific temperatura
  delay(15);
  sound(); // masor numarul de decibeli pentru a inchide geamul*/
 // delay(10); 
}
void closeWindow(){ //functie pentru a inchide geamul
    if(deschis){ // daca fereastra este deschisa
      while(pos <= 180){
        motor.write(pos);
        pos ++;
        delay(15);
      }
      deschis = 0; // geamul este inchis
      
    }
  
}
void openWindow(){ //functia pentru a deschide geamul
  if(!deschis){
    while(pos >= 90){
      motor.write(pos);
      pos--;
      delay(15);
    }
    deschis = 1;
  }
}
void ploua(){
    int inchideGeamul_ca_te_ploua = analogRead(A2);
    //Serial.println(inchideGeamul_ca_te_ploua);
    if(deschis && inchideGeamul_ca_te_ploua < 400){ // daca ploua si fereastra este deschisa
       closeWindow();
       verificare_ploua = true;
    }
    else verificare_ploua = false;
}

void sound(){
    int min1 = 1024, max1 = 0;
    int sunet = analogRead(A3);
    int x = map(sunet, 0, 1204, 0, 123);
    //Serial.println(x);
    if(deschis && x > 60){
      closeWindow();
      delay(15);
    }
  
}

void temperature(){
    int cr = tempmodule.read11(temp); //citesc datele venite de la modului de temperatura si umiditate
    float tmp = tempmodule.temperature; //citesc temperatura 
    float umd = tempmodule.humidity; //citesc umiditatea 
    if(tmp >= (float)30){
      openWindow(); //deschide fereastra
    }
    Serial.println(tmp);
}
/*
  comenzi:
  48 - nimic
  49 - open
  52 - close
  daca ploua il inchid 
  daca sunt prea multi decibeli il inchid
  
 */
