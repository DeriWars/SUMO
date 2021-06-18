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
  pinMode(RED_LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  bool led1On = false;
  bool led2On = false;

  Serial.print("Salut");

  while(true){
    if(digitalRead(PUSH1) == LOW){
      led1On = !led1On;
    }

    if(digitalRead(PUSH2) == LOW){
      led2On = !led2On;
    }


    if(led1On){
      if(digitalRead(LED1) == HIGH){
        digitalWrite(LED1, LOW);
      } else {
        digitalWrite(LED1, HIGH);
      }
    } else{
      digitalWrite(LED1, LOW);
    }

    if(led2On){
      if(digitalRead(BLUE_LED) == HIGH){
        digitalWrite(BLUE_LED, LOW);
      } else {
        digitalWrite(BLUE_LED, HIGH);
      }
    } else{
      digitalWrite(BLUE_LED, LOW);
    }

    delay(100);
  }
}
