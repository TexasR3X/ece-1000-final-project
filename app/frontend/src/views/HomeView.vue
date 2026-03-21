<script setup lang="ts">
    import router from "@/router";
    import backendService from "@/services/backendService";

    function handleClick() {
        backendService.connectToCar();

        router.push("/control-panel");
    }
</script>

<template>
    <div class="btn-container">
        <button
            id="connect-to-car-btn"
            class="btn"
            @click="handleClick"
        >
            Connect to Car
        </button>
    </div>
</template>

<style scoped>
    .btn-container {
        margin-top: 100px;
        display: flex block;
        justify-content: center;
    }

    .btn {
        font-size: 40px;
        font-weight: bold;
        background-color: #7bdcff;
        padding: 30px;
        border: 0 solid #000000;
        border-radius: 20px;
        cursor: pointer;
    }
</style>
