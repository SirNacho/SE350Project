<template>
  <div class="error-container">
    <h1>...But nobody came.</h1>
    <p>Sorry, the page <strong>"{{ $route.params.pathMatch }}"</strong> does not exist.</p>

    <RouterLink to="/">Take me back home</RouterLink>
  </div>
</template>

<style scoped>
.error-container {
  text-align: center;
  margin-top: 50px;
  font-family: sans-serif;
}
h1 {
  color: #ff4d4d;
}
</style>
