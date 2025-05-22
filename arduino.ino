#include <SoftwareSerial.h>

// Pin definitions
const int speedSensorPin = 2;       // Digital input: train moving or stopped
const int doorStatusPin = 3;        // Digital input: door open/closed sensor
const int manualOverridePin = 4;    // Manual override button (active LOW)
const int doorLockMotorPin = 9;     // Output to motor or servo controlling door lock

// GSM module pins
const int gsmTxPin = 7;
const int gsmRxPin = 8;
SoftwareSerial gsmSerial(gsmTxPin, gsmRxPin);

bool doorLocked = false;

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(speedSensorPin, INPUT);
  pinMode(doorStatusPin, INPUT_PULLUP);
  pinMode(manualOverridePin, INPUT_PULLUP);
  pinMode(doorLockMotorPin, OUTPUT);

  lockDoor();
  sendSMS("System initialized: Door Locked");
}

void loop() {
  bool trainMoving = digitalRead(speedSensorPin) == HIGH;
  bool manualOverride = digitalRead(manualOverridePin) == LOW;
  bool doorOpen = digitalRead(doorStatusPin) == LOW; // Assuming LOW means door open

  if (manualOverride) {
    unlockDoor();
    sendSMS("Manual override activated: Door unlocked");
    delay(5000); // Keep unlocked for 5 seconds
  } else {
    if (trainMoving && !doorLocked) {
      lockDoor();
      sendSMS("Train moving: Door locked");
    }
    else if (!trainMoving && doorLocked) {
      unlockDoor();
      sendSMS("Train stopped: Door unlocked");
    }
  }

  // Alert if door opens while locked
  if (doorLocked && doorOpen) {
    sendSMS("ALERT: Unauthorized door opening detected!");
    delay(10000); // Avoid spamming alerts
  }

  delay(1000);
}

void lockDoor() {
  digitalWrite(doorLockMotorPin, HIGH); // Lock door (adjust logic as per your motor)
  doorLocked = true;
  Serial.println("Door locked");
}

void unlockDoor() {
  digitalWrite(doorLockMotorPin, LOW);  // Unlock door
  doorLocked = false;
  Serial.println("Door unlocked");
}

void sendSMS(String message) {
  gsmSerial.println("AT");
  delay(100);
  gsmSerial.println("AT+CMGF=1");    // Set SMS text mode
  delay(100);
  gsmSerial.println("AT+CMGS=\"+1234567890\"");  // Replace with your phone number
  delay(100);
  gsmSerial.print(message);
  delay(100);
  gsmSerial.write(26); // CTRL+Z to send
  delay(5000);
  Serial.println("SMS sent: " + message);
}
