const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("backendContextBridge", {
    /**
     * Prints to console on the backend.
     * @param {...any} args
     */
    log(...args) {
        return ipcRenderer.invoke("frontend-backend--log", ...args);
    },
    /**
     * Have the backend attempt to connect to the car.
     */
    connectToCar() {
        this.log("FRONTEND: Connecting to car.");
        return ipcRenderer.invoke("frontend-backend--connect-to-car");
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
    setDriveState(driveState) {
        this.log(`FRONTEND: Changing state to ${driveState}.`);
        return ipcRenderer.invoke("frontend-backend--change-drive-state");
    }
});
