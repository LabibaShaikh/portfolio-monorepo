// src/routes/users.routes.js
const express = require('express');
const router = express.Router();
const userController = require('../controllers/users.controller');

router.post('/signup', userController.signUp);
router.post('/signin', userController.signIn);
router.get('/profile/:email', userController.getProfile); // Get user profile
router.put('/profile/:email', userController.updateProfile); // Update user profile
router.delete('/profile/:email', userController.deleteProfile); // Delete user profile
module.exports = router;
