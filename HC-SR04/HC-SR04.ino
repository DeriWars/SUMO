/*Permet de mesurer la distance toutes les 5 secondes*/

#define TRIG 5
#define ECHO 25

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  float distance;

  while(true){
    digitalWrite(TRIG, HIGH);
    distance = digitalRead(ECHO) * 17 / 100.0;
    digitalWrite(TRIG, LOW);
    
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(5000);
  }
}
