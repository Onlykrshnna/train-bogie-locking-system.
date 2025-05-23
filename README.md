# Smart Train Bogie Locking & Alert System with SMS Control & LCD Display

## Project Overview

This project aims to enhance railway safety by automatically securing train bogie doors and providing real-time monitoring, alerting, and remote control capabilities. The system locks or unlocks bogie doors using a servo motor, monitors door status via an IR sensor, and displays the current status on a 16x2 I2C LCD screen. Unauthorized door openings trigger SMS alerts to railway authorities through a SIM800L GSM module. Additionally, authorized users can remotely control door locking/unlocking by sending SMS commands (“OPEN” or “CLOSE”) to the system.

---

## Features

- **Automatic Door Locking & Unlocking** via servo motor  
- **Real-time Door Status Monitoring** using IR sensor  
- **Visual Status Display** on 16x2 I2C LCD (Locked/Unlocked, alerts)  
- **SMS Alerts** for unauthorized door opening or tampering  
- **Remote Door Control via SMS Commands** (“OPEN” / “CLOSE”)  
- **LED Indicators** for door lock status (Green = Locked, Red = Unlocked)  
- **Audible Buzzer Alerts** during unauthorized access  
- **Low Power Operation** with 3.7V Li-ion battery and voltage regulation  
- **Cost-effective & Easily Deployable** with widely available components  

---

## Hardware Components

| Component              | Description                                   |
|-----------------------|-----------------------------------------------|
| Arduino Uno R3         | Microcontroller board                         |
| TCRT5000 IR Sensor     | Door position detection                        |
| MG995 Servo Motor      | Door locking/unlocking                         |
| SIM800L GSM Module     | SMS alerts and remote command reception       |
| 16x2 I2C LCD Display   | System status display                          |
| LEDs (Red & Green)     | Lock status indicators                         |
| Buzzer                 | Audible alarm for unauthorized access         |
| 18650 Li-ion Battery   | Portable power source                          |
| AMS1117 Voltage Regulator | Stable 5V supply for GSM module               |

---

## Circuit Diagram

![Circuit Diagram](link_to_circuit_diagram_image)

*Link to the detailed circuit diagram.*

---

## How It Works

1. **Monitoring:** IR sensor detects bogie door open/closed status.  
2. **Locking:** Servo locks the door automatically once closed.  
3. **Alerts:** Unauthorized door openings trigger buzzer, LEDs, LCD alerts, and SMS notifications.  
4. **Remote Control:** Authorized SMS commands remotely open/close door with confirmation SMS.  
5. **Display:** LCD continuously updates current door status for onboard staff.

---

## Installation & Usage

### Setup Hardware

1. Assemble components as per the circuit diagram.  
2. Insert SIM card with SMS capability into SIM800L module.  
3. Connect the 3.7V Li-ion battery with proper voltage regulation.  
4. Ensure servo and sensors are securely mounted on bogie door.

### Upload Code

1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).  
2. Add required libraries: `Servo.h`, `SoftwareSerial.h`, `LiquidCrystal_I2C.h`.  
3. Replace phone number in the code with your own for SMS confirmation.  
4. Upload the Arduino sketch to the Arduino Uno board.

### Operation

- The system will automatically lock/unlock doors based on sensor input.  
- Unauthorized openings will send SMS alerts to the configured number.  
- Send “OPEN” or “CLOSE” via SMS to remotely control the door.  

---

## Code Snippet

```cpp
// Example function to handle SMS commands
void handleSMS(String sms) {
  sms.trim();
  sms.toUpperCase();

  if (sms.indexOf("OPEN") != -1) {
    unlockDoor();
    sendSMS("Door is now OPENED.");
  } else if (sms.indexOf("CLOSE") != -1) {
    lockDoor();
    sendSMS("Door is now LOCKED.");
  }
}
