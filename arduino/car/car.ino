// Note: Small portions of this sketch were based on the work of Lee Curiosity
//   - The functions `setToForward()`, `setToBackward()`, `setToLeft()`, `setToRight()`, and `setToStop()` were based on this work
//   - See https://projecthub.arduino.cc/lee_curiosity/a-beginners-guide-controlling-an-arduino-car-with-a-remote-5d4418

#include <ArduinoBLE.h>

// Store the drive state options
namespace DriveStateOptions {
  const uint8_t forward = 0;
  const uint8_t backward = 1;
  const uint8_t left = 2;
  const uint8_t right = 3;
  const uint8_t stop = 4;
}

// Create the driveService with its driveStateCharacteristic
const char* driveServiceUuid = "678630d9-bbb4-4867-af2e-fb51af7097da";
BLEService driveService(driveServiceUuid);
BLEByteCharacteristic driveStateCharacteristic(driveServiceUuid, BLEWrite);

void setup() {
  Serial.println("Test0");
  pinMode(LED_BUILTIN, OUTPUT);

  //
  driveService.addCharacteristic(driveStateCharacteristic);

  // Set the inital value of driveStateCharacteristic to be STOP
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
}

void loop() {
  // Get a reference to the central device (if any) connected to this peripheral device
  BLEDevice central = BLE.central();
  Serial.println("Test");

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
  digitalWrite(LED_BUILTIN, HIGH);
}

inline void setToBackward() {
  digitalWrite(LED_BUILTIN, LOW);
}

inline void setToLeft() {
  digitalWrite(LED_BUILTIN, LOW);
}

inline void setToRight() {
  digitalWrite(LED_BUILTIN, LOW);
}

inline void setToStop() {
  digitalWrite(LED_BUILTIN, LOW);
}
