import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  server: {
    proxy: {
      // Intercept requests starting with /test
      '/test': {
        target: 'http://127.0.0.1:8080', 
        changeOrigin: true,
        secure: false,
      }
    }
  }
})