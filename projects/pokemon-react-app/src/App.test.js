import React from 'react';
import { render, screen } from '@testing-library/react';
import { BrowserRouter as Router } from 'react-router-dom';
import App from './App';

test('renders Pokedex link', () => {
  render(
   
      <App />
  
  );
  const linkElement = screen.getByRole('link', { name: /Pokedex/i });
  expect(linkElement).toBeInTheDocument();
});

test('renders Pokedex heading', () => {
  render(
   
      <App />
   
  );
  const headingElement = screen.getByRole('heading', { name: /Pokedex/i });
  expect(headingElement).toBeInTheDocument();
});
