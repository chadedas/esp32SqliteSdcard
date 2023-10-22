/*

    โปรเจค อาจารย์ ยุทธนา

    โค้ดนี้ใช้ Arduino IDE เพื่อการสื่อสารกับ SQLite ฐานข้อมูลโดยใช้ SD Card และ SPI. 
    ดาวน์โหลดไลบรารี "sqlite3.h" และ "SD.h" 
    สำหรับการใช้งานเพื่อเข้าถึงข้อมูล SQLite และอ่านและเขียนไฟล์บน SD Card 

    #include ใช้ในการเรียกใช้ไลบรารีและหัวข้อความนั้นใช้เป็นคำอธิบายในการอ้างอิงถึงโค้ดหรือผลงาน
    callback คือฟังก์ชันที่จะถูกเรียกเมื่อรับข้อมูลจาก SQLite และเอาไว้ในพารามิเตอร์ที่ต้องการ คำอธิบายและการแปลงข้อมูลให้อยู่ในรูปแบบที่ถูกต้อง.
    openDb ใช้ในการเปิดฐานข้อมูล SQLite ตามชื่อไฟล์และเปิดการเชื่อมต่อ.
    db_exec ทำหน้าที่ส่งคำสั่ง SQL ไปยัง SQLite และตรวจสอบผลการดำเนินการ และเก็บข้อมูลผ่าน callback.
    setup ทำงานเมื่อเริ่มต้นโปรแกรม รวมถึงเริ่ม SPI, เริ่ม SD Card, เริ่ม SQLite และเปิดฐานข้อมูล.
    loop ทำงานซ้ำๆ และรอการป้อนข้อมูลผ่าน Serial Monitor, ดึงข้อมูลจาก SQLite, เปรียบเทียบข้อมูล, และแสดงผลลัพธ์บน Serial Monitor.
    */

//#include ใช้ในการเรียกใช้ไลบรารีและหัวข้อความนั้นใช้เป็นคำอธิบายในการอ้างอิงถึงโค้ดหรือผลงาน
#include <AccelStepper.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <SPI.h>
#include "SD.h"

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
bool motor1Reversed = false;
bool motor2Reversed = false;
bool motor2Running = false;
bool dcMotorDone = false;

// callback คือฟังก์ชันที่จะถูกเรียกเมื่อรับข้อมูลจาก SQLite และเอาไว้ในพารามิเตอร์ที่ต้องการ คำอธิบายและการแปลงข้อมูลให้อยู่ในรูปแบบที่ถูกต้อง.
const char *data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;

  int *timeX = ((int **)data)[0];
  int *timeY = ((int **)data)[1];
  int *count = ((int **)data)[2];

  for (i = 0; i < argc; i++) {
    if (strcmp(azColName[i], "timeX") == 0) {
      if (argv[i] != NULL) {
        *timeX = atoi(argv[i]);
      }
    }
    if (strcmp(azColName[i], "timeY") == 0) {
      if (argv[i] != NULL) {
        *timeY = atoi(argv[i]);
      }
    }
    if (strcmp(azColName[i], "count") == 0) {
      if (argv[i] != NULL) {
        *count = atoi(argv[i]);
      }
    }
  }
  return 0;
}

// openDb ใช้ในการเปิดฐานข้อมูล SQLite ตามชื่อไฟล์และเปิดการเชื่อมต่อ.
int openDb(const char *filename, sqlite3 **db) {
  int rc = sqlite3_open(filename, db);
  if (rc) {
    Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
    return rc;
  } else {
    Serial.printf("Opened database successfully\n");
  }
  return rc;
}

char *zErrMsg = 0;

//db_exec ทำหน้าที่ส่งคำสั่ง SQL ไปยัง SQLite และตรวจสอบผลการดำเนินการ และเก็บข้อมูลผ่าน callback.
int db_exec(sqlite3 *db, const char *sql) {
  Serial.println(sql);
  long start = micros();
  int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    Serial.printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    Serial.printf("Operation done successfully\n");
  }
  Serial.print(F("Time taken:"));
  Serial.println(micros() - start);
  return rc;
}

sqlite3 *db2;

