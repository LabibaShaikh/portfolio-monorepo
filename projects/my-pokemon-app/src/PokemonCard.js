import React, { useState, useEffect } from 'react';

function PokemonCard({ url }) {
    const [pokemonDetails, setPokemonDetails] = useState(null);
    const [loading, setLoading] = useState(true);  // Add a loading state

    useEffect(() => {
        const fetchPokemonDetails = async () => {
            setLoading(true);  // Set loading to true when fetch starts
            try {
                const response = await fetch(url);
                const data = await response.json();
                setPokemonDetails(data);
            } catch (error) {
                console.error("Error fetching details:", error);
            } finally {
                setLoading(false);  // Set loading to false when fetch completes
            }
        };

        fetchPokemonDetails();
    }, [url]);  // Removed isOpen dependency

    if (loading) {
        return <div className="card">Loading...</div>;
    }

    return (
        <div className="card">
            <div className="card-body">
                {pokemonDetails ? (
                    <div>
                        <h5 className="card-title">{pokemonDetails.name}</h5>
                        <img src={pokemonDetails.sprites?.front_default} alt={pokemonDetails.name} />
                        <p>Height: {pokemonDetails.height}</p>
                        <p>Weight: {pokemonDetails.weight}</p>
                        {/* Add more details as needed */}
                    </div>
                ) : (
                    <p>Details not available</p>
                )}
            </div>
        </div>
    );
}

export default PokemonCard;
