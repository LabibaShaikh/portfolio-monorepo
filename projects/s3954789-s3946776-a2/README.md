### Fullstack Assignment 2

## Link to Repositories:
# Soil Organics Website:
https://github.com/rmit-fsd-2024-s1/s3954789-s3946776-a2

# Admin Portal:
https://github.com/rmit-fsd-2024-s1/s3954789-s3946776-a2-HD

## Team Members:
Sadf Gul (s3946776), Shaikh Naima Labiba (s3954789)

## Project Name:
Soil Organics Website

## Running the Project:
# Backend (Express-server):
Open terminal window and run the following commands:
- cd soil-express
- npm install express sequelize mysql2 cors argon2 --save
- node server.js

# React Website:
Open a separate terminal window and run the following commands:
- cd soil-frontend
- npm install react-router-dom@6 axios react-quill --save
- npm install
- npm start

# Unit Tests:
- cd soil-frontend
- cd components
- cd unit-tests
- npm test

# Admin Portal:
Instructions for running the admin portal are available at the repository linked above.

## Project Description:
Soil Organics is an online food-grocer with several stores across Melbourne that brings premium fresh food to the community. This project seeks to offer an updated website to draw more customers to Soil Organic products. Specifically, we aim to enhance the following features of Soil Organic's previous site:
- Promoting high-quality, organic and affordable groceries
- Providing useful information for DIY gardening
- Creating meal plans personalised to each customer's nutrition and dietary needs

After launching their retail webpage online, Soil's customers and business needs have expanded enormously. Amongst the many new requirements for Soil's page are:
 - Gathering customer feedback on their products
 - Moderating and monitoring innappropriate use of the Soil website
 - Managing stock available to customers
 - Adding a range of standard products available for purchase

This project aims to address these new requirements within Soil's existing product. The following features have been added:
- Upon login, a welcome message is displayed on the user's profile
- A set of standard products has been made available for purchase (via the 'Products' link in the navigation bar).
- Users can now create, edit or delete reviews on a product once logged in.
- Should a user wish to, they can follow or unfollow another user through their reviews.
- An admin portal for managing usersa and products of Soil. This enables the following:
    - Blocking/unblocking users: A user who is blocked will be prevented from Signing in.
    - Add/edit/delete standard or sale products. The information stored for each product in the database can be   updated.
    - Reviews can be deleted. Once done: a message is displayed on the website.
    - A display of the most recent reviews submitted
    - Products that have the most reviews.
    - Highest rated products

## Front-End Languages Used:
- React.js
- Node.js
- HTML
- CSS (Raw + Tailwind)

## Back-End Technologies Used:
- MySQL 
- Express
- Apollo Server Express
- Node
- Apollo Server
- Sequelize

