#include "I2Cdev.h"
#include "MPU6050.h"

// Create an instance of the MPU6050 sensor
MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL // Macro for defining readable acceleration output

// Constants and global variables
const int maxReadings = 100; // Maximum number of readings per movement
float readingsArray[11];     // Array to store maximum readings for each sensor (9 sensors + 2 derived metrics)
int currentReading = 0;      // Counter for the current number of readings
float minThreshold[9] = {};  // Threshold array to define the minimum valid reading per sensor
float accel[3];              // Array to store acceleration differences
int16_t ax, ay, az;          // Variables to hold raw accelerometer values
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0; // Variables to store previous accelerometer readings

const float threshold_high_th = 815;
const float threshold_high_f1a = 764;
const float threshold_high_f1b = 633;
const float threshold_high_f2a = 845;
const float threshold_high_f2b = 710;
const float threshold_high_f3a = 865;
const float threshold_high_f3b = 700;
const float threshold_high_f4a = 780;
const float threshold_high_f4b = 790;

const float threshold_medium_th = 784;
const float threshold_medium_f1a = 683;
const float threshold_medium_f1b = 590;
const float threshold_medium_f2a = 785;
const float threshold_medium_f2b = 640;
const float threshold_medium_f3a = 750;
const float threshold_medium_f3b = 575;
const float threshold_medium_f4a = 666;
const float threshold_medium_f4b = 670;

void setup() {
  // Initialize I2C communication
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin(); 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(9600); // Start serial communication at 9600 baud

  // Set the pin modes for analog inputs
  pinMode(A15, INPUT); pinMode(A14, INPUT); pinMode(A13, INPUT); pinMode(A12, INPUT); 
  pinMode(A11, INPUT); pinMode(A9, INPUT); pinMode(A10, INPUT); pinMode(A7, INPUT); 
  pinMode(A8, INPUT);

  mpu.initialize(); // Initialize the MPU6050 sensor
}

void loop() {
  float* readings = ReadVoltages(); // Fetch sensor voltages
  if (readings != nullptr) { // Check if valid readings are returned
    for (int i = 0; i < 9; i++) {
      if (readings[i] > readingsArray[i]) {
        readingsArray[i] = readings[i]; // Update maximum reading for each sensor
      }
    }

    // Calculate the overall acceleration magnitude
    float accele = sqrt((accel[0]*accel[0]) + (accel[1]*accel[1]) + (accel[2]*accel[2]));

    if (accele > readings[9]) {
      readings[9] = accele; // Update maximum acceleration magnitude
    }

    if (accel[2] > readings[10]) {
      readings[10] = accel[2]; // Update maximum Z-axis acceleration
    }

    currentReading++; // Increment the reading counter
  } else if (currentReading > 0) { // Check if glove was in motion and now is at rest
    char detectedLetter = categorizeRead(readingsArray); // Categorize the gesture
    Serial.print("Detected Letter: ");
    Serial.println(detectedLetter); // Output detected letter

    // Print all sensor readings for debugging
    for (int i = 0; i < 10; i++) {
      Serial.print("readingsArray[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(readingsArray[i]);
    }

    // Reset variables for the next gesture
    currentReading = 0;
    memset(readingsArray, 0, sizeof(readingsArray));
  }

  delay(100); // Wait 100ms before updating again
}

// Function to read analog pins and return an array of voltages
float* ReadVoltages() {
  static float values[9]; // Array to store analog readings
  bool ret = true;        // Flag to check validity of readings
  
  // Read analog values from the sensors
  values[0] = analogRead(A15);
  values[1] = analogRead(A14);
  values[2] = analogRead(A13);
  values[3] = analogRead(A12);
  values[4] = analogRead(A11);
  values[5] = analogRead(A9);
  values[6] = analogRead(A10);
  values[7] = analogRead(A7);
  values[8] = analogRead(A8);

  // Read acceleration data from the MPU6050
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate the difference between current and previous readings
  int16_t diff_ax = ax - prev_ax;
  int16_t diff_ay = ay - prev_ay;
  int16_t diff_az = az - prev_az;
  int16_t accel2 = sqrt((diff_ax * diff_ax) + (diff_ay* diff_ay) + (diff_az * diff_az));
  values[9] = accel2;
  values[10] = diff_az;
  // Update previous readings
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;
  

  // Check for invalid readings below thresholds
  for (int i = 0; i < 9; i++) {
    if (values[i] < minThreshold[i]) {
      ret = false;
    }
  }

  // If all readings are valid, update acceleration differences and return values
  if (ret) {
    accel[0] = diff_ax;
    accel[1] = diff_ay;
    accel[2] = diff_az;
    return values;
  }

  return nullptr; // Return null if invalid readings are found
}

// Function to categorize the movement into a letter based on sensor readings
char categorizeRead(float maxValues[]) {
  // The logic below categorizes the gesture by comparing sensor values against thresholds
  // and returns the corresponding letter. Threshold variables are placeholders and should
  // be defined with actual values based on the gesture classification criteria.

  // Example logic for gesture recognition (should be customized):
  if (maxValues[7] > threshold_high_f2a && maxValues[1] > threshold_high_f2b) {
    // Check if middle finger is bent enough (high threshold)
    if (maxValues[8] > threshold_high_f1a && maxValues[0] > threshold_high_f1b) {
        if (maxValues[4] > threshold_high_th) {
            if (maxValues[5] > threshold_high_f4a && maxValues[3] > threshold_high_f4b) {
                if (maxValues[6] > threshold_high_f3a && maxValues[2] > threshold_high_f3b) {
                  if (maxValues[7] > threshold_high_f2a && maxValues[1] > threshold_high_f2b){
                    return "S";
                  }
                  else{
                    return "N";
                  }
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
            if (maxValues[5] > threshold_high_f4a && maxValues[3] > threshold_high_f4b) {
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
            if (maxValues[10] > -5000) {
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
  } else if (maxValues[7] > threshold_medium_f2a && maxValues[2] > threshold_medium_f2b &&
            maxValues[7] <= threshold_high_f2a && maxValues[1] <= threshold_high_f2b) {
      if (maxValues[8] > threshold_medium_f1a && maxValues[0] > threshold_medium_f1b &&
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
              if (maxValues[7] > threshold_high_f2a && maxValues[1] > threshold_high_f2b) {
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
                  maxValues[7] > threshold_medium_f2a && maxValues[1] > threshold_medium_f2b) {
                  return "V";
              } else {
                  if (maxValues[9] > 4000) {
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
    return '\0';
  }
}
