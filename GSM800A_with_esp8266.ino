#include <SoftwareSerial.h>

SoftwareSerial mySerial(13, 15);

void setup() {
  mySerial.begin(115200);  // Setting the baud rate of GSM Module
  Serial.begin(115200);    // Setting the baud rate of Serial Monitor (Arduino)
//  delay(100);
}

void loop() {
  if (mySerial.available() > 0)
  {
    Serial.write(mySerial.read());
  }
//  if (Serial.available() > 0)
//  {
//    mySerial.write(Serial.read());
//  }
    if (Serial.available() > 0)
    {
      switch (Serial.read()) {
        case 's':
          SendMessage();
          break;
        case 'd':
          DialCall();
          break;
        case 'r':
          RecieveMessage();
          break;
        case 'g':
          GPS_Location();
          break;
        case 'h':
          HTTP();
          break;
      }
    }
}

void SendMessage() {
  mySerial.println("AT+CMGF=1");  //Sets the GSM Module in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+91x\"\r");  // Replace x with mobile number
  delay(1000);
  mySerial.println("Hi champ! How have you been?");  // The SMS text you want to send
  delay(500);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(1000);
}

void RecieveMessage() {
  mySerial.println("AT+CNMI=2,2,0,0,0");  // AT Command to recieve a live SMS
  delay(1000);
}

void DialCall() {
  mySerial.println("ATD+91x;");  // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(100);
}

void GPS_Location() {
    mySerial.println("AT+CGNSSPWR=1");
    delay(1000);
    mySerial.println("AT+CGNSSTST=1");
    delay(1000);
}

void HTTP() {
  mySerial.println("AT+HTTPINIT");
  delay(1000);
  mySerial.println("AT+HTTPPARA=\"URL\",\"Enter your url\"\r\n");
  delay(1000);
  mySerial.println("AT+HTTPACTION=0\r\n");        //'0' To get data & '1' To post data
  delay(1000);
}