//setup ทำงานเมื่อเริ่มต้นโปรแกรม รวมถึงเริ่ม SPI, เริ่ม SD Card, เริ่ม SQLite และเปิดฐานข้อมูล.
void setup() {
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

  char *zErrMsg = 0;
  int rc;

  // เริ่ม SPI
  SPI.begin();

  // เริ่ม SD Card
  SD.begin();

  // เริ่ม SQLite
  sqlite3_initialize();

  // เปิดฐานข้อมูล
  if (openDb("/sd/mdr512.db", &db2))
    return;
}
//loop ทำงานซ้ำๆ และรอการป้อนข้อมูลผ่าน Serial Monitor, ดึงข้อมูลจาก SQLite, เปรียบเทียบข้อมูล, และแสดงผลลัพธ์บน Serial Monitor.
void loop() {

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Start time for Motor 1 rotation
    // Calculate the time in milliseconds

    int timeX = -1;
    int timeY = -1;
    int count = -1;

    int *data[] = { &timeX, &timeY, &count };

    // ดึงค่า timeX จากฐานข้อมูล
    String sqlX = "SELECT timeX FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlX.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for timeX.");
    }

    // ดึงค่า timeY จากฐานข้อมูล
    String sqlY = "SELECT timeY FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlY.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for timeY.");
    }

    // ดึงค่า count จากฐานข้อมูล
    String sqlCount = "SELECT count FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlCount.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for count.");
    }
    if (timeX >= 0 && timeY >= 0 && count >= 0) {
        targetCount1 = timeX
        targetCount2 = timeY

        unsigned long startTime = millis();
        unsigned long motor1Duration = targetCount1 * 10;
        unsigned long motor2Duration = targetCount2 * 10;  // Calculate the time in milliseconds

      while (millis() - startTime < motor1Duration) {
        stepper1.runSpeed();
      }
      stepper1.setSpeed(0);  // Stop Motor 1
      delay(200);            // Delay for 2 seconds

      startTime = millis();  // Start time for Motor 2 rotation
      while (millis() - startTime < motor2Duration) {
        stepper2.runSpeed();
      }
      stepper2.setSpeed(0);  // Stop Motor 2
      delay(200);            // Delay for 2 seconds
      if (!dcMotorDone) {
        controlDCMotor();  // เรียกใช้งาน controlDCMotor() ถ้ายังไม่เสร็จสิ้น
      }

      if (!motor2Reversed) {
        stepper2.setSpeed(1600);
        stepper2.runSpeed();
        motor2Reversed = true;
        delay(200);
      } else {
        stepper2.setSpeed(0);
        motor2Reversed = false;
        delay(200);
      }

      if (!motor1Reversed) {
        stepper1.setSpeed(-1600);
        stepper1.runSpeed();
        motor1Reversed = true;
        delay(200);
      } else {
        stepper1.setSpeed(0);
        motor1Reversed = false;
        delay(200);
        targetCount1 = 0;    // Reset target count for Motor 1
        targetCount2 = 0;    // Reset target count for Motor 2
        dcMotorDone = true;  // เมื่อทุกอย่างเสร็จสิ้นเรียบร้อยแล้วตั้งค่า dcMotorDone เป็น true
        delay(200);
      }
    }

    /*
    if (timeX >= 0 && timeY >= 0 && count >= 0) {
      int X = 3;
      int Y = 5;
      

      // เปรียบเทียบค่า timeX, timeY และ count
      if (timeX >= X && timeY >= Y && count > 0) {
        Serial.print(input + ": timeX = " + timeX + ", timeY = " + timeY + ", count = " + count + "\n");
        Serial.println("Condition is met!");
      } else {
        Serial.print(input + ": timeX = " + timeX + ", timeY = " + timeY + ", count = " + count + "\n");
        Serial.println("Condition is not met!");
      }
    } else {
      Serial.println(input + " not found in the database.");
    }
  }*/
  }

  void controlDCMotor() {
    digitalWrite(MotorPin2, HIGH);  // สั่งงานให้โมดูลขับมอเตอร์จ่ายไฟ ออกขา OUT3
    digitalWrite(MotorPin3, LOW);   // สั่งงานให้ขา OUT4 เป็นขารับไฟจากขา OUT3
    delay(3500);
    digitalWrite(MotorPin2, LOW);  // สั่งงานให้ขา OUT3 หยุดจ่ายไฟ
    digitalWrite(MotorPin3, LOW);  // สั่งงานให้ขา OUT4 หยุดจ่ายไฟ
    delay(100);
    digitalWrite(MotorPin2, LOW);   // สั่งงานให้ขา OUT3 เป็นขารับไฟจากขา OUT4
    digitalWrite(MotorPin3, HIGH);  // สั่งงานให้โมดูลขับมอเตอร์จ่ายไฟ ออกขา OUT4
    delay(3500);
    digitalWrite(MotorPin2, LOW);  // สั่งงานให้ขา OUT3 หยุดจ่ายไฟ
    digitalWrite(MotorPin3, LOW);  // สั่งงานให้ขา OUT4 หยุดจ่ายไฟ

    dcMotorDone = true;  // ตั้งค่าเป็น true เมื่อ DC Motor ทำงานเสร็จสิ้น
  }
