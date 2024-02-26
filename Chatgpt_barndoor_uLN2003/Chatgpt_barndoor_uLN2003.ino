@ -1,150 +0,0 @@
#include <AccelStepper.h>

// Define the number of steps per revolution for your stepper motor
const int stepsPerRevolution = 2048;  // 28BYJ-48 has 2048 steps per revolution

// Define the motor control pins
const int motorPin1 = 8;    // IN1 on ULN2003
const int motorPin2 = 9;    // IN2 on ULN2003
const int motorPin3 = 10;   // IN3 on ULN2003
const int motorPin4 = 11;   // IN4 on ULN2003

// Define the start/stop button, reverse button, and home switch button
const int startStopButton = 2;       // Pin for start/stop button
const int reverseButton = 3;         // Pin for reverse button
const int homeSwitchButton = 4;      // Pin for home switch button

// Create an AccelStepper object
AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

// Variables
bool lastButtonState = HIGH;
unsigned long lastButtonChangeTime = 0;
const unsigned long buttonDelay = 250;  // Delay in milliseconds
bool reverseButtonState = HIGH;
bool lastReverseButtonState = HIGH;
unsigned long lastReverseButtonChangeTime = 0;
const unsigned long reverseButtonDelay = 250;  // Delay in milliseconds

bool homeSwitchState = HIGH;
bool lastHomeSwitchState = HIGH;
unsigned long lastHomeSwitchChangeTime = 0;
const unsigned long homeSwitchDelay = 250;  // Delay in milliseconds

bool motorRunning = false;
bool lastDirection = true;  // true: CW, false: CCW

long lastRevolutionCount = 0;

// Speed control variable (adjust as needed)
float motorSpeed = 15.0;  // Default speed: 15 RPM

void setup() {
  // Set up button pins as inputs with pull-up resistors
  pinMode(startStopButton, INPUT_PULLUP);
  pinMode(reverseButton, INPUT_PULLUP);
  pinMode(homeSwitchButton, INPUT_PULLUP);

  // Set up the AccelStepper library
  stepper.setMaxSpeed(motorSpeed * stepsPerRevolution / 60.0);
  stepper.setAcceleration(500.0);  // Set your desired acceleration in steps per second^2

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Check start/stop button
  int buttonState = digitalRead(startStopButton);
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastButtonChangeTime > buttonDelay) {
    if (!motorRunning) {
      // Start the motor
      startMotor();
    } else {
      // Stop the motor
      stopMotor();
    }
    lastButtonChangeTime = millis();
  }

  // Check reverse button
  reverseButtonState = digitalRead(reverseButton);
  if (reverseButtonState == LOW && lastReverseButtonState == HIGH && millis() - lastReverseButtonChangeTime > reverseButtonDelay) {
    // Toggle direction if the motor is not running
    if (!motorRunning) {
      toggleDirection();
      Serial.println("Direction changed.");
    }
    lastReverseButtonChangeTime = millis();
  }

  // Check home switch button
  homeSwitchState = digitalRead(homeSwitchButton);
  if (homeSwitchState == LOW && lastHomeSwitchState == HIGH && millis() - lastHomeSwitchChangeTime > homeSwitchDelay) {
    // Stop the motor and reset step count to 0 if running in CW direction
    if (motorRunning && lastDirection) {
      homingProcedure();
      Serial.println("Home Switch Pressed. Motor stopped, step count reset, and direction set to CCW.");
    }
    lastHomeSwitchChangeTime = millis();
  }

  // Update the stepper motor
  stepper.run();

  // Update the revolution count
  if (motorRunning) {
    long currentRevolutionCount = stepper.currentPosition() / stepsPerRevolution;
    if (currentRevolutionCount != lastRevolutionCount) {
      Serial.print("Revolution Count: ");
      Serial.println(currentRevolutionCount);
      lastRevolutionCount = currentRevolutionCount;
    }
  }

  // Update the last button states
  lastButtonState = buttonState;
  lastReverseButtonState = reverseButtonState;
  lastHomeSwitchState = homeSwitchState;
}

void startMotor() {
  Serial.println("Starting motor...");

  // Set the motor direction
  stepper.setSpeed(lastDirection ? motorSpeed : -motorSpeed);  // Set speed based on the motorSpeed variable
  stepper.move(lastDirection ? INFINITY : -INFINITY);  // Continuous rotation in the selected direction
  motorRunning = true;
}

void stopMotor() {
  Serial.print("Stopping motor at position: ");
  Serial.println(stepper.currentPosition());
  stepper.stop();
  motorRunning = false;
  lastRevolutionCount = 0;  // Reset revolution count
}

void toggleDirection() {
  lastDirection = !lastDirection;
  if (lastDirection) {
    Serial.println("Direction changed to CW");
  } else {
    Serial.println("Direction changed to CCW");
  }
}

void homingProcedure() {
  Serial.println("Homing Procedure...");

  // Reset step count to 0
  stepper.setCurrentPosition(0);

  // Set direction to CCW
  lastDirection = false;

  // Move CCW for 1 revolution at 15 RPM
  stepper.setMaxSpeed(15.0 * stepsPerRevolution / 60.0);  // 15 RPM
  stepper.move(-stepsPerRevolution);  // Move for 1 revolution in the CCW direction
  stepper.runToPosition();  // Wait for the homing procedure to complete
}
