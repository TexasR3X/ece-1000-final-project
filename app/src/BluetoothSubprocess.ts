import { spawn, type ChildProcessWithoutNullStreams } from "node:child_process";
import getPath from "./getPath.js";

export const allSubprocesses: ChildProcessWithoutNullStreams[] = [];

interface StdioMessageObject {
    message_type: string;
    message_data: string;
}

export default class BluetoothSubprocess {
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

        // Return the process
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

        /*
        function changeDriveState(pythonProcess: ChildProcessWithoutNullStreams, newDriveState: string) {
            const jsonMessage = {
                message_type: "node-python--set-drive-state",
                message_data: newDriveState
            };

            pythonProcess.stdin.write(JSON.stringify(jsonMessage));
        }
        */
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
                                    console.log(`BLUETOOTH: ${stdoutObject.message_data}`);
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
        await this.waitForStdout();
    }
}



// class SubprocessService {
//     public createSubprocess(): ChildProcessWithoutNullStreams {
//         // Get the paths to the python executable and python root folder
//         const pathToPythonExecutable = getPath("bluetooth", ".venv", "bin", "python");
//         const pathToPythonProjectRoot = getPath("bluetooth");

//         // Create the python process that will connect with the car, via bluetooth
//         const pythonSubprocess = spawn(pathToPythonExecutable, ["-m", "src.bluetooth.main"], {
//             cwd: pathToPythonProjectRoot
//         });

//         // Add the process to the array of all subprocesses
//         allSubprocesses.push(pythonSubprocess);

//         // Return the process
//         return pythonSubprocess;
//     }

//     public 

//     public subscribeMainProcessToCleanupEvents() {
//         // Declare an event handler to handle cleaning up subprocesses
//         function cleanupSubprocesses() {
//             allSubprocesses.forEach(subprocess => subprocess.kill("SIGTERM"));
//         }
        
//         // Register the main process use the event handler above
//         process.on("exit", cleanupSubprocesses);
//         process.on("SIGINT", cleanupSubprocesses);
//         process.on("SIGTERM", cleanupSubprocesses);
//         process.on("uncaughtException", cleanupSubprocesses);
//     }
// }

// export const subprocessService = new SubprocessService();
