// due to the navabar not being updated automatically when the state was passed to it, we had to use this.

import React, { createContext, useContext, useState, useEffect } from 'react';

const AuthContext = createContext(null);

/**
 * Provides authentication context for the application.
 * @param {Object} props - The component props.
 * @param {ReactNode} props.children - The child components.
 * @returns {ReactNode} The component with authentication context.
 */
export const AuthProvider = ({ children }) => {
  const [isUserLoggedIn, setIsUserLoggedIn] = useState(false);

  /**
   * Logs out the user by removing the necessary items from local storage and updating the state.
   */
  const logout = () => {
    localStorage.removeItem('isLoggedIn');
    localStorage.removeItem('loggedInEmail');
    setIsUserLoggedIn(false);
  };

  // Set initial state based on local storage
  useEffect(() => {
    const loggedIn = localStorage.getItem('isLoggedIn') === 'true';
    setIsUserLoggedIn(loggedIn);
  }, []);

  // Listen for changes in local storage
  useEffect(() => {
    /**
     * Handles the storage change event and updates the state accordingly.
     */
    const handleStorageChange = () => {
      const loggedInStatus = localStorage.getItem('isLoggedIn') === 'true';
      setIsUserLoggedIn(loggedInStatus);
    };

    window.addEventListener('storage', handleStorageChange);
    return () => {
      window.removeEventListener('storage', handleStorageChange);
    };
  }, []);


  
  // the return is returning the AuthContext.Provider which is a wrapper for the children components
  return (
    <AuthContext.Provider value={{ isUserLoggedIn, setIsUserLoggedIn, logout }}> 
    
      {children}
    </AuthContext.Provider>
  );
};

export const useAuth = () => useContext(AuthContext);




