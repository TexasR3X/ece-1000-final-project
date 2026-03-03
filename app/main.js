const { app, BrowserWindow } = require("electron/main");

// Define how to create a new window for the app
function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600
    });

    win.loadFile("index.html");
}

// Create a new window when the app opens
app.whenReady().then(createWindow);

// Quite the app when every window closes (for every OS)
app.on("window-all-closed", app.quit);


// app.whenReady().then(() => {
//     createWindow();

//     app.on("activate", () => {
//         if (BrowserWindow.getAllWindows().length === 0) {
//             createWindow();
//         }
//     });
// });

// app.on("window-all-closed", () => {
//     if (process.platform !== "darwin") {
//         app.quit();
//     }
// });
