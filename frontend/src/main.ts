import { createApp } from 'vue'
import App from './App.vue'
import router from './router'

import 'nes.css/css/nes.min.css'
import 'snes.css/dist/snes.min.css'
import './assets/main.css'

const app = createApp(App)
app.use(router)
app.mount('#app')
