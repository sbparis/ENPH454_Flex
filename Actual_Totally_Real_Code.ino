const int maxReadings = 100; // Define max number of readings per movement
float readingsArray[maxReadings][9]; // 2D array for 9 sensors and maxReadings rows
int currentReading = 0; // Track the current number of readings
float minThreshold[9] = {}

void setup() {
  Serial.begin(9600);
  // Set the pin modes for analog inputs
  pinMode(A15, INPUT); pinMode(A14, INPUT); pinMode(A13, INPUT); pinMode(A12, INPUT); 
  pinMode(A11, INPUT); pinMode(A9, INPUT); pinMode(A10, INPUT); pinMode(A7, INPUT); 
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
  values[0] = analogRead(A15);
  values[1] = analogRead(A14);
  values[2] = analogRead(A13);
  values[3] = analogRead(A12);
  values[4] = analogRead(A11);
  values[5] = analogRead(A9);
  values[6] = analogRead(A10);
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
  if (maxValues[7] > threshold_high_middle_upper && maxValues[1] > threshold_high_lower_middle) {
    // Check if middle finger is bent enough (high threshold)
    if (maxValues[8] > threshold_high_f1a && maxValues[0] > threshold_high_f1b) {
        if (maxValues[4] > threshold_high_th) {
            if (maxValues[5] > threshold_high_f4a && maxValues[3] > threshold_high_f4b) {
                if (maxValues[6] > threshold_high_f3a && maxValues[2] > threshold_high_f3b) {
                    return "S";
                } else {
                    return "M";
                }
            } else {
                if (mpu_moving) {
                    return "J";
                } else {
                    return "I";
                }
            }
        } else {
            if (maxValues[5] > threshold_highf4a && maxValues[3] > threshold_high_f4b) {
                return "A";
            } else {
                return "Y";
            }
        }
    } else if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b &&
               maxValues[8] <= threshold_high_f1a && maxValues[0] <= threshold_high_f1b) {
        if (maxValues[4] > threshold_high_th) {
            if (maxValues[8] > threshold_high_f1a && maxValues[0] > threshold_high_f1b) {
                return "T";
            } else {
                return "X";
            }
        } else {
            if (mpu_moving) {
                return "Q";
            } else {
                return "G";
            }
        }
    } else {
        if (maxValues[4] > threshold_high_th) {
            return "Z";
        } else {
            return "L";
        }
    }
  } else if (maxValues[7] > threshold_medium_middle_upper && maxValues[2] > threshold_medium_f2b &&
            maxValues[7] <= threshold_high_middle_upper && maxValues[1] <= threshold_high_lower_middle) {
      if (maxValues[8] > threshold_high_f1a && maxValues[0] > threshold_high_f1b) {
          return "N";
      } else if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b &&
                maxValues[8] <= threshold_high_f1a && maxValues[0] <= threshold_high_f1b) {
          if (maxValues[4] > threshold_high_th) {
              return "E";
          } else if (maxValues[4] > threshold_medium_th && maxValues[4] <= threshold_high_th) {
              return "D";
          } else {
              return "C";
          }
      } else {
          if (maxValues[6] > threshold_high_f3a && maxValues[2] > threshold_high_f3b) {
              if (maxValues[7] > threshold_high_middle_upper && maxValues[1] > threshold_high_lower_middle) {
                  return "R";
              } else {
                  if (mpu_moving) {
                      return "P";
                  } else {
                      return "K";
                  }
              }
          } else {
              return "D";
          }
      }
  } else {
      if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b) {
          return "F";
      } else {
          if (maxValues[6] > threshold_high_f3a && maxValues[2] > threshold_high_f3b) {
              if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b &&
                  maxValues[7] > threshold_medium_middle_upper && maxValues[1] > threshold_medium_f2b) {
                  return "V";
              } else {
                  if (mpu_moving) {
                      return "H";
                  } else {
                      return "U";
                  }
              }
          } else {
              if (maxValues[5] > threshold_high_f4a && maxValues[3] > threshold_high_f4b) {
                  return "W";
              } else {
                  return "B";
              }
          }
      }
  }
}

