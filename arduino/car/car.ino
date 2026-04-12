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

// // Infrared Receiver
// IRrecv irRecv(irRecvPin);

// // Declare a variable to hold the results from the infrared receiver
// decode_results irRecvResults;

// The time motors should wait until switching to the next phase
const int motorDelayTime = 6;

// Declare a variable to represent the current drive state of the motor
uint8_t currentDriveState = 4;

// // Remote Control Button Command Codes
// const uint16_t forwardBtnCommand = 24; // Button 2
// const uint16_t backwardBtnCommand = 82; // Button 8
// const uint16_t rightBtnCommand = 90; // Button 6
// const uint16_t leftBtnCommand = 8; // Button 4
// const uint16_t stopBtnCommand = 28; // Button 5

// const int forwardBtnCode = 0x0;
// const int backwardBtnCode = 0x1;
// const int rightBtnCode = 0x2;
// const int leftBtnCode = 0x3;
// const int stopBtnCode = 0x4;

// Store the drive state options
namespace DriveStateOptions {
  const uint8_t forward = 24;
  const uint8_t backward = 82;
  const uint8_t right = 90;
  const uint8_t left = 8;
  const uint8_t stop = 28;
}

/*
// Create the driveService with its `driveStateCharacteristic`
const char* driveServiceUuid = "678630d9-bbb4-4867-af2e-fb51af7097da";
BLEService driveService(driveServiceUuid);
BLEByteCharacteristic driveStateCharacteristic(driveServiceUuid, BLEWrite);
*/

void setup() {
  // Enable the Serial Monitor for debugging
  Serial.begin(9600);

  // Enable the infrared receiver
  IrReceiver.begin(irRecvPin, ENABLE_LED_FEEDBACK);
  // irRecv.enableIRIn();
  
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

  /*
  //
  driveService.addCharacteristic(driveStateCharacteristic);

  // Set the inital value of `driveStateCharacteristic` to be STOP
  driveStateCharacteristic.writeValue(DriveStateOptions::stop);

  // Start the Low Level Bluetooth
  if (!BLE.begin()) {
    // Display an error message to the console (if connected to the Arduino IDE)
    Serial.println("Error: Failed to start the Low Level Bluetooth");

    while (true);
  }

  // Set the name of the device
  BLE.setLocalName("ArduinoCar");
  BLE.setDeviceName("ArduinoCar");
  BLE.setAdvertisedService(driveService);

  // Add the driveService to device
  BLE.addService(driveService);

  // Start advertising the device's presence
  BLE.advertise();
  */
}

void loop() {
  // See if the remote has changed the drive state
  if (IrReceiver.decode()) {
    // Set the `currentDriveState` based on the command from the remote signal
    currentDriveState = IrReceiver.decodedIRData.command;

    // Have the infrared reciever resume waiting for signals
    IrReceiver.resume();
  }

  // Rotate the correct wheels for the current drive state
  rotateInCurrentDirection();

  /*
  rotateForward();
  */
  /*
  // Get a reference to the central device (if any) connected to this peripheral device
  BLEDevice central = BLE.central();
  Serial.println("Test");

  // If a device is connected to this device, do the following
  if (central) {
    Serial.println("Connected to central");

    while (central.connected()) {
      // If the central device has changed the value of `driveStateCharacteristic`
      if (driveStateCharacteristic.written()) {
        // Get the new drive state
        currentDriveState = driveStateCharacteristic.value();

        // // Get the new drive state
        // uint8_t newDriveState = driveStateCharacteristic.value();

        // // Cause the car's actual motion to match the Bluetooth's `driveStateCharacteristic`
        // switch (newDriveState) {
        //   case DriveStateOptions::forward:
        //     setToForward();
        //     break;
        //   case DriveStateOptions::backward:
        //     setToBackward();
        //     break;
        //   case DriveStateOptions::left:
        //     setToLeft();
        //     break;
        //   case DriveStateOptions::right:
        //     setToRight();
        //     break;
        //   case DriveStateOptions::stop:
        //     setToStop();
        //     break;
        //   default:
        //     break;
        // }
      }

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

    turnOffAllCurrentGoingToMotors();

    Serial.println("Disconnected to central");

    // // Stop the car when the central device disconnects
    // setToStop();
  }
  */
}

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

//
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

inline void turnOffAllCurrentGoingToMotors() {
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



// inline void setToForward() {
//   // digitalWrite()

//   digitalWrite(LED_BUILTIN, HIGH);
// }

// inline void setToBackward() {
//   digitalWrite(LED_BUILTIN, LOW);
// }

// inline void setToLeft() {
//   digitalWrite(LED_BUILTIN, LOW);
// }

// inline void setToRight() {
//   digitalWrite(LED_BUILTIN, LOW);
// }

// inline void setToStop() {
//   digitalWrite(LED_BUILTIN, LOW);
// }
