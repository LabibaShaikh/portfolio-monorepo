import React, { useState, useEffect } from "react";

import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

import Header from "./components/Header";
import "bootstrap";
import Navbar from "./components/Navbar";
import SignIn from "./components/SignIn";
import SignUp from "./components/SignUp";
import Sales from "./pages/Sales";
import Products from "./pages/Products";
import ShoppingCart from "./pages/ShoppingCart";
import DIYToolkit from "./pages/DIYToolkit";
import Meals from "./pages/Meals";
import Footer from "./components/Footer";
import Home from "./pages/home";
import Checkout from "./pages/Checkout";
import Profile from "./components/Profile";
import PaymentConfirm from "./pages/PaymentConfirm";
import "./App.css";
import { AuthProvider } from "./components/AuthContext";

/**
 * The main component of the application.
 * Renders the header, navbar, routes, and footer.
 *
 * @returns {JSX.Element} The rendered App component.
 */
function App() {
  return (
    <AuthProvider>
      <Router>
        <div className="App">
          <Header />
          <Navbar />
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/Sales" element={<Sales />} />
            <Route path="/Products" element={<Products />} />
            <Route path="/Meals" element={<Meals />} />
            <Route path="/DIYToolkit" element={<DIYToolkit />} />
            <Route path="/SignIn" element={<SignIn />} />
            <Route path="/SignUp" element={<SignUp />} />
            <Route path="/Profile" element={<Profile />} />
            <Route path="/ShoppingCart" element={<ShoppingCart />} />
            <Route path="/Checkout" element={<Checkout />} />
            <Route
              path="/Checkout/PaymentConfirm"
              element={<PaymentConfirm />}
            />
          </Routes>
          <Footer />
        </div>
      </Router>
    </AuthProvider>
  );
}

export default App;
