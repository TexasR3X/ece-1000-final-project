import { allSubprocesses } from "./BluetoothSubprocess.js";

function cleanupResources() {
    allSubprocesses.forEach(subprocess => subprocess.kill("SIGTERM"));
}

export function subscribeMainProcessToCleanupEvents() {
    process.on("exit", cleanupResources);
    process.on("SIGINT", cleanupResources);
    process.on("SIGTERM", cleanupResources);
    process.on("uncaughtException", cleanupResources);
}
