import React, { useState, useEffect } from 'react';
import { useQuery, useMutation } from '@apollo/client';
import { GET_REVIEWS, DELETE_REVIEW } from './graphql/queries';
import Header from './Header';
import Sidebar from './Sidebar';
import './ManageCustomers.css';

const ManageReviews = () => {
  const { loading, error, data } = useQuery(GET_REVIEWS);
  const [deleteReview] = useMutation(DELETE_REVIEW, {
    refetchQueries: [{ query: GET_REVIEWS }]
  });

  const [openSidebarToggle, setOpenSidebarToggle] = useState(false);
  const [reviews, setReviews] = useState([]);

  const OpenSidebar = () => {
    setOpenSidebarToggle(!openSidebarToggle);
  };

  useEffect(() => {
    if (data) {
      setReviews(data.reviews);
    }
  }, [data]);

  if (loading) return <p>Loading...</p>;
  if (error) return <p>Error fetching reviews</p>;

  const handleDeleteReview = (id) => {
    deleteReview({ variables: { id } });
    let updatedReviews = reviews.filter(obj => obj.id !== id);
    setReviews(updatedReviews);
  };

  return (
    <div className="container">
      <Sidebar openSidebarToggle={openSidebarToggle} OpenSidebar={OpenSidebar} />
      <div className="main-content">
        <Header OpenSidebar={OpenSidebar} />
        <main className="content">
          <h1 className="title">Manage Reviews</h1>
          <div className="table-container">
            <table className="table">
              <thead className="table-header">
                <tr>
                  <th>ID</th>
                  <th>User Email</th>
                  <th>Item ID</th>
                  <th>Review Text</th>
                  <th>Rating</th>
                  <th>Actions</th>
                </tr>
              </thead>
              <tbody>
                {reviews.map((review) => (
                  <tr key={review.id}>
                    <td>{review.id}</td>
                    <td>{review.userEmail}</td>
                    <td>{review.itemId}</td>
                    <td>{review.reviewText}</td>
                    <td>{review.rating}</td>
                    <td>
                      <button className="btn btn-delete" onClick={() => handleDeleteReview(review.id)}>Delete</button>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </main>
      </div>
    </div>
  );
};

export default ManageReviews;
