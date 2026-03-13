const { app, BrowserWindow } = require("electron/main");
const path = require("path");

// Define how to create a new window for the app
function createWindow() {
    const window = new BrowserWindow({
        width: 800,
        height: 600
    });

    window.loadFile(path.join(".", "frontend", "index.html"));
}

// Create a new window when the app opens
app.whenReady().then(createWindow);

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);
