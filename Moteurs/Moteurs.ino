const int MOTEUR_G_PWM = 5;  // Assigne la valeur du pin assigner au PWM des moteurs gauches
const int MOTEUR_G_DIR_1 = 10; // Assigne la valeur du pin assigner à la direction 1 des moteurs gauches
const int MOTEUR_G_DIR_2 = 15; // Assigne la valeur du pin assigner à la direction 2 des moteurs gauches
const int MOTEUR_D_PWM = 6;  // Assigne la valeur du pin assigner au PWM des moteurs droits
const int MOTEUR_D_DIR_1 = A3; // Assigne la valeur du pin assigner à la direction 1 des moteurs droits
const int MOTEUR_D_DIR_2 = A2; // Assigne la valeur du pin assigner à la direction 2 des moteurs droits

void setup() {
  Serial.begin(9600); // Débute la communication avec la carte à une vitesse de 9600
  pinMode(MOTEUR_G_PWM, OUTPUT); // Initalise le pin MOTEUR_G_PWM comme sortie
  pinMode(MOTEUR_G_DIR_1, OUTPUT); // Idem avec MOTEUR_G_DIR_1
  pinMode(MOTEUR_G_DIR_2, OUTPUT); // Idem avec MOTEUR_G_DIR_2
  pinMode(MOTEUR_D_PWM, OUTPUT); // Idem avec MOTEUR_D_PWM
  pinMode(MOTEUR_D_DIR_1, OUTPUT); // Idem avec MOTEUR_D_DIR_1
  pinMode(MOTEUR_D_DIR_2, OUTPUT); // Idem avec MOTEUR_D_DIR_2
}

void loop() {
  String motor = readConsole("Moteur (0==droit, 1==gauche) : "); // Lis la console pour savoir le moteur a activé
  String direction = readConsole("Direction (0==avant, 1==arrière) : "); // Lis la console pour avoir la direction du moteur
  String power = readConsole("Puissance des moteurs (0 à 4) : "); // Lis la console pour savoir la puissance du moteur

  int realDirection; // Direction en int et non en String
  int oppositeDirection; // Direction opposée à realDirection
  int realPower; // Puissance en int et non en String

  if(direction.equals("0\n")){ // On extrait la valeur int de la String lu
      realDirection = 1; // On assigne cette valeur à realDirection
      oppositeDirection = 0; // On assigne son "opposée" à oppositeDirection
  }else if(direction.equals("1\n")){ // Idem
      realDirection = 0; // Idem
      oppositeDirection = 1; // Idem
  }else{ // Si l'utilisateur ne rentre pas une direction valide
      realDirection = -1; // On assigne une valeur par défaut facilement détectable
      oppositeDirection = -1; // On assigne une valeur par défaut facilement détectable
      Serial.println("Entrée non valide (direction). Entrée valide : 0 ou 1"); // On affiche un message d'erreur
  }

  if(power.equals("0\n")){ // De même que pour la direction mais avec la puissance
      realPower = 0; // On assigne la valeur correspondante à realPower
  }else if(power.equals("1\n")){ // Idem
      realPower = 1; // Idem
  }else if(power.equals("2\n")){ // Idem
      realPower = 2; // Idem
  }else if(power.equals("3\n")){ // Idem
      realPower = 3; // Idem
  }else if(power.equals("4\n")){ // Idem
      realPower = 4; // Idem
  }else{ // Si l'utilisateur ne rentre pas une puissance valide
      realPower = -1; // On assigne une valeur par défaut facilement détectable
      Serial.println("Entrée non valide (puissance). Entrée valide : 0 à 4 (entier)"); // On affiche un message d'erreur
  }

  if(realDirection != -1 && realPower != -1){ // On vérifie que les deux entrées (direction et puissance) sont valides
    if(motor.equals("0\n")){ // On regarde sur quel moteur il faut appliquer les instructions
      digitalWrite(MOTEUR_D_DIR_1, realDirection); // On met la direction avant des moteurs droits à realDirection
      digitalWrite(MOTEUR_D_DIR_2, oppositeDirection); // On met la direction arrière des moteurs droits à oppositeDirection (l'opposée de la direction avant)
      analogWrite(MOTEUR_D_PWM, realPower * 255 / 4); // On applique la vitesse choisis par l'utilisateur (en quart)
    }else if(motor.equals("1\n")){ // Idem mais avec les moteurs gauches et non droits
      digitalWrite(MOTEUR_G_DIR_1, realDirection); // Idem mais avec les moteurs gauches et non droits
      digitalWrite(MOTEUR_G_DIR_2, oppositeDirection); // Idem mais avec les moteurs gauches et non droits
      analogWrite(MOTEUR_G_PWM, realPower * 255 / 4); // Idem mais avec les moteurs gauches et non droits
    }else{ // Si l'utilisateur ne rentre pas un moteur valide
      Serial.println("Entrée non valide (moteur). Entrée valide : 0 ou 1"); // Si l'utilisateur ne rentre pas une puissance valide
    }
  }

  delay(100); // On attends 100 milliseconds pour avoir un delai minimum d'activation des moteurs
}

// Lis les entrées de l'utilisateur dans la console
// Param: affiche un message informatif sur ce que dois entrer l'utilisateur
String readConsole(String message) {
  Serial.println(message); // Affiche le message informatif
  while(Serial.available() == 0) { } // Attend que l'utilisateur est entré quelque chose
  String statment = Serial.readString(); // Lis l'entrée de l'utilisateur
  return statment; // Retourne le message entré par l'utilisateur
}
