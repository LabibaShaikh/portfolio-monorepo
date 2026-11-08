// src/data/userAPI.js
import axios from "axios";

const API_HOST = "http://localhost:4000";

async function signUp(userData) {
    try {
        const response = await axios.post(`${API_HOST}/api/users/signup`, userData);
        return response.data;
    } catch (error) {
        console.error('API call to signUp failed:', error.response ? error.response.data : error.message);
        throw error;
    }
}

async function signIn(userData) {
    try {
        const response = await axios.post(`${API_HOST}/api/users/signin`, userData);
        return response.data;
    } catch (error) {
        console.error('API call to signIn failed:', error.response ? error.response.data : error.message);
        throw error;
    }
}

async function getProfile(email) {
    try {
        const response = await axios.get(`${API_HOST}/api/users/profile/${email}`);
        return response.data;
    } catch (error) {
        console.error('API call to getProfile failed:', error.response ? error.response.data : error.message);
        throw error;
    }
}

async function updateProfile(email, profileData) {
    try {
        const response = await axios.put(`${API_HOST}/api/users/profile/${email}`, profileData);
        return response.data;
    } catch (error) {
        console.error('API call to updateProfile failed:', error.response ? error.response.data : error.message);
        throw error;
    }
}

async function deleteProfile(email) {
    try {
        const response = await axios.delete(`${API_HOST}/api/users/profile/${email}`);
        return response.data;
    } catch (error) {
        console.error('API call to deleteProfile failed:', error.response ? error.response.data : error.message);
        throw error;
    }
}

export { signUp, signIn, getProfile, updateProfile, deleteProfile };
