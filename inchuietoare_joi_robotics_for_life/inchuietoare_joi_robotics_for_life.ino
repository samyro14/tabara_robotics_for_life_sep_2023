#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

Servo servo; 

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

const byte ROWS = 4; 
const byte COLS = 3; 

const String pass = "2008";
String pass_try_string = "";

char Keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8}; 

Keypad keypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  
  servo.attach(A0);  
  servo.write(0);
}
  
void loop(){
  char Key = keypad.getKey(); // Citim tasta de pe keypad
  
  if (Key == '*'){ // Daca este '*' atunci incepem sa citim pinul
    pass_try_string = "";
    
    servo.write(0);
    for (int foo = 0; foo < 4; ++foo) { // Repetam ciclu de ctitire de 4 ori pentru a citi pinul (tasta cu tasta)
      char Key1 = keypad.getKey();
      while (not Key1) {
        Key1 = keypad.getKey(); // Asteptam pana se apasa o tasta
      }
      if (Key1 != '#' && Key1 != '*') {
        pass_try_string = pass_try_string + Key1; // Adaugam o cifra la incercarea de pin
        Serial.println(pass_try_string);
      }
    }
    if (pass_try_string == pass) { // Comparam incercarea de pin cu pinul real
    Serial.println("CORECT");
        servo.write(90);
        delay(2000);
        servo.write(0);
    }
    else {
      Serial.println("GRESIT"); 
        servo.write(0);
    }
  }
  
  if (rfid.PICC_IsNewCardPresent()) { // Daca e simt un card
    if (rfid.PICC_ReadCardSerial()) { // Si pot sa il citesc
      if (rfid.uid.uidByte[0] == 161 && rfid.uid.uidByte[1] == 20 && rfid.uid.uidByte[2] == 152 && rfid.uid.uidByte[3] == 36) {
        Serial.println("CORECT"); // Daca ID-ul cardului este acelasi cu ID-ul retinut atunci deschidem usa/bariera
        servo.write(90);
        delay(2000);
        servo.write(0);
      }
      else {
        Serial.println("GRESIT"); // Daca nu atunci nu deschidem usa/bariera
        servo.write(0);
        //READNUID
      }
    }
  }
}
