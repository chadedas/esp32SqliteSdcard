#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for the native USB port only
  }
  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    while (1)
      ;
  }
  delay(5000);
  Serial.println("SD initialization done.");
  //A-L
  for (int num1 = 65; num1 <= 76; num1++) {
    delay(100);
    //0 - 1
    for (int num2 = 0; num2 <= 1; num2++) {
      delay(100);
      //0-9
      for (int num3 = 0; num3 <= 9; num3++) {
        delay(100);
        myFile.close();
        char folderName[4];
        char filename[4];
        // 10 11
        if (num2 == 1 && num3 <= 1) {
          sprintf(folderName, "%c%d%d", char(num1), num2, num3);
          // สร้างโฟลเดอร์
          if (SD.mkdir(folderName)) {
            sprintf(filename, "%c%d%d", char(num1), num2, num3);
            // สร้างไฟล์
            myFile = SD.open((String(folderName) + "/" + String(filename) + ".txt").c_str(), FILE_WRITE);
            if (myFile) {
              myFile.println("30");
              if (num1 == 65) {
                myFile.println("0");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
                ////
              }
              if (num1 == 66) {
                myFile.println("90");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 67) {
                myFile.println("200");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 68) {
                myFile.println("290");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 69) {
                myFile.println("500");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 70) {
                myFile.println("590");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 71) {
                myFile.println("690");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 72) {
                myFile.println("800");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 73) {
                myFile.println("990");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 74) {
                myFile.println("1100");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 75) {
                myFile.println("1175");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 76) {
                myFile.println("1285");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              myFile.close();
              Serial.println(String(filename));
            } else {
              Serial.println("Error opening file");
            }
          }
        } else if (num2 == 0 && num3 <= 9) {
          sprintf(folderName, "%c%d%d", char(num1), num2, num3);
          if (SD.mkdir(folderName)) {
            sprintf(filename, "%c%d%d", char(num1), num2, num3);
            myFile = SD.open((String(folderName) + "/" + String(filename) + ".txt").c_str(), FILE_WRITE);
            if (myFile) {
              myFile.println("30");
              if (num1 == 65) {
                myFile.println("0");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
                ////
              }
              if (num1 == 66) {
                myFile.println("90");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 67) {
                myFile.println("200");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 68) {
                myFile.println("290");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 69) {
                myFile.println("500");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 70) {
                myFile.println("590");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 71) {
                myFile.println("690");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 72) {
                myFile.println("800");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 73) {
                myFile.println("990");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 74) {
                myFile.println("1100");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 75) {
                myFile.println("1175");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              if (num1 == 76) {
                myFile.println("1285");
                if (num2 == 0 && num3 == 0) { myFile.println("0"); }
                if (num2 == 0 && num3 == 1) { myFile.println("90"); }
                if (num2 == 0 && num3 == 2) { myFile.println("210"); }
                if (num2 == 0 && num3 == 3) { myFile.println("330"); }
                if (num2 == 0 && num3 == 4) { myFile.println("440"); }
                if (num2 == 0 && num3 == 5) { myFile.println("550"); }
                if (num2 == 0 && num3 == 6) { myFile.println("660"); }
                if (num2 == 0 && num3 == 7) { myFile.println("780"); }
                if (num2 == 0 && num3 == 8) { myFile.println("890"); }
                if (num2 == 0 && num3 == 9) { myFile.println("1010"); }
                if (num2 == 1 && num3 == 0) { myFile.println("1130"); }
                if (num2 == 1 && num3 == 1) { myFile.println("1200"); }
              }
              myFile.close();
              Serial.println(String(filename));
            } else {
              Serial.println("Error opening file");
            }
          }
        }
      }
    }
  }
}

void loop() {
  // Nothing happens after setup
}
