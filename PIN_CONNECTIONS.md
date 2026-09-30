 # 🔌 Pin Connections

## 🤖 Arduino Uno

### IR Sensors

| Component | Arduino Pin |
|---|---|
| Left IR Sensor OUT | D2 |
| Right IR Sensor OUT | D3 |

### HC-SR04 Ultrasonic Sensor

| HC-SR04 Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D4 |
| ECHO | D5 |

### L298N Motor Driver

| L298N Pin | Arduino Pin |
|---|---|
| ENA | D6 |
| IN1 | D7 |
| IN2 | D8 |
| ENB | D9 |
| IN3 | D10 |
| IN4 | D11 |

### SG90 Servo Motor

| Servo Wire | Connection |
|---|---|
| Signal | D12 |
| VCC | 5V |
| GND | GND |

## ⚙️ DC Motor Connections

| Motor Driver | Motor |
|---|---|
| OUT1 / OUT2 | Left DC Motor |
| OUT3 / OUT4 | Right DC Motor |

## 🔋 Power

- L298N → External battery supply
- Arduino → Suitable 5V supply
- Servo → Suitable 5V supply
- Sensors → Arduino 5V
- **All GND connections must be common.**

## 🔄 Servo Scanning

The servo rotates the HC-SR04 ultrasonic sensor:

- **90° → Front**
- **150° → Left**
- **30° → Right**

When an obstacle is detected, the robot checks both sides and turns toward the side with more available space.

> Note: Pin assignments may need to be changed according to the actual hardware wiring.
