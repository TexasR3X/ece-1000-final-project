import asyncio
from bleak import BleakScanner, BleakClient
from bleak.exc import BleakBluetoothNotAvailableError
from bleak.backends.service import BleakGATTService
from .main_process_api import send_stdout_message, log_message
import sys
import json

DEVICE_NAME = "ArduinoCar"
DRIVE_SERVICE_UUID = "678630d9-bbb4-4867-af2e-fb51af7097da"

# async def main():
#     for stdin in sys.stdin:
#         # Parse the stdin
#         message_object = json.loads(stdin)

#         if message_object.message_type == "main-bluetooth--connect-to-car":
#             await connect_to_car()
#         else:
#             log_message(f"Unknown message_type ({message_object.message_type})")

#         # print(f"data: -->{parsed_stdin}<--")
#         # log_message(f"TEMP data: {parsed_stdin}")

async def main():
    try:
        log_message("Searching for car...")
        devices = await BleakScanner.discover()

        target_device = None

        for device in devices:
            log_message(f"Found Device: {device}")

            if device.name == DEVICE_NAME:
                target_device = device
                break
        else:
            send_stdout_message("bluetooth-main--car-not-found")
            return

        log_message("Connecting to car...")

        async with BleakClient(target_device) as peripheral_device:
            send_stdout_message("bluetooth-main--connected-to-car")

            drive_service = peripheral_device.services.get_service(DRIVE_SERVICE_UUID)

            if drive_service == None:
                raise Exception("Car doesn't have the drive service.")

            log_message(f"drive_service: {drive_service}")

            wait_for_stdin(drive_service)

    except BleakBluetoothNotAvailableError:
        send_stdout_message("python-node--bluetooth-off")
        # log_message("Error: Bluetooth cannot be used. This device likely has it turned off.")

    except Exception as ex:
        send_stdout_message("python-node--unknown-error", str(ex))
        # log_message(f"Error: {ex}")

def wait_for_stdin(drive_service: BleakGATTService):
    for stdin in sys.stdin:
        # Parse the stdin
        message_object = json.loads(stdin)

        if message_object.message_type == "main-bluetooth--change-drive-state":
            log_message("Change the drive state!")
        else:
            log_message(f"Unknown message_type ({message_object.message_type})")

        log_message(f"TEMP data: {message_object}")

if __name__ == "__main__":
    asyncio.run(main())
