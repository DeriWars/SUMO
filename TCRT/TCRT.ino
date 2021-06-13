const int TCRT_AVANT = A0; // Assigne la valeur du pin assigner au détecteur avant
const int TCRT_ARRIERE = A1; // Assigne la valeur du pin assigne au détecteur arrière

void setup() {
  Serial.begin(9600); // Débute la communication avec la carte à une vitesse de 9600
  pinMode(TCRT_AVANT, INPUT); // Initialise le pin TCRT_AVANT comme entrée
  pinMode(TCRT_ARRIERE, INPUT); // Initialise le pin TCRT_ARRIERE comme entrée

  interrupts();
  attachInterrupt(TCRT_AVANT, forward, RISING);
  attachInterrupt(TCRT_ARRIERE, backward, RISING);
}

void loop() {
  Serial.println("Lieu : Piste (zone noire)"); // Affiche un message pour dire que le robot est dans la zone noire
  delay(2000); // Attends 2 secondes avant de refaire les mêmes instructions
}

void forward(){
  Serial.println("Lieu : Hors zone (ligne blanche)");
}

void backward(){
  Serial.println("Lieu : Hors zone (ligne blanche)");
}
