import { spawn, type ChildProcessWithoutNullStreams } from "node:child_process";
import getPath from "./getPath.js";

export const allSubprocesses: ChildProcessWithoutNullStreams[] = [];

interface StdioMessageObject {
    message_type: string;
    message_data: string;
}

export class BluetoothSubprocess {
    public subprocess: ChildProcessWithoutNullStreams;

    public constructor() {
        // Get the paths to the python executable and python root folder
        const pathToPythonExecutable = getPath("bluetooth", ".venv", "bin", "python");
        const pathToPythonProjectRoot = getPath("bluetooth");

        // Create the python process that will connect with the car, via bluetooth
        const pythonSubprocess = spawn(pathToPythonExecutable, ["-m", "src.bluetooth.main"], {
            cwd: pathToPythonProjectRoot
        });

        // Add the process to the array of all subprocesses
        allSubprocesses.push(pythonSubprocess);

        // Subscribe to the "error" event on the subprocess
        pythonSubprocess.on("error", error => console.error("MAIN (ERROR):", error));

        // Store a reference to this process
        this.subprocess = pythonSubprocess;
    }

    public sendStdin(messageType: string, messageData: string = "") {
        // Create the stdout object to send to the bluetooth subprocess
        const stdinObject: StdioMessageObject = {
            message_type: messageType,
            message_data: messageData
        };

        // Send the message to the stdin
        this.subprocess.stdin.write(JSON.stringify(stdinObject));
    }

    public waitForStdout(): Promise<StdioMessageObject> {
        return new Promise((resolve, reject) => {
            try {
                // Declare a variable to hold the stdout from the subprocess
                let stdout = "";

                // Declare event handler for the stdout
                const handleStdout = (stdoutChunk: string) => {
                    try {
                        // Attach the data from the stdout, turn it to the string, and store it in `stdoutChunck`
                        stdout += stdoutChunk.toString();

                        // Split stdout into different lines
                        const linesOfStdout = stdout.split("\n");

                        // Remove the last line from `linesOfStdout` and save it in `stdout`
                        stdout = linesOfStdout.pop() ?? "";

                        // Print each line from Python's stdout
                        for (const jsonLine of linesOfStdout) {
                            if (jsonLine.trim()) {
                                // Parse the line of stdout
                                const stdoutObject: StdioMessageObject = JSON.parse(jsonLine);

                                if (stdoutObject.message_type == "bluetooth-main--log") {
                                    // Log the message from the subprocess, and keep listening for stdout
                                    console.log("BLUETOOTH:", stdoutObject.message_data);
                                }
                                else {
                                    // Stop listening for stdout, and return the message object
                                    this.subprocess.stdout.removeListener("data", handleStdout);
                                    resolve(stdoutObject);
                                }
                            }
                        }
                    }
                    catch (error) {
                        // Stop listening to this event
                        this.subprocess.stdout.removeListener("data", handleStdout);

                        // If an error occures, reject the promise and throw an error in the code where this function is called
                        reject(error);
                    }
                }

                // Listen for and handle the stdout
                this.subprocess.stdout.on("data", handleStdout);
            }
            catch (error) {
                // If an error occures, reject the promise and throw an error in the code where this function is called
                reject(error);
            }
        });
    }

    public async connectToCar() {
        // Send a message to the bluetooth subprocess, asking it to connect to the Arduino
        this.sendStdin("main-bluetooth--connect-to-car");

        // Wait for conformation of the subprocess's connection
        return await this.waitForStdout();
    }

    public async changeDriveState(newDriveState: string) {
        // Send a message to the bluetooth subprocess, asking it to change the drive state
        this.sendStdin("main-bluetooth--change-drive-state", newDriveState);

        // Wait for conformation of the update from the subprocess
        await this.waitForStdout();
    }
}
