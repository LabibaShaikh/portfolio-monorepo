import React, { useEffect, useState } from "react";

/**
 * Represents the MealPlanning component.
 * This component fetches recipes from an API and displays them based on user input.
 *
 * @returns {JSX.Element} The JSX element representing the MealPlanning component.
 */
function MealPlanning() {
    //API to fetch recipes from
    const URL = 'https://api.spoonacular.com/recipes/complexSearch?query=pasta&maxFat=25&number=2&apiKey=bad0ccf2e7d84617ac8b800d2d406844';

    //Hooks to manage the retrieval of recipes from the API
    const [meals, setMeals] = useState(null);
    const [getMeals, setGetMeals] = useState(true);

    //Use Effect to call the API
    useEffect(() => {
        fetch(URL)
        .then((response) => { 
            if(!response.ok) {
                throw new Error('Network response was not ok');
            }        
            return response.json();
        })
        .then((data) => {
            setMeals(data);
            setGetMeals(false);
        })
        .catch((error) => {
            console.log('There was a problem with the fetch operation:', error);
        });
    }, [getMeals]);


    // Button function to handle submitting requests 
    const submitRequest = () => {
        setMeals(null);
        setGetMeals(true);
    }

    return (
        <div className="PersonaliseMealsForm">
            <label htmlFor="MealInput">Enter your meal type:</label><br />
            <input type="text" id="MealInput" placeholder="Enter meal here" />
            <button type="button" onClick={submitRequest}>Find meals</button>
            {/* Conditionally render loading message, or results from API */}
            {
                (meals === null) ? 
                <p>Please wait while we fetch some meals for you...</p>
                :
                <div className="mealsReturned">
                    {meals.results.map((meal) => {
                        return (
                            <p>{meal.title}</p>
                        );
                    })}
                </div>
                }
        </div>
    );
};

export default MealPlanning;