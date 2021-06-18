#define ANALOG_INPUT 8

void setup() {
  Serial.begin(9600);
  delay(1000);
  analogReference(DEFAULT);
  pinMode(ANALOG_INPUT, INPUT);
  analogReadResolution(14);
}

void loop() {
  int inputValue = analogRead(ANALOG_INPUT);
  Serial.println(inputValue);
  float voltage = inputValue * 3.3 / (float)16383;

  Serial.print("Voltage : ");
  Serial.print(voltage);
  Serial.println("V");

  delay(1000);
}
