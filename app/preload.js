const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("mainContextBridge", {
    /**
     * Prints to console on the main process.
     * @param {...any} args
     */
    log(...args) {
        return ipcRenderer.invoke("frontend-main--log", ...args);
    },
    /**
     * Have the main process attempt to connect to the car.
     */
    connectToCar() {
        this.log("Connecting to car.");
        return ipcRenderer.invoke("frontend-main--connect-to-car");
    },
    /**
     * Gets car's current drive state from the main process.
     * @returns string
     */
    getDriveState() {
        return "";
    },
    /**
     * Sets the car's current drive state on the main process.
     * @param {string} driveState 
     */
    setDriveState(driveState) {
        this.log(`Changing state to ${driveState}.`);
        return ipcRenderer.invoke("frontend-main--change-drive-state", driveState);
    }
});
