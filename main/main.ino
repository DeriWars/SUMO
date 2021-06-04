/*Permet de mesurer la distance toutes les 5 secondes*/

#define TRIG 5
#define ECHO 25

const int MAX_DISTANCE = 77;

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  ledsOff();
  
  while(true){
    bool enemyDetected = detect();

    if(enemyDetected){
      attack();
    } else {
      ledsOff();
      digitalWrite(GREEN_LED, HIGH);
      delay(500);
    }
  }
}


int checkWhiteLine(){
  return false;
}

void engageEvasiveManeuver(int maneuver){
  stopEngine();
  
  if(maneuver == -1){
    startRightEngine(200);
    startLeftEngine(255);
  } else if(maneuver == 1){
    startRightEngine(255);
    startLeftEngine(200);
  } else {
    startRightEngine(255);
    startLeftEngine(255);
  }
}



boolean findEnemy() {
  float distance = detect();
  unsigned long detectionTime = -1;
  unsigned long lastDetectionTime = -1;
  int timeElapsed = -1;

  digitalWrite(BLUE_LED, HIGH);
  startRotationLeft();
  
  while(true){
    int maneuver = checkWhiteLine();
    distance = detect();
    
    if(!maneuver && distance <= MAX_DISTANCE){
      engageEvasiveManeuver(maneuver);
    }

    if(timeElapsed == -1){
      if(distance <= 0){
        Serial.print("Detection error! Distance is ");
        Serial.print(distance);
        Serial.println(" cm.");
      } else if(distance > MAX_DISTANCE && lastDetectionTime > 0){
        timeElapsed = (int)(lastDetectionTime - detectionTime);
      } else {
        if(detectionTime == -1){
          detectionTime = millis();
        } else{
          lastDetectionTime = millis();
        }
      }
    } else{
      stopEngine();
      ledsOff();
      digitalWrite(RED_LED, HIGH);
      centerPosition(timeElapsed);
      return true;
    }

    delay(10);
  }

  return false;
}

float detect() {
  igitalWrite(TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG, LOW);

  int timeToTarget = pulseIn(ECHO, HIGH);
  float distance = (float)(timeToTarget * 17) / 1000.0;
    
  Serial.print("Object detected at ");
  Serial.print(distance);
  Serial.println(" cm.");

  return distance;
}

void centerPosition(int timeElapsed){
  startRotationRight();
  delay((int)(timeElapsed / 2));
  stopEngine();
}

void attack(){
  
}



void forward(int speed){
  
}

void backward(int speed){
  
}

void startRotationLeft(int speed){
  startLeftEngine(speed);
  startRightEngine(-speed);
}

void startRotationRight(int speed){
  startRightEngine(speed);
  startLeftEngine(-speed);
}

void startRightEngine(int speed){
  
}

void startLeftEngine(int speed){
  
}

void stopEngine(){
  
}



void ledsOff(){
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}
