<script setup lang="ts">
</script>

<template>
  <div id="app-layout">
    <main>
      <router-view></router-view>
    </main>

    <footer>
      <nav class="footer-nav">
        <router-link to="/">Test</router-link>
        <!-- <router-link to="/test">Test</router-link> -->
      </nav>
      <p class="copyright">&copy; 2026 Sir Nacho</p>
    </footer>

  </div>
</template>

<style scoped>
.header-content {
  display: flex;
  justify-content: flex-end;
}

.footer-nav {
  margin-bottom: 10px;
  font-size: 1.2rem;
  font-weight: bold;
}

.footer-nav a {
  margin: 0 10px;
  transition: text-shadow 0.3s ease;
}

.footer-nav a:hover {
  text-shadow: 0 0 8px #b088f9;
}

.copyright {
  font-size: 0.9rem;
  opacity: 0.7;
  margin: 0;
}
</style>
