import asyncio
import bleak
import bleak.exc
from src.bluetooth.node_api import send_specific_message, log_message
import sys
import json

DEVICE_NAME = "ArduinoCar"
DRIVE_SERVICE_UUID = "678630d9-bbb4-4867-af2e-fb51af7097da"

async def main():
    try:
        log_message("Searching for car...")
        devices = await bleak.BleakScanner.discover()

        target_device = None

        for device in devices:
            log_message(f"Found Device: {device}")

            if device.name == DEVICE_NAME:
                target_device = device
                break
        else:
            send_specific_message("python-node--car-not-found")
            return

        log_message("Connecting to car...")

        async with bleak.BleakClient(target_device) as peripheral:
            send_specific_message("python-node--connected-to-car")

            drive_service = peripheral.services.get_service(DRIVE_SERVICE_UUID)

            if drive_service == None:
                raise Exception("Car doesn't have the drive service.")
            
            log_message(f"drive_service: {drive_service}")

            # for json_message in sys.stdin:
            #     data = json.loads(json_message)
            #     log_message(f"data: {data}")

    except bleak.exc.BleakBluetoothNotAvailableError:
        send_specific_message("python-node--bluetooth-off")
        # log_message("Error: Bluetooth cannot be used. This device likely has it turned off.")

    except Exception as ex:
        send_specific_message("python-node--unknown-error", str(ex))
        # log_message(f"Error: {ex}")

if __name__ == "__main__":
    log_message("Start Python Process")

    asyncio.run(main())

    log_message("End Python Process")
