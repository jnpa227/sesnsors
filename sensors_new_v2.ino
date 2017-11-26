#include <Servo.h>
#include <Stepper.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

Stepper m0(360, 10, 11, 12, 13);

int diskcount = 0;
int range = 15;

int vInput[100]; //Voltage read array
int vPass[4]; // Averages for passes


double vAvg;
double diskAvg = 0;

// All disk values are +/- 15

int diskClear = 500;
int diskPaper = 652;
int diskCloth = 603;
int diskSandPaper = 223;
int diskAluminum = 526;
int diskSteel = 275;

void setup() {
  
  // put your setup code here, to run once:
  servo0.attach(0);
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  
  //rgb
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);

  //stepper motor
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  m0.setSpeed(60);

}

void loop() {

  servo0.write(90);
  servo1.write(0); // clear disk
  servo2.write(30); // paper disk
  servo3.write(0); // cloth
  servo4.write(30); // sand paper
  servo5.write(0); // aluminum
  servo6.write(30); // steel

  //Make sure that door is closed before running this code.
  
  

  int stepNumber = 220;

  if(diskcount < 7) {
    diskAvg = 0;
    // Drop a single disk for sensing
    servo0.write(180);
    delay(100);
    servo0.write(100);

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
   
    if((diskAvg >= (diskClear-range)) and (diskAvg <= (diskClear+range))) {
      servo1.write(30);
    } else if((diskAvg >= (diskPaper-range)) and (diskAvg <= (diskPaper+range))) {
      servo2.write(0);
    } else if((diskAvg >= (diskCloth-range)) and (diskAvg <= (diskCloth+range))) {
      servo3.write(30);
    } else if((diskAvg >= (diskSandPaper-range)) and (diskAvg <= (diskSandPaper+range))) {
      servo4.write(0);
    } else if((diskAvg >= (diskAluminum-range)) and (diskAvg <= (diskAluminum+range))) {
      servo5.write(30);
    } else if((diskAvg >= (diskSteel-range)) and (diskAvg <= (diskSteel+range))) {
      servo6.write(0);
    }

    delay(500);

    // Drop disks

    m0.step(-stepNumber);
    m0.step(stepNumber);
    for(int i = 0; i < 15; i++) {
      m0.step(10);
      delay(200);
     }

    delay(5000);

    // Close all gates
//    servo0.write(32);
//    servo1.write(0);
//    servo2.write(30);
//    servo3.write(0);
//    servo4.write(30);
//    servo5.write(0);
//    servo6.write(30);
    
    diskcount++;
  }
}
