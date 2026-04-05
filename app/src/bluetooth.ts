import { spawn, type ChildProcessWithoutNullStreams } from "node:child_process";
import getPath from "./getPath.js";

/**
 * Attempt to connect to the car.
 */
export function connectToCar(): Promise<ChildProcessWithoutNullStreams> {    
    return new Promise((resolve, reject) => {
        try {
            // Get the path to the python executable
            const pathToPythonExecutable = getPath("bluetooth", ".venv", "bin", "python");

            // Create the python process that will connect with the car, via bluetooth
            const pythonProcess = spawn(pathToPythonExecutable, ["-m", "src.bluetooth.main"], {
                cwd: getPath("bluetooth")
            });

            // Declare a variable to hold the stdout from Python
            let pythonStdout = "";

            // Listen to the stdout from Python
            function handleStdout(stdoutChunk: string) {
                try {
                    // Attach the data from the stdout, turn it to the string, and store it in `pythonStdout`
                    pythonStdout += stdoutChunk.toString();

                    // Split stdout into different lines
                    const lines = pythonStdout.split("\n");

                    // Remove the last line from `lines` and set `pythonStdout` equal to it
                    pythonStdout = lines.pop() ?? "";

                    // Print each line from Python's stdout
                    for (const line of lines) {
                        if (line.trim()) {
                            // Parse the line of stdout
                            const messageFromPython = JSON.parse(line);

                            // Handle the specific message from the Python process
                            switch (messageFromPython.message_type) {
                                case "python-node--log":
                                    console.log(`PYTHON: ${messageFromPython.message_data}`);
                                    break;
                                case "python-node--connected-to-car":
                                    pythonProcess.stdout.off("data", handleStdout);
                                    resolve(pythonProcess);
                                    break;
                                case "python-node--unknown-error":
                                    console.error("PYTHON ERROR:", messageFromPython.message_data);
                                case "python-node--car-not-found":
                                case "python-node--bluetooth-off":
                                    throw new Error(messageFromPython.message_type);
                                default:
                                    throw new Error(`Unrecogized type for messageFromPython. In other words, messageFromPython.message_type = ${messageFromPython.message_type}.`);
                            }
                        }
                    }
                }
                catch (err) {
                    // Stop listening to this event
                    pythonProcess.stdout.off("data", handleStdout);

                    // If an error occures, reject the promise and throw an error in the code where this function is called
                    reject(err);
                }
            }
            pythonProcess.stdout.on("data", handleStdout);
        }
        catch (err) {
            reject(err);
        }
    });
}
