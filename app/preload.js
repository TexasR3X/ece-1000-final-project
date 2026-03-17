const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("backendAPI", {
    /**
     * Prints to console on the backend.
     * @param  {...any} args 
     * @returns void
     */
    log(...args) {
        ipcRenderer.send("log", ...args);
    },
    /**
     * Gets car's current drive state from the backend.
     * @returns string
     */
    getDriveState() {
        return "";
    },
    /**
     * Sets the car's current drive state on the backend.
     * @param {string} driveState 
     */
    setDriveState(driveState) {}
});