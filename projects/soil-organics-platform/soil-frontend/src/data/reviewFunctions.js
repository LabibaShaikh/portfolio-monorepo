import axios from "axios";

// CONSTANTS
const API_HOST = "http://localhost:4000";

// Get number of reviews in the DB
async function getTotalReviews() {
  try {
    const response = await axios.get(`${API_HOST}/api/reviews`);
    return response.data ? response.data.length : 0;
  } catch (error) {
    console.error("Error getting total reviews:", error.message);
    return 0; // Return 0 or handle the error as needed
  }
}

// Get reviews on an item given its itemId
async function getReviews(id) {
  try {
    const response = await axios.get(`${API_HOST}/api/reviews/select/${id}`);
    console.log(id);
    return response.data;
  } catch (error) {
    console.error("Error getting reviews:", error.message);
    return null; // Return null or handle the error as needed
  }
}

// Create a new review
async function addReview(review) {
  try {
    const response = await axios.post(`${API_HOST}/api/reviews`, review);
    return response.data;
  } catch (error) {
    console.error("Error adding review:", error.message);
    return null; // Return null or handle the error as needed
  }
}

// Delete a review
async function removeReview(id) {
  try {
    console.log(id);
    const response = await axios.delete(`${API_HOST}/api/reviews/remove/${id}`);
    return response.data;
  } catch (error) {
    console.error("Error removing review:", error.message);
    return null; // Return null or handle the error as needed
  }
}

// Update a review
async function updateReview(review) {
  try {
    const response = await axios.put(`${API_HOST}/api/reviews`, review);
    return response.data;
  } catch (error) {
    console.error("Error updating review:", error.message);
    return null; // Return null or handle the error as needed
  }
}

export { getReviews, addReview, removeReview, updateReview, getTotalReviews };
