const int TRIG = 13; // Assigne la valeur du pin TRIGGER
const int ECHO = 11; // Assigne la valeur du pin ECHO

const int TCRT_AVANT = A1; // Assigne la valeur du pin assigner au détecteur avant
const int TCRT_ARRIERE = A0; // Assigne la valeur du pin assigne au détecteur arrière

const int MOTEUR_G_PWM = 9;  // Assigne la valeur du pin assigner au PWM des moteurs gauches
const int MOTEUR_G_DIR_1 = 7; // Assigne la valeur du pin assigner à la direction 1 des moteurs gauches
const int MOTEUR_G_DIR_2 = 12; // Assigne la valeur du pin assigner à la direction 2 des moteurs gauches
const int MOTEUR_D_PWM = 10;  // Assigne la valeur du pin assigner au PWM des moteurs droits
const int MOTEUR_D_DIR_1 = A2; // Assigne la valeur du pin assigner à la direction 1 des moteurs droits
const int MOTEUR_D_DIR_2 = A3; // Assigne la valeur du pin assigner à la direction 2 des moteurs droits

const int MAX_DISTANCE = 77; // The maximum distance that the enemy can be
const int ATTACK_DISTANCE = 20; // The distance where the sumobot start attacking
const int MIN_DISTANCE = 2; // The minimum distance with the enemy to engage evasive manoeuvers

const int PUSH = 8;

const int SPEED = 150;
const int MIN_SPEED = 50;

void setup() {
  Serial.println("ETALP - STARTING...");
  Serial.begin(9600);
  delay(1000);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(TCRT_AVANT, INPUT); // Initialise le pin TCRT_AVANT comme entrée
  pinMode(TCRT_ARRIERE, INPUT); // Initialise le pin TCRT_ARRIERE comme entrée

  pinMode(PUSH, INPUT_PULLUP);

  pinMode(MOTEUR_G_PWM, OUTPUT); // Initalise le pin MOTEUR_G_PWM comme sortie
  pinMode(MOTEUR_G_DIR_1, OUTPUT); // Idem avec MOTEUR_G_DIR_1
  pinMode(MOTEUR_G_DIR_2, OUTPUT); // Idem avec MOTEUR_G_DIR_2
  pinMode(MOTEUR_D_PWM, OUTPUT); // Idem avec MOTEUR_D_PWM
  pinMode(MOTEUR_D_DIR_1, OUTPUT); // Idem avec MOTEUR_D_DIR_1
  pinMode(MOTEUR_D_DIR_2, OUTPUT); // Idem avec MOTEUR_D_DIR_2

  Serial.println("ETALP - Started!");

  while(digitalRead(PUSH)){
    delay(1);
  }

  Serial.println("ETALP - LAUNCHING...");
}

void loop() {
  int back = digitalRead(TCRT_ARRIERE);
  int forward = digitalRead(TCRT_AVANT);

  if(back){
    Serial.println("ETALP - White line backward!");
    rightEngine(SPEED, 0, 1);
    leftEngine(SPEED, 0, 1);
    delay(1000);
    stopEngine();
    return;
  } else if(forward){
    Serial.println("ETALP - White line forward!...");
    rightEngine(SPEED, 1, 0);
    leftEngine(SPEED, 1, 0);
    delay(1000);
    stopEngine();
    return;
  }

  float distance = detect();

  if(distance <= MAX_DISTANCE && distance > 0){
    rightEngine(SPEED, 1, 0);
    leftEngine(SPEED, 1, 0);
    Serial.println("ETALP - ATTACKING...");
  }else{
    rightEngine(MIN_SPEED, 1, 0);
    leftEngine(MIN_SPEED, 0, 1);
    Serial.println("ETALP - SEARCHING...");
  }

  delay(500);
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

  if(timeToTarget >= 2000){
    distance = -1;
  }

  return distance;
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
