/**
 * Take an error message (or error event name) that might not be readable to the user, and make it readable to them.
 */
export default function makeErrorMessageReadable(errorMessage: string): string {
    // Remove whitespace and the substring "Error:" from the error message
    errorMessage = errorMessage.replace(/^\s*Error:\s*(.*)\s*/gi, "$1");

    // Map the error event name to the user readable message
    switch (errorMessage) {
        case "bluetooth-main--car-not-found":
            return "The car couldn't be found. Make sure the car is turned on."
        case "bluetooth-main--bluetooth-off":
            return "Your bluetooth is off. Please turn it on."
        default:
            // If no match is detected, assume its already readable to the user
            return errorMessage;
    }
}
