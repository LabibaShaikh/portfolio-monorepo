import React from "react";
import { useNavigate } from "react-router-dom";
import { useState, useEffect } from "react";
import { useAuth } from './AuthContext';
 // Import useAuth hook
import "./Profile";
import "./SignIn";
import "./Navbar.css";
import {Link} from "react-router-dom";
import profile_icon from './profile.png';
/**
 * Renders the navigation bar component.
 * @returns {JSX.Element} The JSX element representing the navigation bar.
 */
/**
 * Renders the navigation bar component.
 * @returns {JSX.Element} The JSX element representing the navigation bar.
 */
function Navbar() {
   

      const { isUserLoggedIn } = useAuth(); // Use the hook to get auth state directly
  
      return (
        <div className="navbarWrapper">
          <nav className="navbar">
            <div className="listWrapper">
              <ul className="no_style_list">
                <li><a href="/">Home</a></li>
                <li><a href="/Sales">Specials</a></li>
                <li><a href="/Products">Products</a></li>
                <li><a href="/Meals">Plan your diet</a></li>
                <li><a href="/DIYToolkit">DIY Gardening</a></li>
              </ul>
            </div>
  
            <div>
              {isUserLoggedIn ? (
                <>
                  <Link to="/Profile">
                    <img src={profile_icon} alt="Profile" id="profile-icon" />
                  </Link>
                  <Link to="/ShoppingCart">
                    <img src="../shopping_cart_black_24dp.svg" alt="shopping-cart-btn" id="shopping-cart-btn" />
                  </Link>
                </>
              ) : (
                <>
                  <Link to="/SignIn">
                    <button id="SignIn-Btn">Sign In</button>
                  </Link>
                  <Link to="/SignUp">
                    <button id="SignUp-Btn">Sign Up</button>
                  </Link>
                  <Link to="/ShoppingCart">
                    <img src="../shopping_cart_black_24dp.svg" alt="shopping-cart-btn" id="shopping-cart-btn" />
                  </Link>
                </>
              )}
            </div>
          </nav>
        </div>
      );
  }

export default Navbar;