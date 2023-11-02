#include <CapacitiveSensor.h>

CapacitiveSensor cs_2_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_4 = CapacitiveSensor(2,4); 
CapacitiveSensor cs_2_5 = CapacitiveSensor(2,5); 
CapacitiveSensor cs_2_6 = CapacitiveSensor(2,6); 
CapacitiveSensor cs_2_7 = CapacitiveSensor(2,7); 
CapacitiveSensor cs_2_8 = CapacitiveSensor(2,8); 
CapacitiveSensor cs_2_9 = CapacitiveSensor(2,9); 
CapacitiveSensor cs_2_10 = CapacitiveSensor(2,10); 
int sound = 11;
void setup() {
   cs_2_10.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   //pinMode(sound, OUTPUT);
}

void loop() {
    long start = millis();
    long total1 =  cs_2_3.capacitiveSensor(3000);
    long total2 =  cs_2_4.capacitiveSensor(3000);
    long total3 =  cs_2_5.capacitiveSensor(3000);
    long total4 =  cs_2_6.capacitiveSensor(3000);
    long total5 =  cs_2_7.capacitiveSensor(3000);
    long total6 =  cs_2_8.capacitiveSensor(3000);
    long total7 =  cs_2_9.capacitiveSensor(3000);
    long total8 =  cs_2_10.capacitiveSensor(3000);   

  //  Serial.println(total1);                  // print sensor output 1
 Serial.println(total1);
    if(total1 > 400) tone(sound, 261.63);
    if(total2 > 400) tone(sound, 293.66);
    if(total3 > 400) tone(sound, 329.63);
    if(total4 > 400) tone(sound, 349.23);
    if(total5 > 400) tone(sound, 392.00);
    if(total6 > 400) tone(sound, 440.00);
    if(total7 > 400) tone(sound, 493.88);
    if(total8 > 400) tone(sound, 523.25);
    
    if(total1 <= 400 && total2 <= 400&& total3 <= 400 && total4 <= 400&& total5 <= 400 && total6 <= 400 
                    && total7 <= 400 && total8 <= 400)
      noTone(sound);
    delay(10);  
}
