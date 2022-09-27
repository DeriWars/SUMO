/*
 * ROBY LE ROBOT (TM) - VERSION 1.2 (2022.01.25)
 * 
 * Laurenço MONTEIRO - Designer
 * Benjamin LAMBERT - Programmeur
 * 
 * ROBY LE ROBOT est une machine de guerre. Utiliser la avec précaution.
 * Programme compatible avec la version 5.0 du SUMOBOT ESIEESPACE
 */

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

const int PUSH = 8; // Assigne la valeur du pin assigner au bouton poussoir

const int MAX_DISTANCE = 100; // La distance maximal avec l'ennemi

const int SPEED = 60; // La vitesse de charge / d'esquive du robot
const int ROTATION_SPEED = 30; // La vitesse de rotation du robot

const int LED_G = 10;
const int LED_D = 11;

void setup() {
  Serial.begin(9600); // Initialise la communication avec le robot
  Serial.println("ROBY - STARTING...");
  delay(1000);
  
  pinMode(TRIG, OUTPUT); // Initialise le pin TRIG comme sortie (capteur utlra-son)
  pinMode(ECHO, INPUT); // Initialise le pin ECHO comme entrée (capteur utlra-son)

  pinMode(TCRT_AVANT, INPUT); // Initialise le pin TCRT_AVANT comme entrée (capteur ligne blanche)
  pinMode(TCRT_ARRIERE, INPUT); // Initialise le pin TCRT_ARRIERE comme entrée (capteur ligne blanche)

  pinMode(PUSH, INPUT_PULLUP); // Initialise le pin PUSH comme entrée PULLUP (bouton)

  pinMode(MOTEUR_G_PWM, OUTPUT); // Initalise le pin MOTEUR_G_PWM comme sortie
  pinMode(MOTEUR_G_DIR_1, OUTPUT); // Idem avec MOTEUR_G_DIR_1
  pinMode(MOTEUR_G_DIR_2, OUTPUT); // Idem avec MOTEUR_G_DIR_2
  pinMode(MOTEUR_D_PWM, OUTPUT); // Idem avec MOTEUR_D_PWM
  pinMode(MOTEUR_D_DIR_1, OUTPUT); // Idem avec MOTEUR_D_DIR_1
  pinMode(MOTEUR_D_DIR_2, OUTPUT); // Idem avec MOTEUR_D_DIR_2

  pinMode(LED_G, OUTPUT);
  pinMode(LED_D, OUTPUT);

  Serial.println("ROBY - Started!");
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_D, HIGH);

  // Attend que l'on appuie sur le bouton poussoir pour commencer le combat
  while(digitalRead(PUSH)){
    delay(1);
  }

  Serial.println("ROBY - WAITING FOR LAUNCH...");
  delay(5000); // Attends les 5 secondes réglementaires après appuie du bouton
  Serial.println("ROBY - LAUNCHING!");
}

void loop() {
  int back = digitalRead(TCRT_ARRIERE); // Récupère la valeur du capteur de ligne arrière
  int forward = digitalRead(TCRT_AVANT); // Récupère la valeur du capteur de ligne avant

  /*
   * Vérifie si un des deux capteurs de ligne à detecter une ligne (1)
   * Si c'est le cas, il repart dans la direction opposée à la ligne
   * pendant une demi seconde, puis s'arrête et cherche l'ennemi
   */
  if(back){
    Serial.println("ROBY - White line backward!");
    rightEngine(SPEED, 1, 0);
    leftEngine(SPEED, 1, 0);
    delay(500);
    stopEngine();
    return;
  } else if(forward){
    Serial.println("ROBY - White line forward!...");
    rightEngine(SPEED, 0, 1);
    leftEngine(SPEED, 0, 1);
    delay(500);
    stopEngine();
    return;
  }

  float distance = detect(); // Récupère la distance le séparant de l'objet le plus proche

  /*
   * Vérifie si la distance est une valeur cohérente (entre 0 et MAX_DISTANCE)
   * Si la valeur est cohérente, alors il considère que l'objet détecté est un ennemi,
   * puis engage une charge contre l'ennemi.
   * Si l'objet n'est pas un ennemi (valeur de la distance incohérente), alors il tourne sur
   * lui-même afin de rechercher un ennemi potentiel.
   * Si l'ennemi est perdu de vue pendant la charge, le robot se met à le chercher en tournant
   * sur lui-même.
   */
  if(distance <= MAX_DISTANCE && distance > 0){
    rightEngine(SPEED, 1, 0);
    leftEngine(SPEED, 1, 0);
    Serial.println("ROBY - ATTACKING...");
  }else{
    rightEngine(ROTATION_SPEED, 0, 1);
    leftEngine(ROTATION_SPEED, 1, 0);
    Serial.println("ROBY - SEARCHING...");
  }
}


/*
 * Permet la détection d'un objet et de calculer la distance
 * entre le robot et l'objet détecté.
 * @return La distance entre le robot et l'objet
 */
float detect() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG, LOW);

  int timeToTarget = pulseIn(ECHO, HIGH);
  float distance = (float)(timeToTarget * 17) / 1000.0;

  /*
   * Si le temps écoulé avant réception du signal est supérieur 
   * à 2000, on considère que la valeur de distance est incohérente
   * Ce constat est venu après des expérimentations où la distance dépassée
   * ce seuil de 2000 µs était incohérente par rapport à la distance réelle
   * observée
   */
  if(timeToTarget >= 2000){
    distance = -1;
  }

  return distance;
}


/*
 * Permet le contrôle total des moteurs droits uniquement
 */
void rightEngine(int speed, int direction, int opposite){
  digitalWrite(MOTEUR_D_DIR_1, direction); // On met la direction avant des moteurs droits à direction
  digitalWrite(MOTEUR_D_DIR_2, opposite); // On met la direction arrière des moteurs droits à opposite (l'opposée de la direction avant)
  analogWrite(MOTEUR_D_PWM, speed); // On applique la vitesse choisis par l'utilisateur (en quart)
}

/*
 * Permet le contrôle total des moteurs gauches uniquement
 */
void leftEngine(int speed, int direction, int opposite){
  digitalWrite(MOTEUR_G_DIR_1, direction); // On met la direction avant des moteurs droits à direction
  digitalWrite(MOTEUR_G_DIR_2, opposite); // On met la direction arrière des moteurs droits à opposite (l'opposée de la direction avant)
  analogWrite(MOTEUR_G_PWM, speed); // On applique la vitesse choisis par l'utilisateur (en quart)
}

/*
 * Permet de stopper les moteurs sans freinage supplémentaire
 */
void stopEngine(){
  rightEngine(255, 0, 0); // SPEED = 255 pour bloquer les roues
  leftEngine(255, 0, 0); // Idem
}
