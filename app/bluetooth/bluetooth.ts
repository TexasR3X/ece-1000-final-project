import noble from "@stoprocent/noble";

export async function runBluetooth() {
    // Discover peripherals as an async generator
    try {
        // Wait for Adapter poweredOn state
        await noble.waitForPoweredOnAsync();
        // Start scanning first
        await noble.startScanningAsync();
        
        // Use the async generator with proper boundaries
        for await (const peripheral of noble.discoverAsync()) {
            console.log(`Found device: ${peripheral.advertisement.localName || "Unknown"}`);
            // Process the peripheral as needed
            
            // Optional: stop scanning when a specific device is found
            if (peripheral.advertisement.localName === "MyDevice") {
                break;
            }
        }
        
        // Clean up after discovery
        await noble.stopScanningAsync();
    }
    catch (error) {
        console.error("Discovery error:", error);
        await noble.stopScanningAsync();
    }
}
