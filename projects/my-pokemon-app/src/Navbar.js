import React from 'react';
import './Navbar.css';
import pikachu from './pikaa.jpg';  // Confirm the path is correct

function Navbar() {
    return (
        <header>
            <img src={pikachu} alt="Pikachu" />
            <nav>
                <ul>
                    <li><a href="/">Pokedex</a></li>
                    <li><a href="/PokemonList">List Pokemon</a></li>
                    <li><a href="#">Compare Pokemon</a></li>
                </ul>
            </nav>
        </header>
    );
}

export default Navbar;
