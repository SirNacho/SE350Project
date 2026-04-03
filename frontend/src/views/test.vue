<script setup lang="ts">
import { ref, onMounted, onUnmounted } from 'vue'

const backendMessage = ref('Loading message from server...')
const backendStatus = ref(false)
let pollingInterval: number | undefined

const checkBackendStatus = async () => {
  try {
    const response = await fetch('/test')

    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`)
    }

    const text = await response.text()

    if (text.trim() === "Hello SE350! The backend is running!") {
      backendStatus.value = true
      backendMessage.value = text.trim()
    } else {
      throw new Error(`Connected, but received unexpected string: "${text}"`)
    }

  } catch (error) {
    console.error("Status check failed")
    backendStatus.value = false
    backendMessage.value = "Failed to connect. Is Spring Boot running?"
  }
}

onMounted(() => {
  checkBackendStatus()
  pollingInterval = setInterval(checkBackendStatus, 3000)
})

onUnmounted(() => {
  if (pollingInterval) {
    clearInterval(pollingInterval)
  }
})
</script>

<template>
  <div class="page-content">
    <h2>Connection Dashboard</h2>

    <div class="status-box success-box" v-if="backendStatus">
      <h3>Spring Boot Status</h3>
      <p style="color: #42b883">
        {{ backendMessage }}
      </p>
    </div>

    <div class="status-box error-box" v-else>
      <h3>Spring Boot Status</h3>
      <p style="color: #ff5555">
        {{ backendMessage }}
      </p>
    </div>
  </div>
</template>

<style scoped>
.page-content {
  padding-top: 50px;
  padding-left: 20px;
  padding-right: 20px;
}

.status-box {
  margin-bottom: 30px;
  padding: 15px;
  border: 2px solid #b088f9;
  border-radius: 8px;
  background-color: rgba(0, 0, 0, 0.5);
  transition: border-color 0.3s ease;
}

.success-box {
  border-color: #42b883;
}

.error-box {
  border-color: #ff5555;
}

h2, h3 {
  color: white;
  margin-bottom: 10px;
}
</style>