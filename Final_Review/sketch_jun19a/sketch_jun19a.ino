#include <Servo.h>

void UpDown();
void LeftRight();

Servo servo1;
Servo servo2;
void setup() 
{
  servo1.attach(11);
  servo2.attach(10); 
  
  servo1.write(90); 
  servo2.write(90); 
}

void loop(){
  
 int sensorTop = analogRead(A0);
 int sensorBottom = analogRead(A1);
 int sensorLeft = analogRead(A3);
 int sensorRight = analogRead(A4);

 int avgT=(sensorTop);
 int avgB=(sensorBottom);
 int avgL=(sensorLeft);
 int avgR=(sensorRight);


  if (avgT > avgB)
  {
  	 UpDown(sensorTop, sensorBottom);
  }
  if(avgT < avgB)
  {
    UpDown(sensorTop, sensorBottom);
  }
  if(avgL > avgR) 
 	{
 	 LeftRight(sensorLeft, sensorRight);
    }
  if(avgL < avgR) 
 	{
 	 LeftRight(sensorLeft, sensorRight);
    }
 delay(3); 
}
void UpDown(int avgT, int avgB){
  int pos1= servo1.read();
    
  if(avgT < avgB){
     pos1 = --pos1; 
    }
  	 else
     {
      pos1 = ++pos1;
     }
  servo1.write(pos1);
 }
void LeftRight(int avgL, int avgR){
  int pos2= servo2.read();
  if(avgL < avgR)
   { 
    pos2 = --pos2;
   }
  	else
    {
     pos2 = pos2 + 1;
    }
  servo2.write(pos2);
}
