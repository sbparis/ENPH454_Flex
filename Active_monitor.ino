void setup() {
  Serial.begin(9600);
  // Set the pin modes for analog and digital inputs
  pinMode (A0, INPUT); pinMode (A9, INPUT); pinMode (A2, INPUT); pinMode (A3, INPUT); 
  pinMode (A4, INPUT); pinMode (A5, INPUT); pinMode (A6, INPUT); pinMode (A7, INPUT); 
  pinMode (A8, INPUT); 

void loop() {
  // Call the function to display live voltages
  displayVoltages();
  delay(500);  // Wait 500ms before updating again
}

// Function to read analog pins and display live voltages
void displayVoltages() {
  // Read analog values from sensors
  int f1a = analogRead(A0), f2a = analogRead(A9);
  int f3a = analogRead(A2), f4a = analogRead(A3);
  int ft = analogRead(A4), f4b = analogRead(A5);
  int f3b = analogRead(A6), f2b = analogRead(A7);
  int f1b = analogRead(A8), 
  
  // Convert the analog readings (0 to 1023) to voltage (0 to 5V)
  float voltage_f1a = f1a;
  float voltage_f1b = f1b;
  float voltage_f2a = f2a;
  float voltage_f2b = f2b;
  float voltage_f3a = f3a;
  float voltage_f3b = f3b;
  float voltage_f4a = f4a;
  float voltage_f4b = f4b;
  float voltage_ft = ft;


  // Display the voltages
  Serial.println("Live Voltage Readings:");
  Serial.print("Index Knuckle (f1a): "); Serial.println(voltage_f1a);
  Serial.print("Index Upper(f1b): "); Serial.println(voltage_f1b);
  Serial.print("Middle Knuckle (f2a): "); Serial.println(voltage_f2a);
  Serial.print("Middle Upper (f2b): "); Serial.println(voltage_f2b);
  Serial.print("Ring Knuckle (f3a): "); Serial.println(voltage_f3a);
  Serial.print("Ring Upper (f3b): "); Serial.println(voltage_f3b);
  Serial.print("Pinky Knuckle(f4a): "); Serial.println(voltage_f4a);
  Serial.print("Pinky Upper (f4b): "); Serial.println(voltage_f4b);
  Serial.print("Thumb (ft): "); Serial.println(voltage_ft);
  Serial.println();  // Blank line for easier reading
}
