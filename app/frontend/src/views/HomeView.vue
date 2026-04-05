<script setup lang="ts">
    import router from "@/router";
    import backendService from "@/services/backendService";
    import { ref } from "vue";

    // Set up the inital look of the error message and button
    const displayedErrorMessage = ref<string | null>(null);
    const btnDisabled = ref(false);
    const btnText = ref("Connect to Car");

    async function handleClick() {
        if (!btnDisabled.value) {
            // Display the button as "Connecting..."
            btnDisabled.value = true;
            displayedErrorMessage.value = null;
            btnText.value = "Connecting...";

            // Attempt to connect to the car
            const errorMessage: string = await backendService.connectToCar();

            if (errorMessage) {
                // Display the error message, and format the button properly
                btnDisabled.value = false;
                displayedErrorMessage.value = errorMessage;
                btnText.value = "Try Again?";
            }
            else {
                // Move the user to the following page
                router.push("/control-panel");
            }
        }
    }
</script>

<template>
    <div class="container flex-center">
        <div
            class="error-message-container flex-center"
            :style="{ display: displayedErrorMessage ? 'flex' : 'none' }"
        >
            <div class="error-message">{{ displayedErrorMessage }}</div>
        </div>
        <div class="btn-container flex-center">
            <button
                @click="handleClick()"
                :class="{ 'btn-disabled': btnDisabled }"
            >
                {{ btnText }}
            </button>
        </div>
    </div>
</template>

<style scoped>
    .container {
        margin-top: 100px;
        flex-direction: column;
        gap: 10px;
    }

    .flex-center {
        display: flex;
        justify-content: center;
    }

    .error-message {
        font-size: 20px;
        font-weight: bold;
        background-color: #ffc16f;
        padding: 20px;
        border: 0 solid #000000;
        border-radius: 20px;
    }

    button {
        font-size: 40px;
        font-weight: bold;
        background-color: #7bdcff;
        padding: 30px;
        border: 0 solid #000000;
        border-radius: 20px;
    }

    .btn-disabled {
        background-color: #d8f5ff
    }
</style>
