#include <Stepper.h>

// Define constants
const int stepsPerRevolution = 200;

// Motor 1 pins
const int motor1Pin1 = 4;
const int motor1Pin2 = 5;
const int motor1Pin3 = 6;
const int motor1Pin4 = 7;

// Motor 2 pins
const int motor2Pin1 = 8;
const int motor2Pin2 = 9;
const int motor2Pin3 = 10;
const int motor2Pin4 = 11;

const int xAxisPin = A0;
const int buttonPin = 2;

// Create Stepper instances for Motor 1 and Motor 2
Stepper motor1(stepsPerRevolution, motor1Pin4, motor1Pin2, motor1Pin3, motor1Pin1);
Stepper motor2(stepsPerRevolution, motor2Pin4, motor2Pin2, motor2Pin3, motor2Pin1);

// Define initial position and step tracking variables for both motors
int initialPosition1 = 0;
int initialPosition2 = 0;
int totalStepsMoved1 = 0;
int totalStepsMoved2 = 0;

void setup() {
  Serial.begin(9600);
  
  // Set up pins for Motor 1
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  motor1.setSpeed(100);
  
  // Set up pins for Motor 2
  motor2.setSpeed(100);
  
  // Move both motors to their initial positions
  motor1.step(initialPosition1);
  motor2.step(initialPosition2);
}

void loop() {
  // Read joystick and button state
  int xValue = analogRead(xAxisPin);
  int buttonState = digitalRead(buttonPin);

  // Set a threshold for joystick movement
  int joystickThreshold = 50;

  if (abs(xValue - 512) > joystickThreshold) {
    // Map joystick values to motor steps
    int steps = map(xValue, 0, 1023, -stepsPerRevolution, stepsPerRevolution);
    
    // Move both motors based on joystick movement
    motor1.step(steps);
    motor2.step(steps);

    // Update total steps moved for both motors
    totalStepsMoved1 += steps;
    totalStepsMoved2 += steps;
  } else {
    // Joystick is not moved, return to the initial position if the button is pressed
    if (buttonState == LOW) {
      // Return to the initial position for both motors
      motor1.step(-totalStepsMoved1);
      motor2.step(-totalStepsMoved2);
      
      // Reset total steps moved for both motors
      totalStepsMoved1 = 0;
      totalStepsMoved2 = 0;
    }
  }

  delay(200);
}
