import { createRouter, createWebHistory } from 'vue-router'
import errorView from '../views/error.vue'
import testView from '../views/test.vue'
import templateView from '../views/template.vue'

const routes = [
  { path: '/', name: 'test', component: testView},
  { path: '/:pathMatch(.*)*', name: 'NotFound', component: errorView},
]

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes,
})

export default router
