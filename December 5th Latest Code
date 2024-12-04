#include "I2Cdev.h"
#include "MPU6050.h"

// Create an instance of the MPU6050 sensor
MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL // Macro for defining readable acceleration output

// Constants and global variables
float values[11];
float minThreshold[] = {690, 610, 550, 600, 560, 680, 640, 600, 680};  // Threshold array to define the minimum valid reading per sensor
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
const float threshold_half_f3a = 725;
const float threshold_half_f3b = 650;
const float threshold_half_f4a = 605;
const float threshold_half_f4b = 725;

void setup(){
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

char categorizeRead(float maxValues[]){
  // The logic below categorizes the gesture by comparing sensor values against thresholds and returns the corresponding letter.

  if (maxValues[3] > threshold_half_f2a && maxValues[4] > threshold_half_f2b) {                   // Check if middle finger is over halfway bent
    if (maxValues[1] > threshold_half_f1a && maxValues[2] > threshold_half_f1b) {               //check if pointer finger is over halfway bent
      if (maxValues[0] > threshold_half_th) {                                                 //check if thumb is over halfway bent
        if (maxValues[7] > threshold_half_f4a && maxValues[8] > threshold_half_f4b) {       //check if pinky is over halfway bent
          if (maxValues[6] > threshold_high_f3b) {                                        //check if ring finger is very bent
            if (maxValues[4] > threshold_high_f2b) {                                    //check if middle finger is very bent
              return 83;  //S
            } else {                                                                    //middle finger not very bent
              return 78;  //N
            }
          }else {                                                                         //ring finger not very bent
              return 77;  //M
              }
        } else {                                                                            //pinky under halfway bent
          if (maxValues[9] > 7000) {                                                    //check if there is movement
            return 74;  //J
          } else {                                                                      //no movement
            return 73;  //I
            }
         }
      } else {                                                                                //thumb under halfway bent
        if (maxValues[7] > threshold_half_f4a && maxValues[8] > threshold_half_f4b) {       //check if pinky is over halfway bent
          if (maxValues[2] > threshold_half_f2b){                                          //check if pointer base is over halfway bent
            return 65;  //A
          } else {                                                                         //pointer base under halfway bent
            return 84;  //T
          }
        } else {                                                                            //pinky is not very bent
          return 89;  //Y
          }
        }
    } else if (maxValues[1] < threshold_half_f1a && maxValues[2] < threshold_half_f1b) {        //pointer finger is not over halfway bent, check if pointer finger is fully straight
        if (maxValues[0] > threshold_half_th) {                                               //check if thumb is over halfway bent
          return 90;  //Z
        } else {                                                                              //thumb is not very bent
          return 76;  //L
          }
    } else {                                                                                    //pointer finger is neither very bent or fully straight
      if (maxValues[0] > threshold_high_th) {                                                 //check if thumb is over halfway bent
        return 88;  //X
      } else {                                                                                //thumb is under halfway bent
        if (maxValues[10] < 5000) {                                                         //check if z acceleration is over threshold for orientation
          return 81;  //Q
          } else {
          return 71;  //G
          }
        }
      }
  } else if (maxValues[3] < threshold_half_f2a && maxValues[4] > threshold_half_f2b) {            //middle finger not over halfway bent, check if only middle finger base is bent
    if(maxValues[9] > 7000){                                                                    //check for movement
      return 80;  //P
    } else{                                                                                     //no movement
      return 75;  //K
    } 
  } else if (maxValues[3] > threshold_half_f2a && maxValues[4] < threshold_half_f2b) {            //check if only middle finger tip is over halfway bent
    if (maxValues[1] > threshold_half_f1a) {                                                    //check in pointer tip is over halfway bent
      if(maxValues[0] > threshold_high_th){                                                   //check if thumb is very bent
        return 69;  //E
      } else if (maxValues[0] < threshold_half_th){                                           //check if thumb is fully straight
        return 67;  //C
      } else{                                                                                 //thumb is neither fully bent or fully straight
        return 79;  //O
      }
    } else{                                                                                     //pointer tip under halfway bent
      return 68;  //D
    }
  } else {                                                                                        //check if middle finger is fully straight
    if (maxValues[1] > threshold_half_f1a){                                                     //check if pointer finger tip is over halfway bent
      return 70;  //F
    } else{                                                                                     //pointer finger tip is under halfway bent
      if (maxValues[5] > threshold_half_f3a) {                                                //check if ring finger tip is over halfway bent, H U V R
        if(maxValues[2] > 520 && maxValues[4] > 525){                                       //check if pointer and middle finger base is over the V threshold
        return 86;  //V
      } else if (maxValues[3] > 558){                                                       //check if middle finger tip is over the R threshold
        return 82;  //R
      } else{                                                                               //neither R nor V thresholds met
        if (maxValues[9] > 2000){                                                          //check if there is movement
          return 72;  //H
        } else {                                                                           //no movement
          return 85;  //U
          }
        } 
      } else{                                                                                 //ring finger is not very bent
        if(maxValues[7] > threshold_half_f4a){                                              //check if pinky finger tip is over halfway bent
          return 87;  //W
        } else {                                                                            //pinky tip under halfway bent
          if (maxValues[0] < threshold_half_th) {                                          //check if thumb is under halfway bent
            return 0;  //NULL
          } else{                                                                          //thumb over halfway bent
            return 66;  //B
          }
        }
      }
    }
  } 
}

void printLetter(char letter, float confidence){
  Serial.print("\n");
  Serial.print("Detected letter: ");
  Serial.print(letter);
  Serial.print("\n");
  Serial.print("Confidence: ");
  Serial.print(confidence);
  Serial.print("%");
  Serial.print("\n");
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

  int count_array[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int count = 0;
  char letter_array[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', (char)0};
  
  while (values[0] > minThreshold[0] || values[1] > minThreshold[1]|| values[3] > minThreshold[3] || values[5] > minThreshold[5] || values[7] > minThreshold[7]){
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

    for(int i =0; i<27; i++){
      if((char)categorizeRead(values)==letter_array[i]) {
        count_array[i] ++;
      }
    }
    count ++;
    delay(50);
  }

  int maxVal = count_array[0]; // Assume the first element is the maximum
  for (int i = 1; i < 27 ; i++) {
      if (count_array[i] > maxVal) {
        maxVal = count_array[i]; // Update maxVal if a larger value is found
      }
  }

  
  if ((int(maxVal)) != 0){
    // Check for specific letters
    if (count_array[7] > 0) {
      printLetter(letter_array[7], (float(count_array[7])/count)*100);
    } else if (count_array[9] > 0) {
      printLetter(letter_array[9], (float(count_array[9])/count)*100);
    } else if (count_array[15] > 0) {
      printLetter(letter_array[15], (float(count_array[15])/count)*100);
    } else if (count_array[6] > 0) {
      printLetter(letter_array[6], (float(count_array[6])/count)*100);
    } else {
        // Find the letter with the maximum count
        for (int i = 0; i < 27; i++) {
            if (count_array[i] == maxVal) {
              float percent = (float(count_array[i])/float (count))*100;
              printLetter(letter_array[i], percent);
            }
        }
    }
  } else {
    Serial.println("Waiting...");
  }

  delay(200);
}
