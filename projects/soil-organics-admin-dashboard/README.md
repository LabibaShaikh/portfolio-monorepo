# Admin Dashboard Project

## Students:
Shaikh Naima Labiba (s3954789)
Sadf Gul (s3946776)

## Introduction
This project involves creating an Admin Dashboard with separate projects for the React front-end and the GraphQL back-end. The dashboard is designed to manage user accounts, products, and reviews, and it includes real-time updates using GraphQL subscriptions. The data is fetched from a Cloud MySQL database.



## Project Structure
### Frontend (React)

admin-dashboard/
├── public/
├── src/
│ ├── components/
│ │ ├── Dashboard.js
│ │ ├── Header.js
│ │ ├── Home.js
│ │ ├── Sidebar.js
│ │ ├── UserManagement.js
│ │ ├── ProductManagement.js
│ │ ├── ReviewModeration.js
│ ├── App.js
│ ├── index.js
│ ├── tailwind.css
├── package.json
└── tailwind.config.js


### Backend (Node.js / GraphQL)
admin-backend/
├── src/
│ ├── schema/
│ │ ├── typeDefs.js
│ │ ├── resolvers.js
│ ├── models/
│ │ ├── User.js
│ │ ├── Product.js
│ │ ├── Review.js
│ ├── index.js
│ ├── db.js
├── package.json


## Installation

### Frontend
1. Install Tailwind CSS:
    ```sh
    npm install -D tailwindcss postcss autoprefixer
    npx tailwindcss init -p
    npm install tailwindcss
    ```

2. Install Recharts and React Icons for chart creation:
    ```sh
    npm install recharts react-icons
    ```

### Backend
1. Install necessary packages:
    ```sh
    npm install express apollo-server-express graphql sequelize mysql2
    ```

2. For graph subscriptions:
    ```sh
    npm install subscriptions-transport-ws graphql-ws
    npm install date-fns@latest
    ```

## Running the Projects

### Frontend
1. Navigate to the `admin-dashboard` directory.
2. Start the React application:
    ```sh
    npm start
    ```

### Backend
1. Navigate to the `admin-backend` directory.
2. Start the GraphQL server:
    ```sh
    node src/server.js
    ```

## Features

### User Management
- Block/unblock a user.
- Add/edit/delete standard and special products.

### Review Moderation
- Delete inappropriate reviews with a corresponding message on the reviews page: "[**** This review has been deleted by the admin ***]".

### Real-time Updates
- Dynamic display of the most recent reviews submitted by users, showing the latest two or three reviews.
- Two distinct metrics related to reviews or user engagement with products, presented visually.

## Explanation of Metrics
1. **Recent Reviews**: Displaying the latest reviews helps the admin monitor new feedback and take prompt action if needed.
2. **User Engagement Metrics**: These metrics provide insights into user interactions with products, helping the admin understand trends and make informed decisions. A bar chart that shows the relationship between the most reviewed, highest reviewed and the number of reviews and a pie chart showing the ratio between reviewed products and rated products 

## Tutorials Followed
1. [React Admin Dashboard Tutorial](https://www.youtube.com/watch?v=pWd29MtFGJA)
2. [GraphQL Subscriptions Tutorial](https://www.youtube.com/watch?v=j0F0l_bvAyU)
3. [Recharts Tutorial](https://www.youtube.com/watch?v=Ou-rZsXRciI&list=PLwHsNjmBZ-MJnVNyiaVYHW_dDA5n3mbVk)

## Graphs Sourced From
- [Recharts - Two Level Pie Chart](https://recharts.org/en-US/examples/TwoLevelPieChart)

## Scenarios for Deleting Reviews
1. **Offensive Language**: Reviews containing offensive or inappropriate language will be deleted.
2. **Spam**: Reviews that are clearly spam or promotional content.
3. **Irrelevant Content**: Reviews that do not pertain to the product or service being reviewed.

These scenarios ensure that the review section remains clean, relevant, and helpful for all users.