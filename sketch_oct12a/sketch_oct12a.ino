#define Output_Pin 9

// Setare alfabet
static String Letters[ ] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "};
static String Morse_Letters[ ] = {
  ".-", //A
  "-...", //B
  "-.-.", //C
  "-..", //D
  ".", //E
  "..-.", //F
  "--.", //G
  "....", //H
  "..", //I
  ".---", //J
  "-.-", //K
  ".-..", //L
  "--", //M
  "-.", //N
  "---", //O
  ".--.", //P
  "--.-", //Q
  ".-.", //R
  "...", //S
  "-", //T
  "..-", //U
  "...-", //V
  ".--", //W
  "-..-", //X
  "-.--", //Y
  "--..", //Z
  "-----", //0
  ".----", //1
  "..---", //2
  "...--", //3
  "....-", //4
  ".....", //5
  "-....", //6
  "--...", //7
  "---..", //8
  "----." //9
  "_" // _
};
// Lungime alfabet
int AlfabetLen;
// Rules
int Punct = 50;
int Linie = 3 * Punct;
int Spatiu_litera = Linie;
int Spatiu_Cuvinte = 7 * Punct;

void setup()
{
  pinMode(Output_Pin, OUTPUT);
  Serial.begin(9600);
  
  //Lungime alfabet
  AlfabetLen = sizeof(Letters) / 6;
  //Serial.print("Size: ");
  //Serial.println(AlfabetLen);
}

String Search_Match(String caracter) {
  for (int foo = 0; foo < AlfabetLen; ++foo) {
    if (caracter == Letters[foo]) {
      return Morse_Letters[foo];
    }
  }
}

void loop()
{
  if (Serial.available()/*Daca am comunicatie seriala*/){
     String DataRead = Serial.readString(); // Citeste un sir de caractere terminate cu "enter"
      
     Serial.println(DataRead); // Afiseaza sirul initial
      
     int Datalength = DataRead.length(); // Lungimea sirului
      
      for (int i = 0; i < Datalength - 1; ++i){
        String c = DataRead.substring(i, i+1); // Sparg sirul in caractere
        Serial.print(c);
        Serial.print(" ");
        Serial.println(Search_Match(c));
        
        String DataOut = Search_Match(c);
        int DataOutLen = Search_Match(c).length();
        
        for (int bar = 0; bar < DataOutLen; ++bar) {
          String c = DataOut.substring(bar, bar+1);
          if (c == ".") {
            tone(Output_Pin, 400);
            delay(Punct);
            noTone(Output_Pin);
            delay(Punct);
          }
          if (c == "-") {
            tone(Output_Pin, 400);
            delay(Linie);
            noTone(Output_Pin);
            delay(Punct);
          }
        }
        if (c == " ") {
          delay(Spatiu_Cuvinte);
        }
        else {
          delay(Spatiu_litera);
        }   
      }
   }
}
