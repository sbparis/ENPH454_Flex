const int maxReadings = 100; // Define max number of readings per movement
float readingsArray[maxReadings][9]; // 2D array for 9 sensors and maxReadings rows
int currentReading = 0; // Track the current number of readings
float minThreshold[1,2,3,4,5,6,7,8,9]

void setup() {
  Serial.begin(9600);
  // Set the pin modes for analog inputs
  pinMode(A0, INPUT); pinMode(A9, INPUT); pinMode(A2, INPUT); pinMode(A3, INPUT); 
  pinMode(A4, INPUT); pinMode(A5, INPUT); pinMode(A6, INPUT); pinMode(A7, INPUT); 
  pinMode(A8, INPUT); 
}

void loop() {
  float* readings = ReadVoltages();
  if (readings != nullptr) { // Valid readings returned
      if (currentReading < maxReadings) { // Add reading if within limit
        for (int i = 0; i < 9; i++) {
          readingsArray[currentReading][i] = readings[i]; // Store each sensor reading
        }
        currentReading++;
      }
  } else if (currentReading > 0) { // If glove was in motion and now at rest
    float maxValues[9];
    calculateMaxValues(maxValues); // Get max values for movement
    char detectedLetter = categorizeRead(maxValues); // Categorize the movement
    Serial.print("Detected Letter: ");
    Serial.println(detectedLetter);
    currentReading = 0; // Reset for the next movement
  } // Update to indicate motion
  delay(500); // Wait 500ms before updating again
}

// Function to read analog pins and return array of voltages
float* ReadVoltages() {
  static float values[9];
  
  // Read analog values from sensors
  values[0] = analogRead(A0);
  values[1] = analogRead(A9);
  values[2] = analogRead(A2);
  values[3] = analogRead(A3);
  values[4] = analogRead(A4);
  values[5] = analogRead(A5);
  values[6] = analogRead(A6);
  values[7] = analogRead(A7);
  values[8] = analogRead(A8);

  // Check for any invalid readings
  for (int i = 0; i < 9; i++) {
    if (values[i] > minThreshold[i]) {
      return values;
    }
  }
  return nullptr;
}

// Function to calculate max values from each sensor column in readingsArray
void calculateMaxValues(float maxValues[]) {
  for (int i = 0; i < 9; i++) {
    maxValues[i] = readingsArray[0][i]; // Initialize with the first reading
    for (int j = 1; j < currentReading; j++) {
      if (readingsArray[j][i] > maxValues[i]) {
        maxValues[i] = readingsArray[j][i];
      }
    }
  }
}

// Placeholder for the function to categorize the movement as a letter
char categorizeRead(float maxValues[]) {
  // Implement categorization logic based on maxValues
  // For now, return a placeholder character
  return 'A';
}

