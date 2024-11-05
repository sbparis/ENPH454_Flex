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
  float f1a = analogRead(A0), f2a = analogRead(A9);
  float f3a = analogRead(A2), f4a = analogRead(A3);
  float ft = analogRead(A4), f4b = analogRead(A5);
  float f3b = analogRead(A6), f2b = analogRead(A7);
  float f1b = analogRead(A8);

  // Display the Live readings 
  Serial.println("Live Voltage Readings:");
  Serial.print("Index Knuckle (f1a): "); Serial.println(f1a);
  Serial.print("Index Upper(f1b): "); Serial.println(f1b);
  Serial.print("Middle Knuckle (f2a): "); Serial.println(f2a);
  Serial.print("Middle Upper (f2b): "); Serial.println(f2b);
  Serial.print("Ring Knuckle (f3a): "); Serial.println(f3a);
  Serial.print("Ring Upper (f3b): "); Serial.println(f3b);
  Serial.print("Pinky Knuckle(f4a): "); Serial.println(f4a);
  Serial.print("Pinky Upper (f4b): "); Serial.println(f4b);
  Serial.print("Thumb (ft): "); Serial.println(ft);
  Serial.println();  // Blank line for easier reading
