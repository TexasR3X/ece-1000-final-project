const connectToCarBtn = document.getElementById("connect-to-car-btn");

connectToCarBtn.addEventListener("click", () => {
    backendApi.log("FRONTEND: Connecting to car.");
    backendApi.connectToCar();
});
