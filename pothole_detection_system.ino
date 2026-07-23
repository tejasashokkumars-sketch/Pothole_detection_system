//==============================
// POTHOLE DETECTION ROBOT
//==============================

// L298N Motor Driver Pins
#define ENA 9
#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10
#define ENB 5

// HC-SR04 Pins
#define TRIG_PIN 7
#define ECHO_PIN 6

long duration;
float distance;

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop()
{
  distance = getDistance();

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance >= 5.5)
  {
    Serial.println("POTHOLE DETECTED");

    stopRobot();

    delay(4000);     // Stop for 4 seconds

    moveForward();

    delay(500);      // Avoid immediate re-detection
  }
  else
  {
    moveForward();
  }

  delay(100);
}

//==============================
// Measure Distance
//==============================
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.0343 / 2.0;

  return distance;
}

//==============================
// Move Forward (Slow Speed)
//==============================
void moveForward()
{
  analogWrite(ENA, 60);   // Slow speed
  analogWrite(ENB, 60);   // Slow speed

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//==============================
// Stop Robot
//==============================
void stopRobot()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}