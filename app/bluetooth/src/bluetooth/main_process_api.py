from datetime import datetime, timezone
import json

def send_stdout_message(message_type: str, message_data: str | None = None):
    json_message = {
        "message_type": message_type,
        "message_data": message_data
    }

    print(json.dumps(json_message), flush=True)

def log_message(message: str):
    # Log the message to a log file
    with open("bluetooth.log", "a") as file:
        date_str = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")

        file.write(f"\n[{date_str}]\n{message}\n")

    # Send the message to the main process
    send_stdout_message("bluetooth-main--log", message)

# def parse_stdin(stdin: str) -> dict:
#     return json.loads(stdin)





# def parse_stdin(line):
#     command = json.loads(line)

#     if command == "log":
#         pass
