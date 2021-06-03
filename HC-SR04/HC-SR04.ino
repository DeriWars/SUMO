/*Permet de mesurer la distance toutes les 5 secondes*/

#define TRIG 3
#define ECHO 4

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
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    int timeToTarget = pulseIn(ECHO, HIGH);
    Serial.println(timeToTarget);
    float distance = (float)(timeToTarget * 17) / 1000.0;
    
    Serial.print("Object detected at ");
    Serial.print(distance);
    Serial.println(" cm.");
    delay(5000);
  }
}
