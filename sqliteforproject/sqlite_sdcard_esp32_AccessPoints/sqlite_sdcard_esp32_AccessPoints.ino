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
    loop ทำงานซ้ำๆ และรอการป้อนข้อมูลผ่าน //Serial2 Monitor, ดึงข้อมูลจาก SQLite, เปรียบเทียบข้อมูล, และแสดงผลลัพธ์บน //Serial2 Monitor.
    */

//#include ใช้ในการเรียกใช้ไลบรารีและหัวข้อความนั้นใช้เป็นคำอธิบายในการอ้างอิงถึงโค้ดหรือผลงาน
#include <WiFi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";


String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
// callback คือฟังก์ชันที่จะถูกเรียกเมื่อรับข้อมูลจาก SQLite และเอาไว้ในพารามิเตอร์ที่ต้องการ คำอธิบายและการแปลงข้อมูลให้อยู่ในรูปแบบที่ถูกต้อง.
const char *data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;



  int *timex = ((int **)data)[0];
  int *timey = ((int **)data)[1];
  int *count = ((int **)data)[2];

  for (i = 0; i < argc; i++) {
    if (strcmp(azColName[i], "timex") == 0) {
      if (argv[i] != NULL) {
        *timex = atoi(argv[i]);
      }
    }
    if (strcmp(azColName[i], "timey") == 0) {
      if (argv[i] != NULL) {
        *timey = atoi(argv[i]);
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
    //Serial2.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
    return rc;
  } else {
    //Serial2.printf("Opened database successfully\n");
  }
  return rc;
}

char *zErrMsg = 0;

//db_exec ทำหน้าที่ส่งคำสั่ง SQL ไปยัง SQLite และตรวจสอบผลการดำเนินการ และเก็บข้อมูลผ่าน callback.
int db_exec(sqlite3 *db, const char *sql) {
  //Serial2.println(sql);
  long start = micros();
  int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    //Serial2.printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    //Serial2.printf("Operation done successfully\n");
  }
  //Serial2.print(F("Time taken:"));
  //Serial2.println(micros() - start);
  return rc;
}

sqlite3 *db2;

//setup ทำงานเมื่อเริ่มต้นโปรแกรม รวมถึงเริ่ม SPI, เริ่ม SD Card, เริ่ม SQLite และเปิดฐานข้อมูล.
void setup() {
  Serial2.begin(9600);


  // เริ่ม SQLite


  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  //Serial2.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  //Serial2.print("AP IP address: ");
  //Serial2.println(IP);
  SPI.begin();

  // เริ่ม SD Card
  SD.begin();
  sqlite3_initialize();
  server.begin();

  char *zErrMsg = 0;
  int rc;

  // เริ่ม SPI
  // เปิดฐานข้อมูล
  if (openDb("/sd/mdr512.db", &db2))
    return;
}
//loop ทำงานซ้ำๆ และรอการป้อนข้อมูลผ่าน //Serial2 Monitor, ดึงข้อมูลจาก SQLite, เปรียบเทียบข้อมูล, และแสดงผลลัพธ์บน //Serial2 Monitor.
void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                     // If a new client connects,
    //Serial2.println("New Client.");  // print a message out in the //Serial2 port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        //Serial2.write(c);            // print it out the //Serial2 monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              //Serial2.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);

            } else if (header.indexOf("GET /26/off") >= 0) {
              //Serial2.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              //Serial2.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              //Serial2.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button
            if (output26State == "off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output27State == "off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial2.println("Client disconnected.");
    //Serial2.println("");
  }
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int timex = -1;
    int timey = -1;
    int count = -1;

    int *data[] = { &timex, &timey, &count };

    // ดึงค่า timex จากฐานข้อมูล
    String sqlX = "SELECT timex FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlX.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      //Serial2.println("Error executing SQL for timex.");
    }

    // ดึงค่า timey จากฐานข้อมูล
    String sqlY = "SELECT timey FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlY.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      //Serial2.println("Error executing SQL for timey.");
    }

    // ดึงค่า count จากฐานข้อมูล
    String sqlCount = "SELECT count FROM project WHERE ID = '" + input + "'";
    if (sqlite3_exec(db2, sqlCount.c_str(), callback, data, &zErrMsg) != SQLITE_OK) {
      //Serial2.println("Error executing SQL for count.");
    }

    if (timex >= 0 && timey >= 0 && count >= 0) {
      Serial2.println(timex + " " + timey /*+ ", count = " + count + "\n"*/);

    } else {
      //Serial2.println(input + " not found in the database.");
    }
  }
}
