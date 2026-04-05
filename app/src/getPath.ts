import path from "node:path";

// Get the path to the root of the app
const appRootPath = path.join(import.meta.dirname, "..", "..");

/**
 * Gets the path to a specifc file or directory, with respect to the root of the app
 */
export default function getPath(...paths: string[]): string {
    return path.join(appRootPath, ...paths);
}