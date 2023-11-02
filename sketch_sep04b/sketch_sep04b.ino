const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int led = 13;

long durata;
int distanta;
int distantaSiguranta;


void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
Serial.begin(9600); 
}


void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

durata = pulseIn(echoPin, HIGH);

distanta= durata*0.034/2;

distantaSiguranta = distanta;
if (distantaSiguranta <= 10){
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
}

Serial.print("Distanta este: ");
Serial.println(distanta);
}
