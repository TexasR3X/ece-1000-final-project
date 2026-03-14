const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("versions", {
    getNode: () => process.versions.node,
    getChrome: () => process.versions.chrome,
    getElectron: () => process.versions.electron
});

contextBridge.exposeInMainWorld("backendConsole", {
    log: (...args) => ipcRenderer.send("log", ...args)
});