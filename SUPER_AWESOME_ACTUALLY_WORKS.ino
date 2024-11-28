#include "I2Cdev.h"
#include "MPU6050.h"

// Create an instance of the MPU6050 sensor
MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL // Macro for defining readable acceleration output

// Constants and global variables
const int maxReadings = 100; // Maximum number of readings per movement
float values[11];
float readingsArray[11];     // Array to store maximum readings for each sensor (9 sensors + 2 derived metrics)
int currentReading = 0;      // Counter for the current number of readings
float minThreshold[] = {640, 580, 520, 570, 530, 650, 580, 580, 650};  // Threshold array to define the minimum valid reading per sensor
float accel[3];              // Array to store acceleration differences
int16_t ax, ay, az;          // Variables to hold raw accelerometer values
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0; // Variables to store previous accelerometer readings

const float threshold_high_th = 815;
const float threshold_high_f1a = 775;
const float threshold_high_f1b = 615;
const float threshold_high_f2a = 705;
const float threshold_high_f2b = 655;
const float threshold_high_f3a = 825;
const float threshold_high_f3b = 690;
const float threshold_high_f4a = 735;
const float threshold_high_f4b = 770;

const float threshold_half_th = 775;
const float threshold_half_f1a = 655;
const float threshold_half_f1b = 575;
const float threshold_half_f2a = 605;
const float threshold_half_f2b = 610;
const float threshold_half_f3a = 735;
const float threshold_half_f3b = 650;
const float threshold_half_f4a = 605;
const float threshold_half_f4b = 725;

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

