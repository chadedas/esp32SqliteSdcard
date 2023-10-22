    /*
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
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <SPI.h>
#include <FS.h>
#include "SD.h"

// ฟังก์ชั่น callback สำหรับเรียกข้อมูล Sqlite มาไว้ในพารามิเตอร์
const char *data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;


  int *axisX = ((int **)data)[0];
  int *axisY = ((int **)data)[1];
  int *count = ((int **)data)[2];

  for (i = 0; i < argc; i++) {
    //Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    if (strcmp(azColName[i], "axisX") == 0) {
      if (argv[i] != NULL) {
        *axisX = atoi(argv[i]);
      }
    }
    if (strcmp(azColName[i], "axisY") == 0) {
      if (argv[i] != NULL) {
        *axisY = atoi(argv[i]);
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
// ฟังก์ชั่นเปิดฐานข้อมูล
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

// ฟังก์ชั่นสำหรับประมวลผลคำสั่ง SQL และเรียกใช้ callback
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
void setup() {
  Serial.begin(115200);
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
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int axisX = -1;
    int axisY = -1;
    int count = -1;

    int *data[] = {&axisX, &axisY, &count};

    // ดึงค่า axisX จากฐานข้อมูล
    String sqlX = "SELECT axisX FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlX.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for axisX.");
    }

    // ดึงค่า axisY จากฐานข้อมูล
    String sqlY = "SELECT axisY FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlY.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for axisY.");
    }

    // ดึงค่า count จากฐานข้อมูล
    String sqlCount = "SELECT count FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlCount.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      Serial.println("Error executing SQL for count.");
    }

    if (axisX >= 0 && axisY >= 0 && count >= 0) {
      int X = 3;
      int Y = 5;

      // เปรียบเทียบค่า axisX, axisY และ count
      if (axisX >= X && axisY >= Y && count > 0) {
        Serial.print(input + ": axisX = " + axisX + ", axisY = " + axisY + ", count = " + count + "\n");
        Serial.println("Condition is met!");
      } else {
        Serial.print(input + ": axisX = " + axisX + ", axisY = " + axisY + ", count = " + count + "\n");
        Serial.println("Condition is not met!");
      }
    } else {
      Serial.println(input + " not found in the database.");
    }
  }
}



