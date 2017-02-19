/* This is the RBE 1001 Template as of 12/4/12. This Template 
 is designed to run the autonomous and teleop sections of the final 
 competition. Write and test your autonomous and teleop code on your
 own, then simply copy paste your code into the appropriate section 
 and make sure the time passed to each function corresponds with the
 time in seconds that each set of code should run. IE 
 autonomous(20); will run for 20 seconds after the transmitter is 
 turned on.The code will not start until the controller is turned on
 There are print statements commented out that were used to test */

#include <PPM.h> // includes the PPM library
#include <Servo.h>

Servo leftdrive;
Servo rightdrive;
Servo leftarm;
Servo rightarm;
Servo flipper;

const int leftdrivepin = 9;
const int rightdrivepin = 8;
const int leftarmpin = 12;
const int rightarmpin = 11;
const int flipperpin = 10;
const int leftlightsensorpin = 10;
const int rightlightsensorpin = 11;

PPM ppm(2);

const int linereading = 950;
const int nonlinereading = 990;

void setup() {
  Serial.begin(9600); // starts the serial port
  // put your setup code here, to run once:
  leftdrive.attach(leftdrivepin);
  rightdrive.attach(rightdrivepin);
  leftarm.attach(leftarmpin);
  rightarm.attach(rightarmpin);
  flipper.attach(flipperpin);

}




void autonomous(unsigned long time) // function definition
{
  while(0==ppm.getChannel(1)){ // waits for controller to be turned on

  }
  unsigned long startTime=millis(); // sets start time of autonomous
  time=time * 1000;  // modifies milliseconds to seconds
  while (millis()-startTime<=time)// compares start time to time entered in the autonomous function
  {
    leftdrive.write(60);
    rightdrive.write(120);
    while(millis() > startTime + 2000) {
      linetrack();
      Serial.println("Autonoumous"); //prints Autonomous over serial (usb com port)
      delay(50); //delay to prevent spamming the serial port 
    }
    Serial.println("Autonoumous"); //prints Autonomous over serial (usb com port)
    delay(50); //delay to prevent spamming the serial port 

  }


}
void teleop(unsigned long time){ // function definition
  unsigned long startTime2=millis(); // sets start time of teleop
  time=time * 1000; // modifies milliseconds to seconds
  while(millis()-startTime2<=time) // compares start time to time entered in the teleop function
  {

    leftdrive.write(180-ppm.getChannel(3));
    rightdrive.write(ppm.getChannel(2));
    Serial.print("Light Reading ");
    Serial.println(analogRead(rightlightsensorpin));

    if (ppm.getChannel(5) < 60) {
      flipper.write(110);
    }
    else if (ppm.getChannel(5) > 120) {
      flipper.write(70);
    }
    else {
      flipper.write(90);
    }

    if (ppm.getChannel(6) < 60) {
      rightarm.write(30);
      leftarm.write(150);
    }
    else if (ppm.getChannel(6) > 120) {
      rightarm.write(110);
      leftarm.write(70);
    }
    else {
      rightarm.write(89);
      leftarm.write(91);
    }

    Serial.println("TeleOp"); //prints Teleop over serial (usb com port)
    delay(50); //delay to prevent spamming the serial port 

  }
  exit(0); // exits program
}


void loop() {

  autonomous(20); //time in seconds to run autonomous code

  teleop(180); //time in seconds that teleop code will run

}

void linetrack() {
  if (analogRead(leftlightsensorpin) < linereading) {
    leftdrive.write(180);
    rightdrive.write(180);
    delay(100);
  }else if (analogRead(rightlightsensorpin) < linereading) {
    leftdrive.write(0);
    rightdrive.write(0);
    delay(100);
  }else {
    leftdrive.write(60);
    rightdrive.write(120);
  }
}

