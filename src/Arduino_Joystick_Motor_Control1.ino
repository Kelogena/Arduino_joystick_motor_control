#include <Servo.h>
#include <Stepper.h>

// ── Pin definitions ────────────────────────────
const int VRX_PIN  = A0;   // Joystick X  → servo
const int VRY_PIN  = A1;   // Joystick Y  → stepper
const int SW_PIN   = 2;    // Joystick button → e-stop
const int SERVO_PIN = 9;

// Stepper: 28BYJ-48 has 2048 steps/revolution
const int STEPS_PER_REV = 2048;
Stepper stepper(STEPS_PER_REV, 8, 6, 7, 5); // IN1,IN2,IN3,IN4

Servo myServo;

bool stopped = false;

void setup() {
  myServo.attach(SERVO_PIN);
  myServo.write(90);             // start centered

  pinMode(SW_PIN, INPUT_PULLUP); // button uses internal pull-up

  stepper.setSpeed(15);          // default RPM (max ~17 for 28BYJ-48)
  Serial.begin(9600);
}

void loop() {
  // ── Emergency stop (active LOW because INPUT_PULLUP) ──
  if (digitalRead(SW_PIN) == LOW) {
    stopped = !stopped;          // toggle on each press
    myServo.write(90);           // return servo to center
    delay(300);                  // debounce
    Serial.println(stopped ? "STOPPED" : "RUNNING");
  }

  if (stopped) return;           // do nothing while stopped

  // ── Read joystick ──────────────────────────────────────
  int xVal = analogRead(VRX_PIN);   // 0 – 1023
  int yVal = analogRead(VRY_PIN);   // 0 – 1023

  // ── Servo: map X-axis → 0–180° ────────────────────────
  int servoAngle = map(xVal, 0, 1023, 0, 180);
  myServo.write(servoAngle);

  // ── Stepper: Y-axis controls speed and direction ───────
  //   Dead zone: 400–623  → stop
  //   0–399  → forward, speed proportional to how far pushed
  //   624–1023 → backward, speed proportional

  int stepDelay;

  if (yVal < 400) {
    // Forward – the further from center, the faster
    int speed = map(yVal, 0, 399, 17, 1);  // 1 = fastest RPM
    stepper.setSpeed(speed);
    stepper.step(4);                        // small step per loop tick

  } else if (yVal > 623) {
    // Backward
    int speed = map(yVal, 624, 1023, 1, 17);
    stepper.setSpeed(speed);
    stepper.step(-4);

  }
  // else: dead zone → stepper doesn't move (no step() call)

  // ── Debug output ───────────────────────────────────────
  Serial.print("X:"); Serial.print(xVal);
  Serial.print("  Y:"); Serial.print(yVal);
  Serial.print("  Servo:"); Serial.print(servoAngle);
  Serial.println("°");
}