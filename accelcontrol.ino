#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

#define OUTPUT_READABLE_ACCEL

float maxaccel;
float prevaccel;
float accel2;
float accel[3];
int16_t ax, ay, az;
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0; // Previous accelerometer values

void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin(); 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(38400);

  mpu.initialize();
}

void loop() {
  // Read only accelerometer data
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate differences between current and previous readings
  int16_t diff_ax = ax - prev_ax;
  int16_t diff_ay = ay - prev_ay;
  int16_t diff_az = az - prev_az;

  accel[0] = diff_ax;
  accel[1] = diff_ay;
  accel[2] = diff_az;

  // Print the differences
  Serial.print("Difference accel:\t");
  Serial.print(diff_ax); Serial.print("\t");
  Serial.print(diff_ay); Serial.print("\t");
  Serial.println(diff_az);

  accel2 = sqrt((accel[0]*accel[0]) + (accel[1]*accel[1]) + (accel[2]*accel[2]));

  if (accel2 > prevaccel){
    maxaccel = accel2;
  }

  prevaccel = accel2;

  // Update previous values for the next loop
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  Serial.print("Integral accel: ");
  Serial.println(maxaccel);

  delay(100); // Optional: Add a delay to slow down the loop
}
