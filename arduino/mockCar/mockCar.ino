#include <ArduinoBLE.h>

// Store the pins to use on the Arduino
namespace Pins {
  const uint8_t frontLeft = 2;
  const uint8_t frontRight = 3;
  const uint8_t backLeft = 4;
  const uint8_t backRight = 5;
}

// Store the drive state options
namespace DriveStateOptions {
  const uint8_t forward = 0;
  const uint8_t backward = 1;
  const uint8_t left = 2;
  const uint8_t right = 3;
  const uint8_t stop = 4;
}

// Create the driveService with its driveStateCharacteristic
const String driveServiceUuid = "678630d9-bbb4-4867-af2e-fb51af7097da";
BLEService driveService(driveServiceUuid);
BLEByteCharacteristic driveStateCharacteristic(driveServiceUuid, BLEWrite);
driveService.addCharacteristic(driveStateCharacteristic);

// Set the inital value of driveStateCharacteristic to be STOP
driveStateCharacteristic.writeValue(DriveStateOptions::stop);

void setup() {
  // Set the output pins on the Arduino
  pinMode(Pins::frontLeft, OUTPUT);
  pinMode(Pins::frontRight, OUTPUT);
  pinMode(Pins::backLeft, OUTPUT);
  pinMode(Pins::backRight, OUTPUT);

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
}

void loop() {
  // Get a reference to the central device (if any) connected to this peripheral device
  BLEDevice central = BLE.central();

  // If a device is connected to this device, do the following
  if (central) {
    Serial.println("Connected to central");

    while (central.connected()) {
      // If the central device has changed the value of driveStateCharacteristic
      if (driveStateCharacteristic.written()) {
        // Get the new drive state
        uint8_t newDriveState = driveStateCharacteristic.value();

        // Cause the car's actual motion to match the Bluetooth's driveStateCharacteristic
        switch (newDriveState) {
          case DriveStateOptions::forward:
            setToForward();
            break;
          case DriveStateOptions::backward:
            setToBackward();
            break;
          case DriveStateOptions::left:
            setToLeft();
            break;
          case DriveStateOptions::right:
            setToRight();
            break;
          case DriveStateOptions::stop:
            setToStop();
            break;
          default:
            break;
        }
      }
    }

    Serial.println("Disconnected to central");

    // Stop the car when the central device disconnects
    setToStop();
  }
}

inline void setToForward() {
  digitalWrite(Pins::frontLeft, HIGH);
  digitalWrite(Pins::frontRight, HIGH);
  digitalWrite(Pins::backLeft, LOW);
  digitalWrite(Pins::backRight, LOW);
}

inline void setToBackward() {
  digitalWrite(Pins::frontLeft, LOW);
  digitalWrite(Pins::frontRight, LOW);
  digitalWrite(Pins::backLeft, HIGH);
  digitalWrite(Pins::backRight, HIGH);
}

inline void setToLeft() {
  digitalWrite(Pins::frontLeft, HIGH);
  digitalWrite(Pins::frontRight, LOW);
  digitalWrite(Pins::backLeft, LOW);
  digitalWrite(Pins::backRight, LOW);
}

inline void setToRight() {
  digitalWrite(Pins::frontLeft, LOW);
  digitalWrite(Pins::frontRight, HIGH);
  digitalWrite(Pins::backLeft, LOW);
  digitalWrite(Pins::backRight, LOW);
}

inline void setToStop() {
  digitalWrite(Pins::frontLeft, LOW);
  digitalWrite(Pins::frontRight, LOW);
  digitalWrite(Pins::backLeft, LOW);
  digitalWrite(Pins::backRight, LOW);
}
