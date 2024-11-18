#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL

int16_t ax, ay, az;
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0; // Previous accelerometer values

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin(); 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(9600);
  mpu.initialize();
  // Set the pin modes for analog and digital inputs
  pinMode (A7, INPUT); pinMode (A8, INPUT); pinMode (A9, INPUT); pinMode (A10, INPUT); 
  pinMode (A11, INPUT); pinMode (A12, INPUT); pinMode (A13, INPUT); pinMode (A14, INPUT); 
  pinMode (A15, INPUT);
}

void loop() {
  // Call the function to display live voltages
  
  
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("Difference accel:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.println(az);
  
  
  displayVoltages();


  delay(1000);  // Wait 500ms before updating again
}

// Function to read analog pins and display live voltages
void displayVoltages() {
  // Read analog values from sensors
  float f1a = analogRead(A8), f2a = analogRead(A7);
  float f3a = analogRead(A10), f4a = analogRead(A9);
  float ft = analogRead(A11), f4b = analogRead(A12);
  float f3b = analogRead(A13), f2b = analogRead(A14);
  float f1b = analogRead(A15);

  // Display the Live readings 
  
  Serial.println("Live Voltage Readings:");
  
  Serial.print("Index Upper (f1a): "); Serial.println(f1a);
  Serial.print("Index Knuckle(f1b): "); Serial.println(f1b);
  
  Serial.print("Middle Upper (f2a): "); Serial.println(f2a);
  Serial.print("Middle Knuckle (f2b): "); Serial.println(f2b);
  

  Serial.print("Ring Upper (f3a): "); Serial.println(f3a);
  Serial.print("Ring Knuckle (f3b): "); Serial.println(f3b);
  
  Serial.print("Pinky Upper(f4a): "); Serial.println(f4a);
  Serial.print("Pinky Knuckle (f4b): "); Serial.println(f4b);
  
  Serial.print("Thumb (ft): "); Serial.println(ft);

  
  Serial.println();  // Blank line for easier reading
}
