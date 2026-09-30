// Line Follower + Obstacle Avoiding Robot
// Controller: Arduino Uno

// IR Sensors
#define LEFT_IR 2
#define RIGHT_IR 3

// Ultrasonic Sensor
#define TRIG_PIN 4
#define ECHO_PIN 5

// Motor Driver (L298N)
#define ENA 6
#define IN1 7
#define IN2 8

#define ENB 9
#define IN3 10
#define IN4 11

int motorSpeed = 150;
int obstacleDistance = 20;

void setup() {
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

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

  return duration * 0.034 / 2;
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void avoidObstacle() {
  stopRobot();
  delay(200);

  backward();
  delay(300);

  turnRight();
  delay(500);

  stopRobot();
  delay(100);
}

void lineFollowing() {
  int leftSensor = digitalRead(LEFT_IR);
  int rightSensor = digitalRead(RIGHT_IR);

  // For sensors where LOW means black line
  if (leftSensor == LOW && rightSensor == LOW) {
    forward();
  }
  else if (leftSensor == LOW && rightSensor == HIGH) {
    turnLeft();
  }
  else if (leftSensor == HIGH && rightSensor == LOW) {
    turnRight();
  }
  else {
    stopRobot();
  }
}

void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Obstacle detection has priority
  if (distance <= obstacleDistance) {
    avoidObstacle();
  }
  else {
    lineFollowing();
  }

  delay(20);
}
