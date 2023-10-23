#include <SPI.h>
#include <SD.h>
#include <AccelStepper.h>

// Define the stepper motor connections (change as needed)
#define MOTOR_PIN_STEP_1 2   // Connect TB6600 "PUL+" of motor 1 to this pin
#define MOTOR_PIN_DIR_1 3    // Connect TB6600 "DIR+" of motor 1 to this pin
#define MOTOR_PIN_STEP_2 4   // Connect TB6600 "PUL+" of motor 2 to this pin
#define MOTOR_PIN_DIR_2 5    // Connect TB6600 "DIR+" of motor 2 to this pin
#define MotorPin2 8 // Connect motor driver to this pin
#define MotorPin3 9 // Connect motor driver to this pin

AccelStepper stepper1(AccelStepper::DRIVER, MOTOR_PIN_STEP_1, MOTOR_PIN_DIR_1);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR_PIN_STEP_2, MOTOR_PIN_DIR_2);
int targetCount1 = 0;
int targetCount2 = 0;
int count = 0;
bool motor1Reversed = false;
bool motor2Reversed = false;
bool motor2Running = false;
bool dcMotorDone = false;

File myFile;
String fileName;

void setup() {
  // Set maximum speed and acceleration for both motors
  stepper1.setMaxSpeed(1600);   // Adjust this value as needed
  stepper1.setAcceleration(0); // Adjust this value as needed

  stepper2.setMaxSpeed(1600);   // Adjust this value as needed
  stepper2.setAcceleration(0); // Adjust this value as needed

  // Set the initial direction (clockwise or counterclockwise) for both motors
  stepper1.setSpeed(1600); // Adjust this value and direction as needed
  stepper2.setSpeed(-1600); // Adjust this value and direction as needed

  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  dcMotorDone = false; // เริ่มต้นเป็น false
  Serial.begin(9600);
  
    while (!Serial) {
  }

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
  Serial.println("Enter ID: ");

  while (!Serial.available()) {
    // Wait for user input from the Serial Monitor
  }
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
          targetCount1 = line.toInt();
          Serial.println("targetCount1 = " + String(x));
        } else if (i == 3) {
          targetCount2 = line.toInt();
          Serial.println("targetCount2 = " + String(y));
        }
      }

      myFile.close();
    } else {
      Serial.println("Error opening file");
    }
}

void loop() {
  
  unsigned long startTime = millis();  // Start time for Motor 1 rotation
  unsigned long motor1Duration = targetCount1 * 10; // Calculate the time in milliseconds

  while (millis() - startTime < motor1Duration) {
    stepper1.runSpeed();
  }
  stepper1.setSpeed(0); // Stop Motor 1
  delay(200);  // Delay for 2 seconds

  startTime = millis();  // Start time for Motor 2 rotation
  unsigned long motor2Duration = targetCount2 * 10; // Calculate the time in milliseconds

  while (millis() - startTime < motor2Duration) {
    stepper2.runSpeed();
  }
  stepper2.setSpeed(0); // Stop Motor 2
  delay(200);  // Delay for 2 seconds
  
  if (!dcMotorDone) {
    controlDCMotor(); // เรียกใช้งาน controlDCMotor() ถ้ายังไม่เสร็จสิ้น
  }
  
  if (!motor2Reversed) {
    stepper2.setSpeed(1600);
    stepper2.runSpeed();
    motor2Reversed = true;
    delay(200);
  }
  else {
    stepper2.setSpeed(0);
    motor2Reversed = false;
    delay(200);
  }

  if (!motor1Reversed) {
    stepper1.setSpeed(-1600);
    stepper1.runSpeed();
    motor1Reversed = true;
    delay(200);
  }
  else{
    stepper1.setSpeed(0);
    motor1Reversed = false;
    delay(200);
    targetCount1 = 0; // Reset target count for Motor 1
    targetCount2 = 0; // Reset target count for Motor 2
    dcMotorDone = true; // เมื่อทุกอย่างเสร็จสิ้นเรียบร้อยแล้วตั้งค่า dcMotorDone เป็น true
    delay(200);
    setup(); // เรียกใช้งานฟังก์ชัน setup() เพื่อรีเซ็ตการตั้งค่าทั้งหมดและเริ่มโปรแกรมใหม่
  }
}
void controlDCMotor() {
  digitalWrite(MotorPin2, HIGH); // สั่งงานให้โมดูลขับมอเตอร์จ่ายไฟ ออกขา OUT3
  digitalWrite(MotorPin3, LOW); // สั่งงานให้ขา OUT4 เป็นขารับไฟจากขา OUT3
  delay(3500);
  digitalWrite(MotorPin2, LOW); // สั่งงานให้ขา OUT3 หยุดจ่ายไฟ
  digitalWrite(MotorPin3, LOW); // สั่งงานให้ขา OUT4 หยุดจ่ายไฟ
  delay(100);
  digitalWrite(MotorPin2, LOW); // สั่งงานให้ขา OUT3 เป็นขารับไฟจากขา OUT4
  digitalWrite(MotorPin3, HIGH); // สั่งงานให้โมดูลขับมอเตอร์จ่ายไฟ ออกขา OUT4
  delay(3500);
  digitalWrite(MotorPin2, LOW); // สั่งงานให้ขา OUT3 หยุดจ่ายไฟ
  digitalWrite(MotorPin3, LOW); // สั่งงานให้ขา OUT4 หยุดจ่ายไฟ
  
  dcMotorDone = true; // ตั้งค่าเป็น true เมื่อ DC Motor ทำงานเสร็จสิ้น
}