void printValues(float values[], int size) {
  Serial.print("Values: ");
  for (int i = 0; i < size; i++) {
    Serial.print("Index ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(values[i]);
    if (i < size - 1) {
      Serial.print(", ");
    }
  }
  Serial.println(); // Move to a new line after printing all values
}


  char categorizeRead(float maxValues[]) {
  // The logic below categorizes the gesture by comparing sensor values against thresholds
  // and returns the corresponding letter. Threshold variables are placeholders and should
  // be defined with actual values based on the gesture classification criteria.

  // Example logic for gesture recognition (should be customized):
  if (maxValues[3] > threshold_half_f2a && maxValues[4] > threshold_half_f2b) {
    // Check if middle finger is over halfway bent
    if (maxValues[1] > threshold_half_f1a && maxValues[2] > threshold_half_f1b) {
      //check if pointer finger is over halfway bent
      if (maxValues[0] > threshold_half_th) {
        //check if thumb is over halfway bent
        if (maxValues[7] > threshold_half_f4a && maxValues[8] > threshold_half_f4b) {
          //check if pinky is over halfway bent
          if (maxValues[5] > threshold_high_f3a && maxValues[6] > threshold_high_f3b) {
            //check if ring finger is very bent
            if (maxValues[4] > threshold_high_f2b) {
              //check if middle finger is very bent
              Serial.print("S");
              return 83;
            } else {
              //middle finger not very bent
              Serial.print("N");
              return 78;
            }
          }else {
              //ring finger not very bent
              Serial.print("M");
              return 77;
              }
        } else {
          //pinky under halfway bent
          if (maxValues[9] > 7000) {
            //check if there is movement
            Serial.print("J");
            return 74;
          } else {
            //no movement
            Serial.print("I");
            return 73;
            }
         }
      } else {
        //thumb under halfway bent
        if (maxValues[7] > threshold_half_f4a && maxValues[8] > threshold_half_f4b) {
          if (maxValues[2] > threshold_half_f2b){
            //check if pinky is over halfway bent
            Serial.print("A");
            return 65;
          } else {
            Serial.print("T");
            return 84;
          }
        } else {
          //pinky is not very bent
          Serial.print("Y");
          return 89;
          }
        }
    } else if (maxValues[1] < threshold_half_f1a && maxValues[2] < threshold_half_f1b) {                      //double check this fully straight logic
      //pointer finger is not over halfway bent, check if pointer finger is fully straight
        if (maxValues[0] > threshold_half_th) {
          //check if thumb is over halfway bent
          Serial.print("Z");
          return 90;
        } else {
          //thumb is not very bent
          Serial.print("L");
          return 76;
          }
    } else {
      //pointer finger is neither very bent or fully straight
      if (maxValues[0] > threshold_high_th) {
        //check if thumb is over halfway bent
        Serial.print("X");
        return 88;
      } else {
        //thumb is under halfway bent
        if (maxValues[10] > -5000) {
          //check if z acceleration is over threshold for orientation
          Serial.print("Q");
          return 81;
          } else {
          Serial.print("G");
          return 71;
          }
        }
      }
  } else if (maxValues[3] < threshold_half_f2a && maxValues[4] > threshold_half_f2b) {
    //middle finger not over halfway bent, check if only middle finger base is bent
      //check if ring finger is over halfway bent
    if(maxValues[9] > 7000){
      //check for movement
      Serial.print("P");
      return 80;
    } else{
      //no movement
      Serial.print("K");
      return 75;
    } 
  } else if (maxValues[3] > threshold_half_f2a && maxValues[4] < threshold_half_f2b) {
    //check if only middle finger tip is over halfway bent
    if (maxValues[1] > threshold_half_f1a) {
      if(maxValues[0] > threshold_high_th){
        //check if thumb is very bent
        Serial.print("E");
        return 69;
      } else if (maxValues[0] < threshold_half_th){
        //check if thumb is fully straight
        Serial.print("C");
        return 67;
      } else{
        //thumb is neither fully bent or fully straight
        Serial.print("O");
        return 79;
      }
    } else{
      //ring finger under halfway bent
      Serial.print("D");
      return 68;
    }
  } else {
    //check if middle finger is fully straight
    if (maxValues[5] > threshold_half_f3a && maxValues[6] > threshold_half_f3b){
      //check if ring finger is over halfway bent
    }else{
      //ring finger not very bent
    }
    if (maxValues[1] > threshold_half_f1a){
      //check if pointer finger tip is over halfway bent
      Serial.print("F");
      return 70;
    } else{
      //pointer finger is mostly straight
      if (maxValues[5] > threshold_half_f3a) {          //this will be huge problem 
        //check if ring finger is over halfway bent, H U V R
        if(maxValues[2] > 520 && maxValues[4] > 525){
        //check if pointer and middle finger base is over the V threshold
        Serial.print("V");
        return 86;
      } else if (maxValues[3] > 558){
        //check if middle finger tip is over the R threshold
        Serial.print("R");
        return 82;
      } else{
        //neither R nor V thresholds met
        if (maxValues[9] > 2000){
          //check if there is movement
          Serial.print("H");
          return 72;
        } else {
          //no movement
          Serial.print("U");
          return 85;
          }
        } 
      } else{
        //ring finger is not very bent
        if(maxValues[7] > threshold_half_f4a){
          //check if pinky finger is more than halfway closed
          Serial.print("W");
          return 87;
        } else {
          if (maxValues[0] < threshold_half_th) {
            Serial.print("NULL");
            return 0;
          } else{
            Serial.print("B");
            return 66;
          }
        }
      }
    }
  } 
}

void loop(){
  values[0] = analogRead(A11);    //thumb
  values[1] = analogRead(A8);     //pointer tip
  values[2] = analogRead(A15);    //pointer base
  values[3] = analogRead(A7);     //middle tip
  values[4] = analogRead(A14);    //middle base
  values[5] = analogRead(A10);    //ring tip
  values[6] = analogRead(A13);    //ring base
  values[7] = analogRead(A9);     //pinky tip
  values[8] = analogRead(A12);    //pinky base
  
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate the difference between current and previous readings
  int16_t diff_ax = ax - prev_ax;
  int16_t diff_ay = ay - prev_ay;
  int16_t diff_az = az - prev_az;
  float accel2 = sqrt((float)diff_ax * diff_ax + (float)diff_ay * diff_ay + (float)diff_az * diff_az);
  values[9] = accel2;
  values[10] = diff_az;
  
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  printValues(values, 11);

  int detected = categorizeRead(values);

  char detectedLetter = (char)detected;
  
  Serial.print("Detected Letter: ");
  Serial.println(detectedLetter); // Output detected letter
  delay(250);
}
