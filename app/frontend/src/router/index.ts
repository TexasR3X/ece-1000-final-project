import { createRouter, createWebHashHistory } from "vue-router";
import HomeView from "../views/HomeView.vue";
import ControlPanel from "@/views/ControlPanel.vue";

const router = createRouter({
    history: createWebHashHistory(import.meta.env.BASE_URL),
    routes: [
        {
            path: "/",
            name: "home",
            component: HomeView
        },
        {
            path: "/control-panel",
            name: "control-panel",
            component: ControlPanel
        },
    ],
});

export default router;
