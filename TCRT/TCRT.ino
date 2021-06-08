const int TCRT_AVANT = A0; // Assigne la valeur du pin assigner au détecteur avant
const int TCRT_ARRIERE = A1; // Assigne la valeur du pin assigne au détecteur arrière

void setup() {
  Serial.begin(9600); // Débute la communication avec la carte à une vitesse de 9600
  pinMode(TCRT_AVANT, INPUT); // Initialise le pin TCRT_AVANT comme entrée
  pinMode(TCRT_ARRIERE, INPUT); // Initialise le pin TCRT_ARRIERE comme entrée
}

void loop() {
  if(digitalRead(TCRT_AVANT) || digitalRead(TCRT_ARRIERE)){ // Vérifie si l'un des deux capteurs est actif
    Serial.println("Lieu : Ligne blanche"); // Affiche un message si l'un des deux capteurs repère une zone blanche
  } else{ // Si aucun des deux capteurs ne détecte un ligne blanche
    Serial.println("Lieu : Piste (zone noire)"); // Affiche un message pour dire que le robot est dans la zone noire
  }

  delay(2000); // Attends 2 secondes avant de refaire les mêmes instructions
}
