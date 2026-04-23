// Note: Portions of this sketch were based on the work of Lee Curiosity
//   - See https://projecthub.arduino.cc/lee_curiosity/a-beginners-guide-controlling-an-arduino-car-with-a-remote-5d4418 for Curiosity's original work

// #include <ArduinoBLE.h>
#include <IRremote.h>

// Right Motor Pins
namespace RightMotorPins {
  const uint8_t in1 = 2;
  const uint8_t in2 = 3;
  const uint8_t in3 = 4;
  const uint8_t in4 = 5;
}

// Left Motor Pins
namespace LeftMotorPins {
  const uint8_t in1 = 6;
  const uint8_t in2 = 7;
  const uint8_t in3 = 8;
  const uint8_t in4 = 9;
}

// Infrared Receiver Pin
const uint8_t irRecvPin = 10;

// The time motors should wait until switching to the next phase
const int motorDelayTime = 6;

// Declare a variable to represent the current drive state of the motor
uint8_t currentDriveState = 4;

// Store the drive state options
namespace DriveStateOptions {
  const uint8_t forward = 24;
  const uint8_t backward = 82;
  const uint8_t right = 90;
  const uint8_t left = 8;
  const uint8_t stop = 28;
}

void setup() {
  // Enable the Serial Monitor for debugging
  Serial.begin(9600);

  // Enable the infrared receiver
  IrReceiver.begin(irRecvPin, ENABLE_LED_FEEDBACK);
  
  // Allow the built in LED to be used
  pinMode(LED_BUILTIN, OUTPUT);

  // Set up the motor driver pins
  pinMode(RightMotorPins::in1, OUTPUT);
  pinMode(RightMotorPins::in2, OUTPUT);
  pinMode(RightMotorPins::in3, OUTPUT);
  pinMode(RightMotorPins::in4, OUTPUT);
  pinMode(LeftMotorPins::in1, OUTPUT);
  pinMode(LeftMotorPins::in2, OUTPUT);
  pinMode(LeftMotorPins::in3, OUTPUT);
  pinMode(LeftMotorPins::in4, OUTPUT);
}

void loop() {
  // See if the remote has changed the drive state
  if (IrReceiver.decode()) {
    // Set the `currentDriveState` based on the command from the remote signal
    currentDriveState = IrReceiver.decodedIRData.command;

    // Have the infrared reciever resume waiting for signals
    IrReceiver.resume();
  }

  // Rotate the correct motors for the current drive state
  rotateInCurrentDirection();
}

// Rotate the correct motors for the current drive state
inline void rotateInCurrentDirection() {
  switch(currentDriveState) {
    case DriveStateOptions::forward:
      rotateForward();
      break;
    case DriveStateOptions::backward:
      rotateBackward();
      break;
    case DriveStateOptions::right:
      rotateRight();
      break;
    case DriveStateOptions::left:
      rotateLeft();
      break;
    default:
      break;
  }
}

// Complete one rotation in the forward direction
inline void rotateForward() {
  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in1` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, HIGH);
  // Set the left motor to face the `in1` phase
  digitalWrite(LeftMotorPins::in1, HIGH);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in2` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, HIGH);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in2` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, HIGH);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in3` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, HIGH);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in3` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, HIGH);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in4` phase
  digitalWrite(RightMotorPins::in1, HIGH);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in4` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, HIGH);
}

// Complete one rotation in the backward direction
inline void rotateBackward() {
  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in1` phase
  digitalWrite(RightMotorPins::in1, HIGH);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in1` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, HIGH);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in2` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, HIGH);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in2` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, HIGH);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in3` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, HIGH);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in3` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, HIGH);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in4` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, HIGH);
  // Set the left motor to face the `in4` phase
  digitalWrite(LeftMotorPins::in1, HIGH);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);
}

// Complete one rotation in the right direction
inline void rotateRight() {
  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in1` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in1` phase
  digitalWrite(LeftMotorPins::in1, HIGH);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in2` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in2` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, HIGH);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in3` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in3` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, HIGH);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in4` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in4` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, HIGH);
}

// Complete one rotation in the left direction
inline void rotateLeft() {
  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in1` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, HIGH);
  // Set the left motor to face the `in1` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in2` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, HIGH);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in2` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in3` phase
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, HIGH);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in3` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);

  // Wait to change the phase
  delay(motorDelayTime);
  // Set the right motor to face the `in4` phase
  digitalWrite(RightMotorPins::in1, HIGH);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Set the left motor to face the `in4` phase
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);
}

// Ensure that all motors input pins are off
inline void stopAllCurrentGoingToMotors() {
  // Keep the right motor off
  digitalWrite(RightMotorPins::in1, LOW);
  digitalWrite(RightMotorPins::in2, LOW);
  digitalWrite(RightMotorPins::in3, LOW);
  digitalWrite(RightMotorPins::in4, LOW);
  // Keep the left motor off
  digitalWrite(LeftMotorPins::in1, LOW);
  digitalWrite(LeftMotorPins::in2, LOW);
  digitalWrite(LeftMotorPins::in3, LOW);
  digitalWrite(LeftMotorPins::in4, LOW);
}
