import React, { useState } from "react";
import { useNavigate } from 'react-router-dom';
import { useAuth } from '../components/AuthContext';
import './Meals.css'; 

/**
 * Renders the Meals component.
 * This component allows users to search for recipes based on diet, excluded ingredients, and maximum calories.
 * It fetches recipes from the Spoonacular API and displays them in a grid.
 * @returns {JSX.Element} The rendered Meals component.
 */


// Function to handle the input changes
function Meals() {
    const [recipes, setRecipes] = useState([]);
    const [searchParams, setSearchParams] = useState({
        diet: '',
        excludeIngredients: '',
        maxCalories: ''
    });
    const navigate = useNavigate();
    const { isUserLoggedIn } = useAuth(); // Use the useAuth hook to get the login status

    // Function to handle input changes
    const handleInputChange = (e) => {
        setSearchParams({
            ...searchParams,
            [e.target.name]: e.target.value
        });
    };

    // Function to fetch recipes
    const fetchRecipes = () => {
        if (!isUserLoggedIn) {
            // Redirect to sign-in page if not logged in
            navigate('/SignIn');
            alert('Please sign in to search recipes.');
            return;
        }


          // Construct the API URL
        console.log("API Key:", process.env.REACT_APP_SPOONACULAR_API_KEY);
        
        const apiUrl = `https://api.spoonacular.com/recipes/complexSearch?apiKey=${process.env.REACT_APP_SPOONACULAR_API_KEY}&diet=${searchParams.diet}&excludeIngredients=${searchParams.excludeIngredients}&maxCalories=${searchParams.maxCalories}`;
        console.log("API URL:", apiUrl);  // Check the constructed URL in the console
        // Fetch recipes from the API
        fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                console.log("Fetched data:", data);  // Log fetched data to see what is returned
                if (data.results) {
                    setRecipes(data.results);
                } else {
                    setRecipes([]);
                    alert('No recipes found!');
                }
            })
            .catch(error => {
                console.error('Error:', error);
            });
    };
     // Render the Meals component
    return (
        <div className='meals-container'>
            <div className='search-container'>
                <input type="text" name="diet" placeholder="Diet (e.g., vegetarian)" onChange={handleInputChange} />
                <input type="text" name="excludeIngredients" placeholder="Exclude Ingredients" onChange={handleInputChange} />
                <input type="number" name="maxCalories" placeholder="Max Calories" onChange={handleInputChange} />
                <button onClick={fetchRecipes}>Search Recipes</button>
            </div>
            <div className="recipes-grid">
                {recipes.map((recipe, index) => (
                    <div key={index} className="recipe-card">
                        <a href={`https://spoonacular.com/recipes/${recipe.title}-${recipe.id}`}
                           target="_blank"
                           rel="noopener noreferrer"
                           className="recipe-link">
                            <div className="recipe-image-container">
                                <img src={recipe.image} alt={recipe.title} className="recipe-image" />
                            </div>
                            <p className="recipe-title">{recipe.title}</p>
                        </a>
                    </div>
                ))}
            </div>
        </div>
    );
}

export default Meals;
