// =======================
// Pin Definitions
// =======================

// Motor control pins for each wheel (IN1, IN2 = direction; EN = speed via PWM)
const int FL_IN1 = 27, FL_IN2 = 26, FL_EN = 14;  // Front Left motor
const int BL_IN1 = 33, BL_IN2 = 25, BL_EN = 32;  // Back Left motor
const int BR_IN1 = 19, BR_IN2 = 18, BR_EN = 17;  // Back Right motor
const int FR_IN1 = 16, FR_IN2 = 15, FR_EN = 4;   // Front Right motor

// Ultrasonic sensor pins (TRIG = send pulse, ECHO = receive echo)
const int TRIG_F = 23, ECHO_F = 22;  // Front sensor
const int TRIG_B = 13, ECHO_B = 35;  // Back sensor
const int TRIG_L = 5,  ECHO_L = 34;  // Left sensor
const int TRIG_R = 12, ECHO_R = 36;  // Right sensor

const int BUZZER_PIN = 21;  // Buzzer output pin
const int PIR_PIN = 2;      // PIR motion sensor input pin

const int THRESHOLD = 22;         // Obstacle distance threshold in cm
const int NORMAL_SPEED = 128;     // Speed for forward/backward
const int TURN_SPEED = 255;       // Speed for turning

// =======================
// State Tracking
// =======================

// Robot states to manage behavior
enum RobotState {
  IDLE, FORWARD, BACKWARD,
  REVERSE_BEFORE_TURN, TURN_LEFT, TURN_RIGHT
};

RobotState currentState = IDLE;       // Initial robot state
RobotState nextTurnState = IDLE;      // Holds upcoming turn direction

unsigned long stateStartTime = 0;     // Timer for tracking duration of actions
unsigned long actionDuration = 0;     // How long to perform a state (e.g., reversing)

// =======================
// Setup
// =======================
void setup() {
  // Set motor pins as outputs
  pinMode(FL_IN1, OUTPUT); pinMode(FL_IN2, OUTPUT); pinMode(FL_EN, OUTPUT);
  pinMode(BL_IN1, OUTPUT); pinMode(BL_IN2, OUTPUT); pinMode(BL_EN, OUTPUT);
  pinMode(BR_IN1, OUTPUT); pinMode(BR_IN2, OUTPUT); pinMode(BR_EN, OUTPUT);
  pinMode(FR_IN1, OUTPUT); pinMode(FR_IN2, OUTPUT); pinMode(FR_EN, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(TRIG_F, OUTPUT); pinMode(ECHO_F, INPUT);
  pinMode(TRIG_B, OUTPUT); pinMode(ECHO_B, INPUT);
  pinMode(TRIG_L, OUTPUT); pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT); pinMode(ECHO_R, INPUT);

  // Set buzzer and PIR sensor pins
  pinMode(BUZZER_PIN, OUTPUT); digitalWrite(BUZZER_PIN, LOW);  // Buzzer starts OFF
  pinMode(PIR_PIN, INPUT);                                     // PIR is input

  Serial.begin(115200);  // Initialize serial communication
}

// =======================
// Helper Functions
// =======================

// Measures distance using an ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000); // Timeout = 20ms
  return duration * 0.034 / 2;  // Convert to cm
}

// Sets speed for all motors
void setMotorSpeed(int speed) {
  analogWrite(FL_EN, speed); analogWrite(BL_EN, speed);
  analogWrite(BR_EN, speed); analogWrite(FR_EN, speed);
}

// Move robot forward
void moveForward() {
  setMotorSpeed(NORMAL_SPEED);
  digitalWrite(FL_IN1, HIGH); digitalWrite(FL_IN2, LOW);
  digitalWrite(BL_IN1, HIGH); digitalWrite(BL_IN2, LOW);
  digitalWrite(BR_IN1, HIGH); digitalWrite(BR_IN2, LOW);
  digitalWrite(FR_IN1, HIGH); digitalWrite(FR_IN2, LOW);
}

// Move robot backward
void moveBackward() {
  setMotorSpeed(NORMAL_SPEED);
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, HIGH);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, HIGH);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, HIGH);
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, HIGH);
}

// Turn robot left in place
void turnLeft() {
  setMotorSpeed(TURN_SPEED);
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, HIGH);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, HIGH);
  digitalWrite(BR_IN1, HIGH); digitalWrite(BR_IN2, LOW);
  digitalWrite(FR_IN1, HIGH); digitalWrite(FR_IN2, LOW);
}

// Turn robot right in place
void turnRight() {
  setMotorSpeed(TURN_SPEED);
  digitalWrite(FL_IN1, HIGH); digitalWrite(FL_IN2, LOW);
  digitalWrite(BL_IN1, HIGH); digitalWrite(BL_IN2, LOW);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, HIGH);
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, HIGH);
}

// Stop all motors
void stopMotors() {
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, LOW);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, LOW);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, LOW);
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, LOW);
}

// =======================
// Main Logic Loop
// =======================
void loop() {
  unsigned long now = millis();  // Current time for timing state transitions

  // === PIR Motion Detection ===
  int motionDetected = digitalRead(PIR_PIN);
  if (motionDetected == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);   // Turn buzzer ON if motion is detected
    Serial.println("⚠️ Motion Detected!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);    // Otherwise turn it OFF
  }

  // === Obstacle Avoidance ===
  if (currentState == FORWARD || currentState == IDLE) {
    long front = getDistance(TRIG_F, ECHO_F);
    long left  = getDistance(TRIG_L, ECHO_L);
    long right = getDistance(TRIG_R, ECHO_R);
    long back  = getDistance(TRIG_B, ECHO_B);

    // Print distances for debugging
    Serial.print("F: "); Serial.print(front);
    Serial.print(" | L: "); Serial.print(left);
    Serial.print(" | R: "); Serial.print(right);
    Serial.print(" | B: "); Serial.println(back);

    // Decision logic based on distances
    if (front > THRESHOLD) {
      moveForward();
      currentState = FORWARD;
    } else if (left > right && left > THRESHOLD) {
      moveBackward();                      // Reverse first
      currentState = REVERSE_BEFORE_TURN;
      nextTurnState = TURN_LEFT;          // Then turn left
      stateStartTime = now;
      actionDuration = 400;
    } else if (right > THRESHOLD) {
      moveBackward();                      // Reverse first
      currentState = REVERSE_BEFORE_TURN;
      nextTurnState = TURN_RIGHT;         // Then turn right
      stateStartTime = now;
      actionDuration = 400;
    } else if (back > THRESHOLD) {
      moveBackward();                      // Just reverse if front/side blocked
      currentState = BACKWARD;
      stateStartTime = now;
      actionDuration = 500;
    } else {
      stopMotors();                        // No escape — stop
      currentState = IDLE;
    }
  }

  // === Handle Timed States ===
  if (currentState == BACKWARD || currentState == TURN_LEFT || currentState == TURN_RIGHT || currentState == REVERSE_BEFORE_TURN) {
    if (now - stateStartTime >= actionDuration) {
      if (currentState == BACKWARD) {
        turnRight();                        // Default recovery turn
        currentState = TURN_RIGHT;
        stateStartTime = now;
        actionDuration = 325;
      } else if (currentState == REVERSE_BEFORE_TURN) {
        if (nextTurnState == TURN_LEFT) {
          turnLeft();
          currentState = TURN_LEFT;
        } else {
          turnRight();
          currentState = TURN_RIGHT;
        }
        stateStartTime = now;
        actionDuration = 325;
      } else {
        currentState = IDLE;                // Done with turn
      }
    }
  }
}
