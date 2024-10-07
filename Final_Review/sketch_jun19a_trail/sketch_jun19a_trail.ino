#include <Servo.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

#define TIME_HEADER  "T"   
#define TIME_REQUEST  7  

void UpDown();
void LeftRight();

Servo servo1;
Servo servo2;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() 
{
  lcd.begin(16,2); 
  lcd.print("servo1 "); 
  lcd.setCursor(0,1);
  lcd.print("servo2 ");

  servo1.attach(7);
  servo2.attach(10); 
  
  servo1.write(90); 
  servo2.write(90); 

  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
}

void loop(){

 int sensorTop = analogRead(A0);
 int sensorBottom = analogRead(A1);
 int sensorLeft = analogRead(A3);
 int sensorRight = analogRead(A4);

 int avgT=(sensorTop+sensorBottom)/2;
 int avgB=(sensorLeft+sensorRight)/2;
 int avgL=(sensorTop+sensorLeft)/2;
 int avgR=(sensorBottom+sensorRight)/2;


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
  if (avgT < 200 || avgB < 200 || avgL < 200 || avgR < 200){
    if (Serial.available()) {
      processSyncMessage();
    }
    if (timeStatus()!= timeNotSet) {
      digitalClockDisplay();  
    }
  }
 delay(3); 
}
void UpDown(int avgT, int avgB){
  int pos1= servo1.read();
  int c_val = 1024/180;
    
  if(avgT < avgB){
     pos1 = pos1-c_val; 
    }
  	 else
     {
      pos1 = pos1+c_val;
     }
  servo1.write(pos1);
  lcd.setCursor(12,0);
 lcd.print(pos1);
 }
void LeftRight(int avgL, int avgR){
  int pos2= servo2.read();
  int c_val = 1024/180;
  if(avgL < avgR)
   { 
    pos2 = pos2-c_val;
   }
  	else
    {
     pos2 = pos2 + c_val;
    }
  servo2.write(pos2);
  lcd.setCursor(12,1);
 lcd.print(pos2);
}
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1687241311; 
  unsigned long START_TIME = 1687217400;
  int count = 0;

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
     if (pctime == START_TIME){
      int pos1= servo1.read();
      pos1 = 15*count;
    }else{
      START_TIME += 3600;
      count++; 
  }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}