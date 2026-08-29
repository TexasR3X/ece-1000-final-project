import { app, BrowserWindow, ipcMain } from "electron";
import { connectToCar, changeDriveState } from "./src/bluetooth.js";
import getPath from "./src/getPath.js";
import makeErrorMessageReadable from "./src/makeErrorMessageReadable.js"
import { subscribeMainProcessToCleanupEvents } from "./src/cleanupResources.js";
import BluetoothSubprocess from "./src/BluetoothSubprocess.js";

// Define how to create a new window for the app
function createWindow() {
    const window = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: getPath("preload.js")
        }
    });

    // Create and open the window
    window.loadFile(getPath("frontend", "dist", "index.html"));

    // Open the Chrome developer tools in the window
    window.webContents.openDevTools();
}

// Create a new window when the app opens
app.whenReady().then(() => {
    ipcMain.handle("frontend-main--log", (_, ...args: any[]) => console.log("FRONTEND:", ...args));

    ipcMain.handle("frontend-main--connect-to-car", async () => {
        try {
            // Create the bluetooth subprocess
            const bluetoothSubprocess = new BluetoothSubprocess();

            bluetoothSubprocess.connectToCar();

            ipcMain.handle("frontend-backend--change-drive-state", (_, newDriveState: string) => {

            });





            // // Connect to the car, and get a reference to the python process that is connected to it
            // const pythonProcess = await connectToCar();

            // // Add an event listener to change the drive state through the python process
            // ipcMain.handle("frontend-backend--change-drive-state", (_, newDriveState: string) => {
            //     changeDriveState(pythonProcess, newDriveState);
            // });

            // // Return an error message of null
            // return null;
        }
        catch (error) {
            const errorMessage = makeErrorMessageReadable((error as any).toString());

            console.error(`ERROR: ${errorMessage}`);

            return errorMessage;
        }
    });

    createWindow();
});

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);

// Ensure that the python subprocess is properly cleaned up when the main process ends
subscribeMainProcessToCleanupEvents();
