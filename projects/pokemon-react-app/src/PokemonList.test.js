import React from 'react';
import { render, screen, waitFor, act } from '@testing-library/react';
import '@testing-library/jest-dom';
import PokemonList from './PokemonList';
import fetchMock from 'jest-fetch-mock';

// Enable fetch mocks
fetchMock.enableMocks();

describe('PokemonList Component', () => {
  beforeEach(() => {
    fetchMock.resetMocks();
  });

  test('renders loading state initially', () => {
    render(<PokemonList />);
    expect(screen.getByText('Loading Pokemons...')).toBeInTheDocument();
  });

  test('renders list of pokemons after fetch', async () => {
    const mockResponse = {
      count: 2,
      results: [
        { name: 'pikachu', url: 'https://pokeapi.co/api/v2/pokemon/25/' },
        { name: 'bulbasaur', url: 'https://pokeapi.co/api/v2/pokemon/1/' }
      ]
    };

    fetchMock.mockResponseOnce(JSON.stringify(mockResponse));

    await act(async () => {
      render(<PokemonList />);
    });

    await waitFor(() => {
      expect(screen.getByText('pikachu')).toBeInTheDocument();
      expect(screen.getByText('bulbasaur')).toBeInTheDocument();
    });
  });

  test('handles fetch error', async () => {
    fetchMock.mockRejectOnce(new Error('API failure'));

    await act(async () => {
      render(<PokemonList />);
    });

    await waitFor(() => {
      expect(screen.getByText(/Failed to load Pokemons/i)).toBeInTheDocument();
    });
  });

  test('pagination works correctly', async () => {
    const mockResponsePage1 = {
      count: 3,
      results: [
        { name: 'Pikachu', url: 'https://pokeapi.co/api/v2/pokemon/25/' },
        { name: 'Bulbasaur', url: 'https://pokeapi.co/api/v2/pokemon/1/' }
      ]
    };

    const mockResponsePage2 = {
      count: 3,
      results: [
        { name: 'Charmander', url: 'https://pokeapi.co/api/v2/pokemon/4/' }
      ]
    };

    fetchMock.mockResponses(
      [JSON.stringify(mockResponsePage1)],
      [JSON.stringify(mockResponsePage2)]
    );

    await act(async () => {
      render(<PokemonList />);
    });

    await waitFor(() => {
      expect(screen.getByText('Pikachu')).toBeInTheDocument();
      expect(screen.getByText('Bulbasaur')).toBeInTheDocument();
    });

    const nextButton = screen.getByText('Next');
    await act(async () => {
      nextButton.click();
    });

    await waitFor(() => {
      expect(screen.getByText('Charmander')).toBeInTheDocument();
    });
  });
});
