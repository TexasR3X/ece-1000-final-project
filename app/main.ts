import { app, BrowserWindow, ipcMain } from "electron";
import { connectToCar } from "./src/bluetooth.js";
import getPath from "./src/getPath.js";
import makeErrorMessageReadable from "./src/makeErrorMessageReadable.js"

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
    ipcMain.handle("frontend-backend--log", (_, ...args: any[]) => console.log(...args));
    ipcMain.handle("frontend-backend--connect-to-car", async () => {
        try {
            const pythonProcess = await connectToCar();

            return null;
        }
        catch (error) {
            const errorMessage = makeErrorMessageReadable((error as any).toString());

            console.error(`ERROR: ${errorMessage}`)

            return errorMessage;
        }
    });

    createWindow();
});

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);
