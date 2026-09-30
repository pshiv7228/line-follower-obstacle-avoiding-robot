# 🤖 Line Follower & Obstacle Avoiding Robot

An Arduino-based autonomous robot that combines **line following** with **ultrasonic obstacle detection and avoidance**.

## 📌 Project Overview

This project demonstrates a basic autonomous robotic system using Arduino Uno, IR sensors, an ultrasonic sensor mounted on a servo motor, and an L298N motor driver.

The robot follows a predefined line and uses the ultrasonic sensor to detect obstacles. When an obstacle is detected, the servo rotates the ultrasonic sensor to scan the left and right sides. The robot then chooses a direction based on the available distance.

## ✨ Features

- Automatic line following
- Ultrasonic obstacle detection
- Servo-based left/right scanning
- Automatic obstacle avoidance
- DC motor control using L298N
- Arduino-based control
- Adjustable motor speed

## 🧰 Hardware Components

- Arduino Uno
- L298N Motor Driver
- 2 × DC Geared Motors
- 2 × IR Sensor Modules
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Robot Chassis
- Wheels
- Battery
- Jumper Wires

## 💻 Software & Tools

- Arduino IDE
- Arduino C/C++
- Arduino Uno
- Servo Library

## ⚙️ How It Works

### 1. Line Following

The two IR sensors detect the line on the surface.

The Arduino reads the sensor signals and controls the two DC motors through the L298N motor driver.

### 2. Obstacle Detection

The HC-SR04 ultrasonic sensor measures the distance in front of the robot.

If an obstacle is detected within the defined distance, the robot stops and starts the obstacle avoidance process.

### 3. Servo Scanning

The ultrasonic sensor is mounted on an SG90 servo motor.

The servo scans:

- 90° → Front
- 150° → Left
- 30° → Right

The Arduino compares the left and right distances and selects the side with more available space.

### 4. Motor Control

The L298N motor driver controls the two DC motors.

The robot can:

- Move forward
- Move backward
- Turn left
- Turn right
- Stop

## 📁 Project Files

| File | Description |
|---|---|
| `robot.ino` | Main Arduino program |
| `PIN_CONNECTIONS.md` | Complete hardware pin connections |
| `README.md` | Project documentation |

## 🔌 Pin Connections

Detailed Arduino pin connections are available in:

**[PIN_CONNECTIONS.md](PIN_CONNECTIONS.md)**

## 🧠 Key Concepts

- Robotics
- Embedded Systems
- Sensor Interfacing
- Line Following
- Ultrasonic Distance Measurement
- Servo Motor Control
- DC Motor Control
- Autonomous Navigation

## 🔮 Future Improvements

- Bluetooth control
- Wi-Fi / IoT integration
- Mobile application control
- Better path recovery
- Adjustable obstacle detection
- Improved motor speed control
- More advanced navigation algorithms

## 🎓 Learning Outcomes

Through this project, I learned about:

- Arduino programming
- Sensor interfacing
- Motor driver control
- Servo motor control
- Ultrasonic distance measurement
- Basic autonomous robotics

## 👨‍💻 Author

**Shiv Patel**

B.Tech Mechatronics Engineering  
ITM Vocational University

---

⭐ *Built as a practical robotics and automation project for learning and experimentation.*
