import json

def send_stdout_message(message_type: str, data: str | None = None):
    json_message = {
        "message_type": message_type,
        "message_data": data
    }

    print(json.dumps(json_message), flush=True)

def log_message(message: str):
    send_stdout_message("python-node--log", message)

# def parse_stdin(stdin: str) -> dict:
#     return json.loads(stdin)





# def parse_stdin(line):
#     command = json.loads(line)

#     if command == "log":
#         pass
