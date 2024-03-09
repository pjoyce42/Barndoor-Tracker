#include <AccelStepper.h>

// Define the number of steps per revolution for your stepper motor
const int stepsPerRevolution = 3200 ;  // NEMA 17 has 200 steps per revolution

// Define the motor control pins for the A4988 driver
const int stepPin = 5;    // Step pin on A4988
const int dirPin = 6;     // Direction pin on A4988

// Define the start/stop button, reverse button, and home switch button
const int startStopButton = 2;       // Pin for start/stop button
const int reverseButton = 3;         // Pin for reverse button
const int homeSwitchButton = 4;      // Pin for home switch button

// Create an AccelStepper object
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

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

// Speed control variables (adjust as needed)
// float motorSpeedCW = 15.0;  // Default CW speed: 15 RPM
float motorSpeedCW = 1.0;  // Eclipse CW speed: ??? RPM
float motorSpeedCCW = 40.0; // Default CCW speed: 10 RPM

void setup() {
  // Set up button pins as inputs with pull-up resistors
  pinMode(startStopButton, INPUT_PULLUP);
  pinMode(reverseButton, INPUT_PULLUP);
  pinMode(homeSwitchButton, INPUT_PULLUP);

  // Set up the AccelStepper library
  stepper.setMaxSpeed(motorSpeedCW * stepsPerRevolution / 60.0);  // Set the initial speed to CW speed
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
    // Stop the motor and reset step count to 0 if running in CCW direction
    if (motorRunning && !lastDirection) {
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
  stepper.setSpeed(lastDirection ? motorSpeedCW : -motorSpeedCCW);  // Set speed based on the motorSpeed variables
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
    stepper.setMaxSpeed(motorSpeedCW * stepsPerRevolution / 60.0);
  } else {
    Serial.println("Direction changed to CCW");
    stepper.setMaxSpeed(motorSpeedCCW * stepsPerRevolution / 60.0);
  }
}

void homingProcedure() {
  Serial.println("Homing Procedure...");

  // Move CW for 1 revolution at the CW speed
  stepper.setMaxSpeed(15.0 * stepsPerRevolution / 60.0);
  stepper.move(stepsPerRevolution);  // Move for 1 revolution in the CW direction
  stepper.runToPosition();  // Wait for the homing procedure to complete

  // Reset step count to 0
  stepper.setCurrentPosition(0);

  // Set direction to CW
  lastDirection = true;

  Serial.print("Current motor at position: ");
  Serial.println(stepper.currentPosition());
}
