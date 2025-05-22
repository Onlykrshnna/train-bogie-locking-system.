# train-bogie-locking-system.
# Smart Train Bogie Locking & Alert System

## Project Overview
The Smart Train Bogie Locking & Alert System is a safety-focused embedded solution designed to automatically secure train bogie doors while the train is in motion and unlock them only at authorized stops. It enhances passenger security by preventing unauthorized door openings during transit and sends real-time alerts to the control center in case of any security breaches or system faults.

## Key Features
- Automatic locking of bogie doors when the train is moving
- Safe unlocking only when the train has fully stopped at stations
- Real-time SMS alerts via GSM module on unauthorized access or tampering
- Manual override functionality for emergency access
- Reliable sensor integration to monitor door status and train movement

## Technologies Used
- **Hardware:** Arduino Uno, IR Sensors, Speed Sensor, Magnetic Door Sensors, GSM Module (SIM800L), Motor Driver, DC Motors/Servos
- **Software:** Arduino IDE, Embedded C/C++, AT Commands for GSM communication

## Challenges Faced
- Sensor calibration to minimize false triggers during train slowdowns
- Ensuring reliable GSM communication and alert delivery
- Designing fail-safe manual override controls
- Simulating realistic train conditions for testing purposes

## How It Works
1. The system continuously monitors train movement and door status through sensors.
2. Doors lock automatically when the train starts moving.
3. Doors unlock only when the train stops fully at designated stations.
4. Any unauthorized door opening triggers an immediate SMS alert to the control center.
5. Authorized personnel can manually override door locks during emergencies.

## Setup Instructions
1. Clone this repository:  
   ```bash
   git clone https://github.com/USERNAME/train-bogie-locking-system.git
