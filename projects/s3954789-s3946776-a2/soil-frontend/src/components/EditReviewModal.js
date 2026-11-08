import React from 'react';
import Rating from '@mui/material/Rating';
import StarRating from "./StarRating";
import useReview from "../components/useReview";
import validate from '../components/ReviewValidationRules';
import { useState, useEffect } from 'react';
import { updateReview } from "../data/reviewFunctions";
import './EditReviewModal.css';

function EditReviewModal({ reviewToEdit, setIsEditOpen }) {

    const [starRating, setStarRating] = useState(5);

    //Store values, errors and updates to the form
    const {
        values,
        errors,
        handleChange,
        handleSubmit,
        } = useReview(submitReview, validate);

    //This function handles rating changes
    function handleRating(rating) {
        setStarRating(rating);
        };

    async function submitReview() {
        const updatedReview = {id: reviewToEdit.id, rating: starRating, reviewText: values.reviewText, itemId: reviewToEdit.itemId, userEmail: reviewToEdit.userEmail};
        const response = await updateReview(updatedReview);
        alert("Your review has been updated!");
        setIsEditOpen(false);
    };

    return (
        <div className="Edit-Review">
            <h1>Edit your review</h1>
            <div className="Edit-Review-Form">
                <form onSubmit={handleSubmit} noValidate>
                    <div className='Edit-StarRating'>
                        <StarRating handleRating={handleRating} />
                    </div>
                    <textarea className={`input ${errors.reviewText && 'is-danger'}`} 
                            rows="4" type="reviewText" name="reviewText" placeholder="Your review goes here" onChange={handleChange} 
                            value={values.reviewText || reviewToEdit.reviewText} required /><br />
                            {errors.reviewText && (
                            <p className="help-is-danger">{errors.reviewText}</p>
                            )}
                    <button className="saveBtn" type="submit">Save</button>
                </form>
            </div>
            <button className="Close-Button" onClick={() => setIsEditOpen(false)}>X</button>
        </div>
    );
};

export default EditReviewModal;