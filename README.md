# SE 350 Project
[![build and test](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml/badge.svg)](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml)
[![Spring Boot Version](https://img.shields.io/badge/dynamic/xml?color=6db33f&url=https://raw.githubusercontent.com/SirNacho/SE350Project/main/backend/pom.xml&query=%2F%2A%5Blocal-name%28%29%3D%27project%27%5D%2F%2A%5Blocal-name%28%29%3D%27parent%27%5D%2F%2A%5Blocal-name%28%29%3D%27version%27%5D&label=Spring%20Boot&logo=springboot)](https://spring.io/projects/spring-boot)
[![Java Version](https://img.shields.io/badge/dynamic/xml?color=ed8b00&url=https://raw.githubusercontent.com/SirNacho/SE350Project/main/backend/pom.xml&query=%2F%2A%5Blocal-name%28%29%3D%27project%27%5D%2F%2A%5Blocal-name%28%29%3D%27properties%27%5D%2F%2A%5Blocal-name%28%29%3D%27java.version%27%5D&label=Java&logo=java)](https://www.oracle.com/java/)
[![Vue.js Version](https://img.shields.io/badge/dynamic/json?color=4fc08d&url=https://raw.githubusercontent.com/SirNacho/SE350Project/main/frontend/package.json&query=$.dependencies.vue&label=Vue.js&logo=vue.js)](https://vuejs.org/)
[![TypeScript Version](https://img.shields.io/badge/dynamic/json?color=3178c6&url=https://raw.githubusercontent.com/SirNacho/SE350Project/main/frontend/package.json&query=$.devDependencies.typescript&label=TypeScript&logo=typescript)](https://www.typescriptlang.org/)

| Hi, welcome to my git repo for my SE 350 project!

# Full stack setup:
- Frontend: Vue.js
- Backend: Spring Boot


# Requirements:
## Backend Requirements:
- Hosts: Linux on X86 (Recommended)
- Java Version: 21
- Project Type: Maven

## Frontend Requirements:
- Hosts: Linux on X86 (Recommended)
- NPM Version: 25.8.2
- Uses CSS and TypeScript

# How to Run:
## Backend:
Cd in the backend directory: 
```
cd backend
```
Install the maven dependencies:
```
mvn clean install
```
Run the spring boot application (preferably in the background):
```
mvn spring-boot:run
```

## Frontend:
Cd in the frontend directory:
```
cd frontend
```
Install npm packages:
```
npm install
```
Run the frontend application (preferably in the background):
```
npm run preview
```
(Optional) Or run the frontend with --host to expose it:
```
npm run preview -- --host
```
