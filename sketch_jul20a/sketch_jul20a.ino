int led = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  delay(2000);
  // put your main code here, to run repeatedly:

}
