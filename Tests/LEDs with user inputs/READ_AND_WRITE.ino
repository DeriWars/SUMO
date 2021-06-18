/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
*/
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  delay(1000);
  pinMode(RED_LED, OUTPUT);
  pinMode(LED1, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  while(true){
    Serial.println("Please enter a statment: ");
    while(Serial.available() == 0) { }
    String statment = Serial.readString();
    Serial.println(statment);

    if(statment.equals("led1 on\n")){
      digitalWrite(LED1, HIGH);
    } else if(statment.equals("led1 off\n")){
      digitalWrite(LED1, LOW);
    }

    if(statment.equals("led2 on\n")){
      digitalWrite(RED_LED, HIGH);
    } else if(statment.equals("led2 off\n")){
      digitalWrite(RED_LED, LOW);
    }

    delay(10);
  }
}
