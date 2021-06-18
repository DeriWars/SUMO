const int LED = 37;
const int LED2 = 38;
const int LED3 = 39;
const int LED4 = 40;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  shutdownLeds();
  digitalWrite(LED, LOW);
  delay(2000);

  shutdownLeds();
  digitalWrite(LED2, LOW);
  delay(2000);

  shutdownLeds();
  digitalWrite(LED3, LOW);
  delay(2000);

  shutdownLeds();
  digitalWrite(LED4, LOW);
  delay(2000);
}

void shutdownLeds(){
  digitalWrite(LED, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}
