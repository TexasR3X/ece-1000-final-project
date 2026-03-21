<script setup lang="ts">
    import router from "@/router";
    import backendService from "@/services/backendService";

    function handleClick() {
        backendService.connectToCar();

        router.push("/control-panel");
    }
</script>

<template>
    <div class="container">
        <button @click="handleClick()">Connect to Car</button>
    </div>
</template>

<style scoped>
    .container {
        margin-top: 100px;
        display: flex;
        justify-content: center;
    }

    button {
        font-size: 40px;
        font-weight: bold;
        background-color: #7bdcff;
        padding: 30px;
        border: 0 solid #000000;
        border-radius: 20px;
    }
</style>
