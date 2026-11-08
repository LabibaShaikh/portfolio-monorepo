import React, { useState } from 'react';

function PokemonSearch() {
    const [searchTerm, setSearchTerm] = useState('');

    const handleInputChange = (event) => {
        setSearchTerm(event.target.value);
    };

    const handleSubmit = (event) => {
        event.preventDefault();
        // Add your logic here to handle form submission
    };

    return (
        <div>
            <form onSubmit={handleSubmit}>
                <input
                    type="text"
                    value={searchTerm}
                    onChange={handleInputChange}
                    placeholder="Enter a Pokemon name"
                />
                <button type="submit">Search</button>
            </form>
        </div>
    );
}

export default PokemonSearch;