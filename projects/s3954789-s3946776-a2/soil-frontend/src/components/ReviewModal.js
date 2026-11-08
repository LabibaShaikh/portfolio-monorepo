import React, { useState, useEffect } from 'react';
import Rating from '@mui/material/Rating';
import StarRating from "./StarRating";
import useReview from "../components/useReview";
import validate from '../components/ReviewValidationRules';
import { getFollowedUsers, addFollowedUser, removeFollowedUser } from '../data/followFunctions';
import { getReviews, removeReview, addReview } from '../data/reviewFunctions';
import { useAuth } from './AuthContext';
import './ReviewModal.css';
 
let followedUsers;
let reviews;
 
function ReviewModal({ itemId, setIsOpen, setIsEditOpen, setReviewToEdit }) {
    const { isUserLoggedIn } = useAuth();
    const [isReviewsLoading, setIsReviewsLoading] = useState(true);
    const [isFollowersLoading, setIsFollowersLoading] = useState(true);
    const [starRating, setStarRating] = useState(5);
 
    let loggedInEmail = localStorage.getItem("loggedInEmail");
 
    useEffect(() => {
        getReviews(itemId).then(result => {
            reviews = result;
            setIsReviewsLoading(false);
            console.log(reviews);
        }).catch(error => {
            console.error("Error fetching reviews:", error);
        });
 
        if (loggedInEmail) {
            getFollowedUsers(loggedInEmail).then(result => {
                followedUsers = result;
                setIsFollowersLoading(false);
                console.log(followedUsers);
            }).catch(error => {
                console.error("Error fetching followed users:", error);
            });
        } else {
            setIsFollowersLoading(false);
        }
    }, [itemId]);
 
    const {
        values,
        errors,
        handleChange,
        handleSubmit,
    } = useReview(submitReview, validate);
 
    function handleRating(rating) {
        setStarRating(rating);
    };
 
    async function submitReview() {
        if (!isUserLoggedIn) {
            alert("Please login to submit a review.");
        } else {
            try {
                const response = await addReview({rating: starRating, reviewText: values.reviewText, itemId: itemId, userEmail: loggedInEmail});
                alert("Review Submitted!");
                setIsReviewsLoading(true);
                getReviews(itemId).then(result => {
                    reviews = result;
                    setIsReviewsLoading(false);
                }).catch(error => {
                    console.error("Error fetching reviews:", error);
                });
            } catch (error) {
                console.error("Error submitting review:", error);
            }
        }
    };
 
    async function deleteReview(reviewID) {
        try {
            const response = await removeReview(reviewID);
            setIsReviewsLoading(true);
            getReviews(itemId).then(result => {
                reviews = result;
                setIsReviewsLoading(false);
            }).catch(error => {
                console.error("Error fetching reviews:", error);
            });
        } catch (error) {
            console.error("Error deleting review:", error);
        }
    }
 
    function editReview(review) {
        setIsEditOpen(true);
        setReviewToEdit(review);
        setIsOpen(false);
    }
 
    async function followUser(email, emailToFollow) {
        try {
            await addFollowedUser({ userEmail: email, userFollowsEmail: emailToFollow });
            setIsFollowersLoading(true);
            getFollowedUsers(loggedInEmail).then(result => {
                followedUsers = result;
                setIsFollowersLoading(false);
            }).catch(error => {
                console.error("Error fetching followed users:", error);
            });
        } catch (error) {
            console.error("Error following user:", error);
        }
    }
 
    async function unfollowUser(email, emailToUnfollow) {
        try {
            await removeFollowedUser({ userEmail: email, userFollowsEmail: emailToUnfollow });
            setIsFollowersLoading(true);
            getFollowedUsers(loggedInEmail).then(result => {
                followedUsers = result;
                setIsFollowersLoading(false);
            }).catch(error => {
                console.error("Error fetching followed users:", error);
            });
        } catch (error) {
            console.error("Error unfollowing user:", error);
        }
    }
 
    return (
        <div className="ReviewModal-Wrapper">
            <div className="Review-Form">
                <form onSubmit={handleSubmit} noValidate>
                    <h1>Leave a review</h1>
                    <div className='StarRating'>
                        <StarRating handleRating={handleRating} />
                    </div>
                    <textarea className={`input ${errors.reviewText && 'is-danger'}`}
                            rows="4" type="reviewText" name="reviewText" placeholder="Your review goes here" onChange={handleChange}
                            value={values.reviewText || ''} required /><br />
                            {errors.reviewText && (
                            <p className="help-is-danger">{errors.reviewText}</p>
                            )}
                    <button className="submitReview" type="submit">Submit</button>
                </form>
            </div>
            <div className="ProdReviews">
                <h1>Reviews</h1>
                {(reviews && reviews.length > 0) ? (reviews.map((review, index) =>
                    <div className='Review' key={index}>
                    {review.isDeleted == 1 ? 
                    (<p>***This review has been deleted by the admin.***</p>) : 
                    (<div>
                        <Rating name="read-only" value={review.rating} readOnly />
                        <p>{review.reviewText}</p>
                        {(loggedInEmail === review.userEmail) ?
                            (<div className='Edit-or-delete'>
                             <button onClick={() => editReview(review)}>Edit</button>
                             <button onClick={() => deleteReview(review.id)}>Delete</button>
                             </div>) :
                             (followedUsers && followedUsers.find(obj => obj.userFollowsEmail === review.userEmail) ?
                             (<div><button onClick={() => unfollowUser(loggedInEmail, review.userEmail)}>Unfollow</button></div>) :
                             (<div><button onClick={() => followUser(loggedInEmail, review.userEmail)}>Follow</button></div>))
                        }
                    <br /></div>)}
                    </div>
                )) :
                (<div className='NoReviews'><p>Be the first to leave a review!</p></div>)}
            </div>
            <button className="Close-Button" onClick={() => setIsOpen(false)}>X</button>
        </div>
    );
}
 
export default ReviewModal;
