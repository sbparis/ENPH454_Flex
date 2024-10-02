 void setup() {
  Serial.begin(9600);
  pinMode (A0,INPUT); pinMode (A1,INPUT); pinMode (A2,INPUT); pinMode (A3,INPUT); pinMode (A4,INPUT);
  pinMode (A5,INPUT); pinMode (A6,INPUT); pinMode (A7,INPUT); pinMode (A8,INPUT); pinMode (A9,INPUT);
  pinMode (A10,INPUT);

  //thumb: 0,1; index: 2,3; middle: 4,5; ring: 6,7; pinky: 8,9; gyroscope: 10
  //a sensor is closer to base of finger, b sensor is closer to top of finger
  f1a= analogRead(A0); f1b= analogRead(A1); f2a = analogRead(A2); f2b = analogRead(A3); f3a = analogRead(A4); f3b = analogRead(A5);
  f4a = analogRead(A6); f4b = analogRead(A7); f5a = analogRead(A8); f5b = analogRead(A9);
  palm = analogRead(A10)


}

void loop() {
  // put your main code here, to run repeatedly:
  fopen = []; fclose = []
  
}
