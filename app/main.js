const { app, BrowserWindow, ipcMain } = require("electron/main");
const path = require("path");

// Define how to create a new window for the app
function createWindow() {
    const window = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, "preload.js")
        }
    });

    // Create and open the window
    window.loadFile(path.join(__dirname, "frontend", "index.html"));

    // Open the Chrome developer tools in the window
    window.webContents.openDevTools();
}

// Create a new window when the app opens
app.whenReady().then(() => {
    ipcMain.on("log", (_, ...args) => console.log(...args));

    createWindow();
});

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);
