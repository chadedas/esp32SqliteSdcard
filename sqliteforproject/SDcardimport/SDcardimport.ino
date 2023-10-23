#include <SPI.h>
#include <SD.h>

#include <AccelStepper.h>

// Define the stepper motor connections (change as needed)
#define MOTOR_PIN_STEP_1 2  // Connect TB6600 "PUL+" of motor 1 to this pin
#define MOTOR_PIN_DIR_1 3   // Connect TB6600 "DIR+" of motor 1 to this pin
#define MOTOR_PIN_STEP_2 4  // Connect TB6600 "PUL+" of motor 2 to this pin
#define MOTOR_PIN_DIR_2 5   // Connect TB6600 "DIR+" of motor 2 to this pin
#define MotorPin2 8         // Connect motor driver to this pin
#define MotorPin3 9         // Connect motor driver to this pin

AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_PIN_STEP_1, MOTOR_PIN_DIR_1);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR_PIN_STEP_2, MOTOR_PIN_DIR_2);
int targetCount1 = 0;
int targetCount2 = 0;
int x = 0;
int y = 0;
int count = 0;
bool motor1Reversed = false;
bool motor2Reversed = false;
bool motor2Running = false;
bool dcMotorDone = false;

File myFile;
String fileName;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");

  // Set maximum speed and acceleration for both motors
  stepper1.setMaxSpeed(1600);   // Adjust this value as needed
  stepper1.setAcceleration(0);  // Adjust this value as needed

  stepper2.setMaxSpeed(1600);   // Adjust this value as needed
  stepper2.setAcceleration(0);  // Adjust this value as needed

  // Set the initial direction (clockwise or counterclockwise) for both motors
  stepper1.setSpeed(1600);   // Adjust this value and direction as needed
  stepper2.setSpeed(-1600);  // Adjust this value and direction as needed

  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  dcMotorDone = false;  // เริ่มต้นเป็น false
  Serial.begin(9600);

  Serial.println("Enter ID : ");
}

void loop() {

  if (Serial.available() > 0) {
    fileName = Serial.readStringUntil('\n');


    myFile = SD.open((String(fileName) + "/" + String(fileName) + ".txt").c_str(), FILE_READ);
    if (myFile) {
      for (int i = 1; i <= 3; i++) {
        String line = myFile.readStringUntil('\n');
        line.trim();
        if (i == 1) {
          count = line.toInt();
          Serial.println("count = " + String(count));
        } else if (i == 2) {
          x = line.toInt();
          Serial.println("x = " + String(x));
        } else if (i == 3) {
          y = line.toInt();
          Serial.println("y = " + String(y));
        }
      }
      myFile.close();
    } else {
      Serial.println("Error opening file");
    }
  }
}
