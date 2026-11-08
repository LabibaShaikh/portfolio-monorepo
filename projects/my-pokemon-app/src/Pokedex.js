import React, { useState } from 'react';
import Navbar from './Navbar';
import './Pokedex.css';

function Pokedex() {
    const [name, setName] = useState('');
    const [type, setType] = useState('');
    const [submitStatus, setSubmitStatus] = useState('');

    const handleSubmit = (e) => {
        e.preventDefault();
        if (!name.trim() || !type.trim()) {
            setSubmitStatus('Please fill in all fields.');
            return;
        }
        const pokemon = { name, type };
        console.log('Submitted:', pokemon); // Log the submission for debugging

        fetch('/api/pokemon', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(pokemon)
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            console.log('API response:', data);
            setSubmitStatus('Submission successful!');
            setName(''); // Clear fields only on successful submission
            setType('');
        })
        .catch(error => {
            console.error('API error:', error);
            setSubmitStatus('Submission failed. Please try again.');
        });
    };
    
    return (
        <div>
            <Navbar />
            <h1>Pokedex</h1>
            <form onSubmit={handleSubmit}>
                <label htmlFor="pokemonName">
                    Pokemon Name:
                    <input
                        id="pokemonName"
                        type="text"
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                    />
                </label>
                <label htmlFor="pokemonType">
                    Pokemon Type:
                    <input
                        id="pokemonType"
                        type="text"
                        value={type}
                        onChange={(e) => setType(e.target.value)}
                    />
                </label>
                <button type="submit">Submit</button>
                {submitStatus && <p>{submitStatus}</p>}
            </form>
        </div>
    );
}

export default Pokedex;
