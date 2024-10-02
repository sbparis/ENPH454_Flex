 void setup() {
  Serial.begin(9600);
  pinMode (A0,INPUT); pinMode (A1,INPUT); pinMode (A2,INPUT); pinMode (A3,INPUT); pinMode (A4,INPUT);
  pinMode (A5,INPUT); pinMode (A6,INPUT); pinMode (A7,INPUT); pinMode (A8,INPUT); pinMode (A9,INPUT);
  pinMode (A10,INPUT); pinMode (A11,INPUT);

  //thumb: 0,1; index: 2,3; middle: 4,5; ring: 6,7; pinky: 8,9; gyroscope: 10
  //a sensor is closer to base of finger, b sensor is closer to top of finger
  int f1a= analogRead(A0), f1b= analogRead(A1), f2a = analogRead(A2), f2b = analogRead(A3), f3a = analogRead(A4), f3b = analogRead(A5),
  f4a = analogRead(A6), f4b = analogRead(A7), f5a = analogRead(A8), f5b = analogRead(A9),
  palm = analogRead(A10);

   //button
   int button = digitalRead(A11);

}

void loop() {
  // put your main code here, to run repeatedly:

 if (button = True){
  break;
 }
 
 int fopen = 10, fclose = 1013;

 char letter = '\0';

 if (f3a<=fopen && f3b<=fopen){   //B,F,H,U,V,W
  if (f2b>=fopen){       //F
   letter = 'F';
  }
  else if (f4b<=fopen){   //B, W
   if (f5a <= fopen){  //B
    letter = 'B'
   }
   else {   //W
    letter = 'W'
   }
  }
  else {   //H, U, V
   
  }
  
}
