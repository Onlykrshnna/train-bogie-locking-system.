#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins
const int servoPin = 9;
const int irSensorPin = 2;
const int ledLocked = 4;
const int ledUnlocked = 5;
const int buzzerPin = 6;

// Objects
Servo lockServo;
SoftwareSerial gsmSerial(10, 11); // RX, TX pins for SIM800L
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
String incomingSMS = "";
bool doorLocked = false;
bool alertSent = false;

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(irSensorPin, INPUT);
  pinMode(ledLocked, OUTPUT);
  pinMode(ledUnlocked, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lockServo.attach(servoPin);
  lockDoor();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Train Bogie Sys");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  delay(2000);

  sendATCommand("AT");
  sendATCommand("AT+CMGF=1");     // SMS text mode
  sendATCommand("AT+CNMI=2,2,0,0,0"); // Direct SMS to serial

  lcd.clear();
  updateLCDStatus();
}

void loop() {
  monitorDoor();
  receiveSMS();
}

void monitorDoor() {
  int doorState = digitalRead(irSensorPin);
  if (doorLocked && doorState == HIGH && !alertSent) {
    // Door opened while locked - unauthorized
    alertSent = true;
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledUnlocked, HIGH);
    digitalWrite(ledLocked, LOW);
    lcd.clear();
    lcd.print("Alert! Door Open");
    sendSMS("Alert! Train bogie door opened unauthorized.");
  }
  if (doorState == LOW) {
    // Door closed
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledLocked, doorLocked ? HIGH : LOW);
    digitalWrite(ledUnlocked, doorLocked ? LOW : HIGH);
    if(alertSent) {
      alertSent = false;
      updateLCDStatus();
    }
  }
}

void receiveSMS() {
  while (gsmSerial.available()) {
    char c = gsmSerial.read();
    Serial.write(c);

    if (c == '\n' || c == '\r') {
      if (incomingSMS.length() > 0) {
        handleSMS(incomingSMS);
        incomingSMS = "";
      }
    } else {
      incomingSMS += c;
    }
  }
}

void handleSMS(String sms) {
  sms.trim();
  sms.toUpperCase();

  Serial.print("Received SMS: ");
  Serial.println(sms);

  if (sms.indexOf("OPEN") != -1) {
    unlockDoor();
    sendSMS("Door is now OPENED.");
  } else if (sms.indexOf("CLOSE") != -1) {
    lockDoor();
    sendSMS("Door is now LOCKED.");
  }
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1");
  delay(100);
  gsmSerial.println("AT+CMGS=\"+911234567890\""); // Replace with your phone number
  delay(100);
  gsmSerial.print(message);
  delay(100);
  gsmSerial.write(26); // Ctrl+Z to send
  delay(5000);
  Serial.println("SMS sent: " + message);
}

void sendATCommand(String cmd) {
  gsmSerial.println(cmd);
  delay(500);
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}

void lockDoor() {
  lockServo.write(0);  // Adjust angle for lock
  doorLocked = true;
  updateLCDStatus();
  digitalWrite(ledLocked, HIGH);
  digitalWrite(ledUnlocked, LOW);
  digitalWrite(buzzerPin, LOW);
  Serial.println("Door Locked.");
}

void unlockDoor() {
  lockServo.write(90); // Adjust angle for unlock
  doorLocked = false;
  updateLCDStatus();
  digitalWrite(ledLocked, LOW);
  digitalWrite(ledUnlocked, HIGH);
  digitalWrite(buzzerPin, LOW);
  Serial.println("Door Unlocked.");
}

void updateLCDStatus() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Door Status:");
  lcd.setCursor(0,1);
  if (doorLocked) {
    lcd.print("Locked");
  } else {
    lcd.print("Unlocked");
  }
}
