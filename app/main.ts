import { app, BrowserWindow, ipcMain } from "electron";
import getPath from "./src/getPath.js";
import makeErrorMessageReadable from "./src/makeErrorMessageReadable.js"
import { subscribeMainProcessToCleanupEvents } from "./src/cleanupResources.js";
import { BluetoothSubprocess } from "./src/BluetoothSubprocess.js";

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

            const stdioResponse = await bluetoothSubprocess.connectToCar();

            console.log("MAIN: stdioResponse:", stdioResponse);

            if (stdioResponse.message_type === "bluetooth-main--connected-to-car") {
                ipcMain.handle("frontend-main--change-drive-state", async (_, newDriveState: string) => {
                    console.log("MAIN: newDriveState:", newDriveState);

                    await bluetoothSubprocess.changeDriveState(newDriveState);
                });
            }
            else {
                throw new Error(stdioResponse.message_type);
            }

            // Return an error message of null
            return null;
        }
        catch (error) {
            const errorMessage = makeErrorMessageReadable((error as any).toString());

            console.error("MAIN (ERROR):", errorMessage);

            return errorMessage;
        }
    });

    createWindow();
});

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);

// Ensure that the python subprocess is properly cleaned up when the main process ends
subscribeMainProcessToCleanupEvents();
