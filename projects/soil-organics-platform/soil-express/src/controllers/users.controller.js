// src/controllers/users.controller.js
const db = require("../database");
const Users = db.users;
const bcrypt = require('bcrypt');

exports.signUp = async (req, res) => {
    try {
      const { email, password, firstName, lastName } = req.body;
      const existingUser = await Users.findOne({ where: { email } });
      if (existingUser) {
        return res.status(409).json({ message: "Email already in use." });
      }
      const hashedPassword = await bcrypt.hash(password, 10);
      const dateOfJoining = new Date();  // Set date of joining to current date
      const newUser = await Users.create({
        email,
        password: hashedPassword,
        firstName,
        lastName,
        dateOfJoining  // Ensure this field is added to your model
      });
      res.status(201).json({ message: "User created successfully", user: newUser });
    } catch (error) {
      console.error("Server Error in signUp:", error);
      res.status(500).json({ message: "Error creating user", error: error.toString() });
    }
  };
  

exports.signIn = async (req, res) => {
  try {
    const { email, password } = req.body;
    const user = await Users.findOne({ where: { email } });
    if (!user) {
      return res.status(404).json({ message: "User not found." });
    }
    const isPasswordValid = await bcrypt.compare(password, user.password);
    if (!isPasswordValid) {
      return res.status(401).json({ message: "Invalid password." });
    }
    if(user.blocked == 1) {
      return res.status(200).json({ message: "User is blocked"});
    }
    res.status(200).json({ message: "Sign in successful", user });
  } catch (error) {
    console.error("Server Error in signIn:", error);
    res.status(500).json({ message: "Error signing in", error: error.toString() });
  }
};

// Get Profile controller function
exports.getProfile = async (req, res) => {
    try {
        const { email } = req.params;
        const user = await Users.findOne({ where: { email } });
        if (!user) {
            return res.status(404).json({ message: "User not found." });
        }
        res.status(200).json(user);
    } catch (error) {
        console.error("Server Error in getProfile:", error);
        res.status(500).json({ message: "Error fetching profile", error: error.toString() });
    }
};

// Update Profile controller function
exports.updateProfile = async (req, res) => {
    try {
        const { email } = req.params;
        const { firstName, lastName, password } = req.body;
        const user = await Users.findOne({ where: { email } });
        if (!user) {
            return res.status(404).json({ message: "User not found." });
        }
        if (password) {
            user.password = await bcrypt.hash(password, 10);
        }
        user.firstName = firstName;
        user.lastName = lastName;
        await user.save();
        res.status(200).json({ message: "Profile updated successfully", user });
    } catch (error) {
        console.error("Server Error in updateProfile:", error);
        res.status(500).json({ message: "Error updating profile", error: error.toString() });
    }
};

// Delete Profile controller function
exports.deleteProfile = async (req, res) => {
    try {
        const { email } = req.params;
        const user = await Users.findOne({ where: { email } });
        if (!user) {
            return res.status(404).json({ message: "User not found." });
        }
        await user.destroy();
        res.status(200).json({ message: "Profile deleted successfully" });
    } catch (error) {
        console.error("Server Error in deleteProfile:", error);
        res.status(500).json({ message: "Error deleting profile", error: error.toString() });
    }
};