#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL

const int maxReadings = 100; // Define max number of readings per movement
float readingsArray[11]; // 2D array for 9 sensors and maxReadings rows
int currentReading = 0; // Track the current number of readings
float minThreshold[9] = {}
float accel[3];
int16_t ax, ay, az;
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0;

void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin(); 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(9600);
  // Set the pin modes for analog inputs
  pinMode(A15, INPUT); pinMode(A14, INPUT); pinMode(A13, INPUT); pinMode(A12, INPUT); 
  pinMode(A11, INPUT); pinMode(A9, INPUT); pinMode(A10, INPUT); pinMode(A7, INPUT); 
  pinMode(A8, INPUT); 

  mpu.initialize();
}

void loop() {
  float* readings = ReadVoltages();
  if (readings != nullptr) { // Valid readings returned
    for (int i = 0; i < 9; i++) {
      if (readings[i] > readingsArray[i]) {
        readingsArray[i] = readings[i];
      }; // Store each sensor reading
    }
    accele = sqrt((accel[1]*accel[1]) + (accel[2]*accel[2]) + (accel[3]*accel[3]));
    if (accel > readings[9]) {
        readings[9] = accele;
    }
    if (accel[2] > readings[10]){
      readings[10] = accel[2];
    }
    currentReading++;
  } else if (currentReading > 0) { // If glove was in motion and now at rest
    char detectedLetter = categorizeRead(readingsArray); // Categorize the movement
    Serial.print("Detected Letter: ");
    Serial.println(detectedLetter);
  for (int i = 0; i < 10; i++) {
    Serial.print("readingsArray[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(readingsArray[i]);
  }
}    
    currentReading = 0; // Reset for the next movement
    memset(readingsArray, 0, sizeof(readingsArray));
  } // Update to indicate motion
  delay(100); // Wait 500ms before updating again
}

// Function to read analog pins and return array of voltages
float* ReadVoltages() {
  static float values[9];
  bool ret = true;
  
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

  mpu.getAcceleration(&ax, &ay, &az);

  int16_t diff_ax = ax - prev_ax;
  int16_t diff_ay = ay - prev_ay;
  int16_t diff_az = az - prev_az;

  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  // Check for any invalid readings
  for (int i = 0; i < 9; i++) {
    if (values[i] < minThreshold[i]) {
      ret = false;
    }
  }
  if(ret){
    accel[0] = diff_ax;
    accel[1] = diff_ay;
    accel[2] = diff_az;
    return values;
  }
  return nullptr;
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
                if (maxValues[9] > 5000) {
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
            if (maxValues[10] > MAXIMUM Y ACCELERATION]) {
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
                  if (maxValues[9] > 6500) {
                      return "P";
                  } else {
                      return "K";
                  }
              }
          } else {
              return "D";
          }
      }
  } else if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b) {
          return "F";
      } else {
          if (maxValues[6] > threshold_high_f3a && maxValues[2] > threshold_high_f3b) {
              if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b &&
                  maxValues[7] > threshold_medium_middle_upper && maxValues[1] > threshold_medium_f2b) {
                  return "V";
              } else {
                  if (maxValues[9] > 3000) {
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
  } else {
    return NULL;
  }
}
