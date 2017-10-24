#include <Servo.h>
#include<Stepper.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

Stepper m0(360, 10, 11, 12, 13);

int diskcount = 0;

int vInput[100]; //Voltage read array
int vPass[4]; // Averages for passes
//int vAvg[5]; // Average for disk

double vAvg;
double diskAvg = 0;

// All disk values are +/- 5

int diskClear = 265;
int diskPaper = 273;
int diskCloth = 143;
int diskSandPaper = 46;
int diskAluminum = 105;
int diskSteel = 48;

void setup() {

  // this will break servo motors
  //Serial.begin(9600);
  
  // put your setup code here, to run once:
  servo0.attach(0);
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  
  //rgb
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  //servos
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  m0.setSpeed(70);
}

void loop() {

    servo0.write(32);
  servo1.write(0);
  servo2.write(30);
  servo3.write(0);
  servo4.write(30);
  servo5.write(0);
  servo6.write(30);

  //Make sure that door is closed before running this code.
  
  diskAvg = 0;

  int stepNumber = 170;

  if(diskcount < 7) {

    // Sense
    
    for(int j = 0; j < 5; j++) {
      vAvg = 0;
      for(int i = 0; i < 100; i++) {
        int voltage = analogRead(0);
        vAvg += voltage;
        delay(5);
      }
      vAvg /= 100;
      diskAvg += vAvg;
    }
    diskAvg /= 5;

    
   // Separate

   // Positive is counter clock wise
   
    if((diskAvg >= diskClear-10) || (diskAvg <= diskClear+10)) {
      servo1.write(30);
    } else if((diskAvg >= diskPaper-10) || (diskAvg <= diskPaper+10)) {
      servo2.write(0);
    } else if((diskAvg >= diskCloth-10) || (diskAvg <= diskCloth+10)) {
      servo3.write(30);
    } else if((diskAvg >= diskSandPaper-10) || (diskAvg <= diskSandPaper+10)) {
      servo4.write(0);
    } else if((diskAvg >= diskAluminum-10) || (diskAvg <= diskAluminum+10)) {
      servo5.write(30);
    } else if((diskAvg >= diskSteel-10) || (diskAvg <= diskSteel+10)) {
      servo6.write(0);
    }

    delay(500);

    // Drop disks

    m0.step(-stepNumber);
    m0.step(stepNumber);
    for(int i = 0; i < 5; i++) {
      m0.step(10);
      delay(200);
    }

    delay(5000);


    // Close all gates
    servo0.write(32);
  servo1.write(0);
  servo2.write(30);
  servo3.write(0);
  servo4.write(30);
  servo5.write(0);
  servo6.write(30);
    
    // Paddle
    servo0.write(0);
    delay(100);
    servo0.write(32);
    
    diskcount++;
  }
}
