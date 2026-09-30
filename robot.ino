#include <Servo.h>

// ================= PIN DEFINITIONS =================

// IR Sensors
const byte LEFT_IR_PIN  = 2;
const byte RIGHT_IR_PIN = 3;

// Ultrasonic Sensor
const byte TRIG_PIN = 4;
const byte ECHO_PIN = 5;

// L298N Motor Driver
const byte ENA_PIN = 6;
const byte IN1_PIN = 7;
const byte IN2_PIN = 8;

const byte ENB_PIN = 9;
const byte IN3_PIN = 10;
const byte IN4_PIN = 11;

// Servo Motor
const byte SERVO_PIN = 12;


// ================= OBJECTS =================

Servo ultrasonicServo;


// ================= SETTINGS =================

const int MOTOR_SPEED = 150;
const int OBSTACLE_DISTANCE = 20;

const int SERVO_CENTER = 90;
const int SERVO_LEFT   = 150;
const int SERVO_RIGHT  = 30;


// ================= SETUP =================

void setup() {

  // IR sensors
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);

  // Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor driver
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  // Servo
  ultrasonicServo.attach(SERVO_PIN);
  ultrasonicServo.write(SERVO_CENTER);

  // Serial communication
  Serial.begin(9600);

  stopRobot();
}


// ================= ULTRASONIC =================

long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  return duration * 0.0343 / 2;
}


// ================= MOTOR CONTROL =================

void forward() {

  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);

  analogWrite(ENA_PIN, MOTOR_SPEED);
  analogWrite(ENB_PIN, MOTOR_SPEED);
}


void backward() {

  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);

  analogWrite(ENA_PIN, MOTOR_SPEED);
  analogWrite(ENB_PIN, MOTOR_SPEED);
}


void turnLeft() {

  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);

  analogWrite(ENA_PIN, MOTOR_SPEED);
  analogWrite(ENB_PIN, MOTOR_SPEED);
}


void turnRight() {

  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);

  analogWrite(ENA_PIN, MOTOR_SPEED);
  analogWrite(ENB_PIN, MOTOR_SPEED);
}


void stopRobot() {

  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);

  analogWrite(ENA_PIN, 0);
  analogWrite(ENB_PIN, 0);
}


// ================= SERVO SCANNING =================

long scanAtAngle(int angle) {

  ultrasonicServo.write(angle);
  delay(400);

  return getDistance();
}


// ================= OBSTACLE AVOIDANCE =================

void avoidObstacle() {

  stopRobot();
  delay(200);

  // Move slightly backward
  backward();
  delay(250);

  stopRobot();
  delay(200);

  // Scan left
  long leftDistance = scanAtAngle(SERVO_LEFT);

  // Scan right
  long rightDistance = scanAtAngle(SERVO_RIGHT);

  // Return sensor to center
  ultrasonicServo.write(SERVO_CENTER);
  delay(200);

  // Choose the side with more space
  if (leftDistance > rightDistance) {

    turnLeft();
    delay(500);

  } else {

    turnRight();
    delay(500);
  }

  stopRobot();
  delay(100);
}


// ================= LINE FOLLOWING =================

void lineFollowing() {

  int leftSensor = digitalRead(LEFT_IR_PIN);
  int rightSensor = digitalRead(RIGHT_IR_PIN);

  // LOW = black line
  // HIGH = white surface

  if (leftSensor == LOW && rightSensor == LOW) {

    // Both sensors on the line
    forward();
  }

  else if (leftSensor == LOW && rightSensor == HIGH) {

    // Line is on the left
    turnLeft();
  }

  else if (leftSensor == HIGH && rightSensor == LOW) {

    // Line is on the right
    turnRight();
  }

  else {

    // Line not detected
    stopRobot();
  }
}


// ================= MAIN LOOP =================

void loop() {

  // Keep ultrasonic sensor facing forward
  ultrasonicServo.write(SERVO_CENTER);

  long distance = getDistance();

  Serial.print("Front Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Obstacle detected
  if (distance <= OBSTACLE_DISTANCE) {

    avoidObstacle();
  }

  // No obstacle
  else {

    lineFollowing();
  }

  delay(20);
}
