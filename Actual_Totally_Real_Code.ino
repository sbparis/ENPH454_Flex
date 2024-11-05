bool lastrun;

void setup() {
  Serial.begin(9600);
  // Set the pin modes for analog and digital inputs
  pinMode (A0, INPUT); pinMode (A9, INPUT); pinMode (A2, INPUT); pinMode (A3, INPUT); 
  pinMode (A4, INPUT); pinMode (A5, INPUT); pinMode (A6, INPUT); pinMode (A7, INPUT); 
  pinMode (A8, INPUT); 

void loop() {
  readings = ReadVoltages();
  if(readings != 0){
    if(lastrun = false){
      float runValues = readings;
      lastrun = true;
      count = 1;
    } else {
      runvalues.append(readings);
      count += 1
    }
  } else {
    lastrun = false;
    maxarr = maxvalues(runValues, count);
    output = categorizeRead(maxarr);
  }
  }
  delay(500);  // Wait 500ms before updating again
}

// Function to read analog pins and display live voltages
float* ReadVoltages() {
  // Read analog values from sensors
  float f1a = analogRead(A0), f2a = analogRead(A9);
  float f3a = analogRead(A2), f4a = analogRead(A3);
  float ft = analogRead(A4), f4b = analogRead(A5);
  float f3b = analogRead(A6), f2b = analogRead(A7);
  float f1b = analogRead(A8);

  if (f1a < !! || f1b < !! || f2a < !! || f2b < !! || f3a < !! || f3b < !! || f4a < !! || f4b < !! || ft < !!){
    return 0;
  } else {
    float values[] = [f1a, f1b, f2a, f2b, f3a, f3b, f4a, f4b, ft];
    return values;
  }
  
}

float Maxarr(float runValues[]){
  
}

char categorizeRead(float maxarr[]){

}
