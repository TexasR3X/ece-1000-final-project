import type { ChildProcessWithoutNullStreams } from "node:child_process";

const subprocesses: ChildProcessWithoutNullStreams[] = [];

export function registerProcessForCleanup(subprocess: ChildProcessWithoutNullStreams) {
    subprocesses.push(subprocess);
}

function cleanupResources() {
    console.log("Cleaning up...");

    subprocesses.forEach(subprocess => {
        console.log("subprocess.pid:", subprocess.pid);
        subprocess.kill("SIGTERM");
    });
}

export function subscribeMainProcessToCleanupEvents() {
    process.on("exit", cleanupResources);
    process.on("SIGINT", cleanupResources);
    process.on("SIGTERM", cleanupResources);
    process.on("uncaughtException", cleanupResources);
}
