const int TRIG = 5; // Assigne la valeur du pin TRIGGER
const int ECHO = 25; // Assigne la valeur du pin ECHO

const int TCRT_AVANT = A0; // Assigne la valeur du pin assigner au détecteur avant
const int TCRT_ARRIERE = A1; // Assigne la valeur du pin assigne au détecteur arrière

const int MOTEUR_G_PWM = 5;  // Assigne la valeur du pin assigner au PWM des moteurs gauches
const int MOTEUR_G_DIR_1 = 10; // Assigne la valeur du pin assigner à la direction 1 des moteurs gauches
const int MOTEUR_G_DIR_2 = 15; // Assigne la valeur du pin assigner à la direction 2 des moteurs gauches
const int MOTEUR_D_PWM = 6; // Assigne la valeur du pin assigner au PWM des moteurs droits
const int MOTEUR_D_DIR_1 = A3; // Assigne la valeur du pin assigner à la direction 1 des moteurs droits
const int MOTEUR_D_DIR_2 = A2; // Assigne la valeur du pin assigner à la direction 2 des moteurs droits

const int MAX_DISTANCE = 77; // The maximum distance that the enemy can be
const int ATTACK_DISTANCE = 20; // The distance where the sumobot start attacking
const int MIN_DISTANCE = 1; // The minimum distance with the enemy to engage evasive manoeuvers

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(TCRT_AVANT, INPUT); // Initialise le pin TCRT_AVANT comme entrée
  pinMode(TCRT_ARRIERE, INPUT); // Initialise le pin TCRT_ARRIERE comme entrée

  pinMode(MOTEUR_G_PWM, OUTPUT); // Initalise le pin MOTEUR_G_PWM comme sortie
  pinMode(MOTEUR_G_DIR_1, OUTPUT); // Idem avec MOTEUR_G_DIR_1
  pinMode(MOTEUR_G_DIR_2, OUTPUT); // Idem avec MOTEUR_G_DIR_2
  pinMode(MOTEUR_D_PWM, OUTPUT); // Idem avec MOTEUR_D_PWM
  pinMode(MOTEUR_D_DIR_1, OUTPUT); // Idem avec MOTEUR_D_DIR_1
  pinMode(MOTEUR_D_DIR_2, OUTPUT); // Idem avec MOTEUR_D_DIR_2

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  interrupts();
  attachInterrupt(TCRT_AVANT, forwardLine, RISING);
  attachInterrupt(TCRT_AVANT, backwardLine, RISING);
}

void loop() {
  ledsOff();
  
  while(true){
    int whiteLines = checkWhiteLine();

    if(whiteLines != 0){
      engageEvasiveManeuver(whiteLines);
      continue;
    }
    
    bool enemyDetected = findEnemy();

    if(enemyDetected){
      attack();
    } else {
      ledsOn(0, 1, 1);
      delay(500);
    }
  }
}


int checkWhiteLine(){
  if(digitalRead(TCRT_AVANT) && digitalRead(TCRT_ARRIERE)){
    return 2;
  }else if(digitalRead(TCRT_AVANT)){
    return 1;
  }else if(digitalRead(TCRT_ARRIERE)){
    return -1;
  }
  
  return 0;
}

void forwardLine(){
  engageEvasiveManeuver(-1);
}

void backwardLine(){
  engageEvasiveManeuver(1);
}

void engageEvasiveManeuver(int maneuver){
  stopEngine();
  ledsOn(1, 0, 1);
  
  if(maneuver == 1){ // Back sensor has detected white line
    rightEngine(200, 1, 0);
    leftEngine(255, 1, 0);
  } else if(maneuver == -1){ // Forward sensors have detected white line
    rightEngine(255, 1, 0);
    leftEngine(200, 1, 0);
  } else {
    startRotationRight(255);
    delay(500);
    stopEngine();
  }
}



boolean findEnemy() {
  float distance = detect();
  unsigned long detectionTime = -1;
  unsigned long lastDetectionTime = -1;
  int timeElapsed = -1;

  ledsOn(0, 0, 1);
  startRotationLeft(150);
  
  while(true){
    int maneuver = checkWhiteLine();
    distance = detect();
    
    if(!maneuver && distance > MIN_DISTANCE){
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
      ledsOn(1, 0, 0);
      centerPosition(timeElapsed);
      return true;
    }

    delay(5);
  }

  return false;
}

float detect() {
  digitalWrite(TRIG, HIGH);
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
  startRotationRight(255);
  delay((int)(timeElapsed / 2));
  stopEngine();
}



void attack(){
  ledsOn(1, 0, 0);
  
  int startTime = millis();
  int startDistance = detect();
  int distance = startDistance;
  
  while(distance > ATTACK_DISTANCE){
    distance = detect();

    if(distance > MAX_DISTANCE){ // Enemy has been lost
      forward(255);
      ledsOn(1, 1, 0);
      
      while(detect() && !checkWhiteLine()){
        delay(100);
      }
      
      stopEngine();
      return;
    }
  }
  
  int endTime = millis();
  float speed = (distance - startDistance) / (endTime - startTime);

  //Enemy go in face-to-face
  startRotationLeft(255);
  delay(1000);
  rightEngine(255, 1, 0);
  leftEngine(200, 1, 0);

  int maneuverTime;

  while(maneuverTime < 2000){
    maneuverTime += 10;
    int whiteLines = checkWhiteLine();

    if(!whiteLines){
      delay(10);
      continue;
    }

    engageEvasiveManeuver(whiteLines);
    return;
  }
}



void forward(int speed){
  rightEngine(speed, 1, 0);
  leftEngine(speed, 1, 0);
}

void backward(int speed){
  rightEngine(speed, 0, 1);
  leftEngine(speed, 0, 1);
}

void startRotationLeft(int speed){
  leftEngine(speed, 1, 0);
  rightEngine(speed, 0, 1);
}

void startRotationRight(int speed){
  rightEngine(speed, 1, 0);
  leftEngine(speed, 0, 1);
}

void rightEngine(int speed, int direction, int opposite){
  digitalWrite(MOTEUR_D_DIR_1, direction); // On met la direction avant des moteurs droits à direction
  digitalWrite(MOTEUR_D_DIR_2, opposite); // On met la direction arrière des moteurs droits à opposite (l'opposée de la direction avant)
  analogWrite(MOTEUR_D_PWM, speed); // On applique la vitesse choisis par l'utilisateur (en quart)
}

void leftEngine(int speed, int direction, int opposite){
  digitalWrite(MOTEUR_G_DIR_1, direction); // On met la direction avant des moteurs droits à direction
  digitalWrite(MOTEUR_G_DIR_2, opposite); // On met la direction arrière des moteurs droits à opposite (l'opposée de la direction avant)
  analogWrite(MOTEUR_G_PWM, speed); // On applique la vitesse choisis par l'utilisateur (en quart)
}

void stopEngine(){
  rightEngine(0, 0, 0);
  leftEngine(0, 0, 0);
}



void ledsOn(int r, int g, int b){
  r = (r == 1) ? r = HIGH : r = LOW;
  g = (g == 1) ? g = HIGH : g = LOW;
  b = (b == 1) ? b = HIGH : b = LOW;
  
  digitalWrite(RED_LED, r);
  digitalWrite(GREEN_LED, g);
  digitalWrite(BLUE_LED, b);
}

void ledsOff(){
  ledsOn(0, 0, 0);
}
