const int MOTEUR_G_PWM = 9;  // Assigne la valeur du pin assigner au PWM des moteurs gauches
const int MOTEUR_G_DIR_1 = 7; // Assigne la valeur du pin assigner à la direction 1 des moteurs gauches
const int MOTEUR_G_DIR_2 = 12; // Assigne la valeur du pin assigner à la direction 2 des moteurs gauches
const int MOTEUR_D_PWM = 10;  // Assigne la valeur du pin assigner au PWM des moteurs droits
const int MOTEUR_D_DIR_1 = A2; // Assigne la valeur du pin assigner à la direction 1 des moteurs droits
const int MOTEUR_D_DIR_2 = A3; // Assigne la valeur du pin assigner à la direction 2 des moteurs droits

void setup() {
  Serial.begin(9600); // Débute la communication avec la carte à une vitesse de 9600
  delay(1000);
  pinMode(MOTEUR_G_PWM, OUTPUT); // Initalise le pin MOTEUR_G_PWM comme sortie
  pinMode(MOTEUR_G_DIR_1, OUTPUT); // Idem avec MOTEUR_G_DIR_1
  pinMode(MOTEUR_G_DIR_2, OUTPUT); // Idem avec MOTEUR_G_DIR_2
  pinMode(MOTEUR_D_PWM, OUTPUT); // Idem avec MOTEUR_D_PWM
  pinMode(MOTEUR_D_DIR_1, OUTPUT); // Idem avec MOTEUR_D_DIR_1
  pinMode(MOTEUR_D_DIR_2, OUTPUT); // Idem avec MOTEUR_D_DIR_2
}

void loop() {
  digitalWrite(MOTEUR_G_DIR_1, 1); // On met la direction avant des moteurs droits à realDirection
  digitalWrite(MOTEUR_G_DIR_2, 0); // On met la direction arrière des moteurs droits à oppositeDirection (l'opposée de la direction avan
  analogWrite(MOTEUR_G_PWM, 2 * 255 / 4); // On applique la vitesse choisis par l'utilisateur (en quart)

  digitalWrite(MOTEUR_D_DIR_1, 1); // On met la direction avant des moteurs droits à realDirection
  digitalWrite(MOTEUR_D_DIR_2, 0); // On met la direction arrière des moteurs droits à oppositeDirection (l'opposée de la direction avan
  analogWrite(MOTEUR_D_PWM, 2 * 255 / 4); // On applique la vitesse choisis par l'utilisateur (en quart)
}
