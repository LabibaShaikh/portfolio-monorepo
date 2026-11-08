import React, { useState, useEffect } from 'react';
import './Home.css';
import { BsFillArchiveFill, BsFillGrid3X3GapFill, BsPeopleFill } from 'react-icons/bs';
import { BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer, LineChart, Line } from 'recharts';

function Home() {
  // Bar chart data
  const data = [
    { name: 'Page A', uv: 4000, pv: 2400, amt: 2400 },
    { name: 'Page B', uv: 3000, pv: 1398, amt: 2210 },
    { name: 'Page C', uv: 2000, pv: 9800, amt: 2290 },
    { name: 'Page D', uv: 2780, pv: 3908, amt: 2000 },
    { name: 'Page E', uv: 1890, pv: 4800, amt: 2181 },
    { name: 'Page F', uv: 2390, pv: 3800, amt: 2500 },
    { name: 'Page G', uv: 3490, pv: 4300, amt: 2100 },
  ];

  // Example reviews data
  const [reviews, setReviews] = useState([
    { id: 1, text: 'Great product!', user: 'User1' },
    { id: 2, text: 'Very satisfied with the purchase.', user: 'User2' },
    { id: 3, text: 'Good value for money.', user: 'User3' },
  ]);

  // Fetch reviews from an API
  useEffect(() => {
    // Mock fetching reviews
    const fetchReviews = async () => {
      // Replace with your API call
      const reviewsFromAPI = [
        { id: 1, text: 'Great product!', user: 'User1' },
        { id: 2, text: 'Very satisfied with the purchase.', user: 'User2' },
        { id: 3, text: 'Good value for money.', user: 'User3' },
      ];
      setReviews(reviewsFromAPI);
    };
    fetchReviews();
  }, []);

  return (
    <main className='main-container'>
      <div className='main-title'>
        <h3>ANALYTICS</h3>
      </div>

      <div className='main-cards'>
        <div className='card'>
          <div className='card-inner'>
            <h3>BEST SELLING PRODUCTS</h3>
            <BsFillArchiveFill className='card_icon' />
          </div>
          <h1>300</h1>
        </div>
        <div className='card'>
          <div className='card-inner'>
            <h3>HIGHEST RATED</h3>
            <BsFillGrid3X3GapFill className='card_icon' />
          </div>
          <h1>12</h1>
        </div>
        <div className='card'>
          <div className='card-inner'>
            <h3>RECENT REVIEWS</h3>
            <BsPeopleFill className='card_icon' />
          </div>
          <h1>33</h1>
        </div>
      </div>

      <div className='charts'>
        <ResponsiveContainer width="100%" height="100%">
          <BarChart data={data}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="name" />
            <YAxis />
            <Tooltip />
            <Legend />
            <Bar dataKey="pv" fill="#8884d8" />
            <Bar dataKey="uv" fill="#82ca9d" />
          </BarChart>
        </ResponsiveContainer>

        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={data}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="name" />
            <YAxis />
            <Tooltip />
            <Legend />
            <Line type="monotone" dataKey="pv" stroke="#8884d8" activeDot={{ r: 8 }} />
            <Line type="monotone" dataKey="uv" stroke="#82ca9d" />
          </LineChart>
        </ResponsiveContainer>
      </div>

      <div className='reviews'>
        <h3>Recent Reviews</h3>
        {reviews.map((review) => (
          <div key={review.id} className='review-card'>
            <p><strong>{review.user}:</strong> {review.text}</p>
          </div>
        ))}
      </div>
    </main>
  );
}

export default Home;
