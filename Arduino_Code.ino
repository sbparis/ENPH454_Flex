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
  fopen = []; fclose = []

  if (button = True){
  break;
 }
 
 int fopen = 10, fclose = 1013;

 char letter = '\0';

  void classifyLetter() {
    if (f3a<=fopen && f3b<=fopen){   //B,F,H,U,V,W
      if (f2b>=fopen){       //F
      letter = 'F';
      }
      else if (f4b<=fopen){   //B, W
      if (f5a <= fopen){  //B
        letter = 'B';
      }
      else {   //W
        letter = 'W';
      }
      }
      else {   //H, U, V
      
      }
      
    }else if (f3a>=fclose && f3b>=fclose){     //A, G, I, J, L, M, Q, S, T, X, Y, Z 
      if (f2a<=fopen && f2b<=fopen){         //L, Z
        if (f1a<=fopen){       //L
          letter = 'L';
        }
        else{
          letter = 'Z';
        }
      }
      else if (f2a>=fclose && f2b>=fclose){     //A, I, J, M, S, Y
        if (f1b>=fclose){      //I, J, M, S
          if (f5a<=fopen){     //I, J
            if (palm==moving){      //gyroscope movement
              letter = 'J';
            }
            else{
              letter = 'I';
            }
          }
          else{      //M,S
            if (f4a <= ____ && f4b >= ____){    //M
              letter = 'M';
            }
            else{     //S
              letter = 'S';
            }
          }
        }
        else{     //A, Y
          if (f5a<=fopen){   //Y
            letter = 'Y';
          }
          else{     //A
            letter = 'A';
          }
        }
      }
      else{       //G, Q, T, X
        if (f1a<=fopen && f1b<=fopen){    //G, Q
          if (palm ){

          }
          else{

          }
        }
        else{       //T, X
          if (f2 ){

          }
          else{

          }

        }
      }
    }else{     //C, D, E, K, N, O, P, R
      if (f2a<=fopen && f2b<=fopen){      //D, K, P, R

      }
      else if (f2a>=fclose && f2b>=fclose){   //N
        letter = 'N';

      }
      else{     //C,E,O
        if (f1a<=fopen && f1b<=fopen){    //C
          letter = 'C';
        }
        else if (f1a>=fclose && f1b>=fclose){   //E
          letter = 'E';
        } 
        else{    //O
          letter = 'O';
        }

      }


    }
  }
  printf("Letter=", "%c", 'letter');
}
}
