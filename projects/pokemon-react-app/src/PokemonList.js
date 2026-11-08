import React, { useEffect, useState } from "react";
import PokemonCard from "./PokemonCard";
import Navbar from "./Navbar";
import "./PokemonList.css";

/**
 * Renders a list of Pokemons with pagination.
 *
 * @returns {JSX.Element} The PokemonList component.
 */
function PokemonList() {
    const [pokemons, setPokemons] = useState([]);
    const [loading, setLoading] = useState(true);
    const [currentPage, setCurrentPage] = useState(1);
    const [totalPages, setTotalPages] = useState(0);
    const limit = 40; // Adjust if you want to change the page size
  
    useEffect(() => {
      const offset = (currentPage - 1) * limit;
      const url = `https://pokeapi.co/api/v2/pokemon?limit=${limit}&offset=${offset}`;
  
      const fetchPokemons = async () => {
        setLoading(true);
        try {
          const response = await fetch(url);
          const data = await response.json();
          setPokemons(data.results);
          setTotalPages(Math.ceil(data.count / limit));
        } catch (error) {
          console.error("Failed to load Pokemons:", error);
        } finally {
          setLoading(false);
        }
      };
  
      fetchPokemons();
    }, [currentPage]);
  
    const pages = getPageNumbers(currentPage, totalPages);
  
    if (loading)
      return (
        <div className="container text-center">
          <p>Loading Pokemons...</p>
        </div>
      );
  
    return (
      <>
        <div>
          <Navbar />
        </div>
        <div className="container mt-4">
          <div className="row">
            {pokemons.map((pokemon) => (
              <div
                key={pokemon.name}
                className="col-sm-12 col-md-6 col-lg-4 mb-4"
              >
                <PokemonCard url={pokemon.url} />
              </div>
            ))}
          </div>
          <div className="pagination">
            <button
              onClick={() => setCurrentPage((prev) => Math.max(prev - 1, 1))}
              disabled={currentPage === 1}
            >
              Previous
            </button>
            {pages.map((page) => (
              <button
                key={page}
                className={page === currentPage ? "active" : ""}
                onClick={() => setCurrentPage(page)}
              >
                {page}
              </button>
            ))}
            <button
              onClick={() =>
                setCurrentPage((prev) => Math.min(prev + 1, totalPages))
              }
              disabled={currentPage === totalPages}
            >
              Next
            </button>
          </div>
        </div>
      </>
    );
  }
  
  export default PokemonList;
  



function getPageNumbers(currentPage, totalPages) {
    const pageNeighbours = 2; // How many adjacent pages should be shown on each side
    const totalNumbers = pageNeighbours * 2 + 3; // Total page numbers to show at a time
    const totalBlocks = totalNumbers + 2; // Including next and previous buttons

    if (totalPages > totalBlocks) {
        const startPage = Math.max(2, currentPage - pageNeighbours);
        const endPage = Math.min(totalPages - 1, currentPage + pageNeighbours);
        let pages = [1];

        for (let page = startPage; page <= endPage; page++) {
            pages.push(page);
        }

        pages.push(totalPages);

        return pages;
    }

    return Array.from({ length: totalPages }, (_, index) => index + 1);
}
