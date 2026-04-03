# SE 350 Project
Hi, welcome to my git repo for my SE 350 project!

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
