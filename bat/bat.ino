
int led = 5;
int buzzer = 8;
int trig = 9;
int echo = 10;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);  

}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int timp = pulseIn(echo, HIGH);
  long long distanta = 0.034 * timp / 2;
  if(distanta <= 10){
    digitalWrite(led, HIGH);
    tone(buzzer, 500);
    
  }
  else{
    digitalWrite(led, LOW);
    noTone(buzzer);
  }
  delay(100);
}
