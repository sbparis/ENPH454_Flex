void setup() {
  Serial.begin(9600);
  // Set the pin modes for analog and digital inputs
  pinMode (A0, INPUT); pinMode (A1, INPUT); pinMode (A2, INPUT); pinMode (A3, INPUT); 
  pinMode (A4, INPUT); pinMode (A5, INPUT); pinMode (A6, INPUT); pinMode (A7, INPUT); 
  pinMode (A8, INPUT); pinMode (A9, INPUT); pinMode (A10, INPUT); pinMode (A11, INPUT);
}

void loop() {
  // Call the function to display live voltages
  displayVoltages();
  delay(500);  // Wait 500ms before updating again
}

// Function to read analog pins and display live voltages
void displayVoltages() {
  // Read analog values from sensors
  int f1a = analogRead(A0), f1b = analogRead(A1);
  int f2a = analogRead(A2), f2b = analogRead(A3);
  int f3a = analogRead(A4), f3b = analogRead(A5);
  int f4a = analogRead(A6), f4b = analogRead(A7);
  int f5a = analogRead(A8), f5b = analogRead(A9);
  int palm = analogRead(A10);
  
  // Convert the analog readings (0 to 1023) to voltage (0 to 5V)
  float voltage_f1a = f1a;
  float voltage_f1b = f1b;
  float voltage_f2a = f2a;
  float voltage_f2b = f2b;
  float voltage_f3a = f3a;
  float voltage_f3b = f3b;
  float voltage_f4a = f4a;
  float voltage_f4b = f4b;
  float voltage_f5a = f5a;
  float voltage_f5b = f5b;
  float voltage_palm = palm;

  // Display the voltages
  Serial.println("Live Voltage Readings:");
  Serial.print("Thumb Sensor 1 (f1a): "); Serial.println(voltage_f1a);
  Serial.print("Thumb Sensor 2 (f1b): "); Serial.println(voltage_f1b);
  Serial.print("Index Finger Sensor 1 (f2a): "); Serial.println(voltage_f2a);
  Serial.print("Index Finger Sensor 2 (f2b): "); Serial.println(voltage_f2b);
  Serial.print("Middle Finger Sensor 1 (f3a): "); Serial.println(voltage_f3a);
  Serial.print("Middle Finger Sensor 2 (f3b): "); Serial.println(voltage_f3b);
  Serial.print("Ring Finger Sensor 1 (f4a): "); Serial.println(voltage_f4a);
  Serial.print("Ring Finger Sensor 2 (f4b): "); Serial.println(voltage_f4b);
  Serial.print("Pinky Finger Sensor 1 (f5a): "); Serial.println(voltage_f5a);
  Serial.print("Pinky Finger Sensor 2 (f5b): "); Serial.println(voltage_f5b);
  Serial.print("Palm Sensor: "); Serial.println(voltage_palm);

  Serial.println();  // Blank line for easier reading
}
