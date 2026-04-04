<script setup lang="ts">
    import backendService from "@/services/backendService";
</script>

<template>
    <div class="component-container">
        <div class="grid-container">
            <!-- Top Row -->
            <div class="empty-grid-cell"></div>
            <button class="forward-btn" @click="backendService.setDriveState(`FORWARD`)">Forward</button>
            <div class="empty-grid-cell"></div>
            <!-- Middle Row -->
            <button class="left-btn" @click="backendService.setDriveState(`LEFT`)">Left</button>
            <button class="stop-btn" @click="backendService.setDriveState(`STOP`)">Stop</button>
            <button class="right-btn" @click="backendService.setDriveState(`RIGHT`)">Right</button>
            <!-- Bottom Row -->
            <div class="empty-grid-cell"></div>
            <button class="backward-btn" @click="backendService.setDriveState(`BACKWARD`)">Backward</button>
            <div class="empty-grid-cell"></div>
        </div>
    </div>
</template>

<style scoped>
    .component-container {
        margin-top: 100px;
        display: flex;
        justify-content: center;
    }

    .grid-container {
        width: 400px;
        display: grid;
        grid-template-columns: 3fr 3fr 3fr;
        gap: 10px;
    }

    button {
        font-size: 40px;
        font-weight: bold;
        background-color: #7bdcff;
        padding: 10px;
        border: 0 solid #000000;
        border-radius: 20px;
    }
</style>
