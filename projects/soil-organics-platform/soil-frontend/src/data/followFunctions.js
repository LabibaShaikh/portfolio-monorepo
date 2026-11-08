import axios from "axios";

//CONSTANTS
const API_HOST = "http://localhost:4000";

//follow a user
async function addFollowedUser(followerData) {
    const response = await axios.post(API_HOST + "/api/followers", followerData);

    return response.data;
}

//unfollow a user
async function removeFollowedUser(follower) {
    const followerData = { params: {userEmail: follower.userEmail, userFollowsEmail: follower.userFollowsEmail}};
    console.log(followerData);
    const response = await axios.delete(API_HOST + "/api/followers", followerData);

    return response.data;
}

//get followed users 
async function getFollowedUsers(email) {
    const response = await axios.get(API_HOST + "/api/followers", { params: {userEmail: email} });

    return response.data;
}

export { addFollowedUser, removeFollowedUser, getFollowedUsers }