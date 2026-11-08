# Airbnb-like Application Setup Instructions

**Name:** Shaikh Naima Labiba  
**Student Number:** s3954789  

## Prerequisites:
- Node.js installed  
- MongoDB account and database set up  
- npm (Node Package Manager)  

# Airbnb-like Application Setup Instructions

**Name:** Shaikh Naima Labiba  
**Student Number:** s3954789  

## Prerequisites:
- Node.js installed  
- MongoDB account and database set up  
- npm (Node Package Manager)  

## Setup Steps:

1. **Install Dependencies:**
   ```bash
   npm install
   ```

2. **Environment Setup:**
   - Create a file named `.env` in the root directory.
   - Add the following content to `.env`:
     ```env
     PORT=3000
     MONGO_URI=your_mongodb_connection_string_here
     ```
   - Replace `your_mongodb_connection_string_here` with your actual MongoDB connection string.

3. **Start the Server:**
   ```bash
   npm start
   ```
   or
   ```bash
   node server.js
   ```

4. **Access the Application:**
   - Open your browser and go to [http://localhost:3000](http://localhost:3000).
   - The frontend files are served from the `public/` directory.
   - The API endpoints are available at `/api` routes.

## Directory Structure:
- `public/`      : Contains all frontend HTML, CSS, and JavaScript files
- `server.js`    : Main server file running Express.js backend
- `.env`         : Environment variables (MongoDB connection string)
- `package.json` : Project dependencies and scripts

**Note:** Make sure MongoDB is running and accessible before starting the server.

