import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import './App.css';
import Dashboard from './dashboard';
import ManageCustomers from './ManageCustomers';
import ApolloProvider from './ApolloProvider';
import ManageProducts from './ManageProducts';
import ManageReviews from './ManageReviews';
function App() {
  return (
    <ApolloProvider>
      <Router>
        <div className="App">
          <Routes>
            <Route path="/" element={<Dashboard />} />
            <Route path="/manage-customers" element={<ManageCustomers />} />
            <Route path="/manage-products" element={<ManageProducts />} />
            <Route path="/manage-reviews" element={<ManageReviews />} />


          </Routes>
        </div>
      </Router>
    </ApolloProvider>
  );
}

export default App;
