import React from "react";
import { Link } from "react-router-dom";
import "../components/PlanYourDiet.css";

/**
 * Renders the component for planning a nutritious diet.
 * @returns {JSX.Element} The rendered component.
 */
function PlanYourDiet() {

    return (
        //Image wrapper
        <div className="PlanYourDietWrapper">
            <div className="MealPlan-Image">
                <img src="PlanYourDietImg.jpg" alt="PlanYourDietImg.jpg" height="1000px" width="100%"></img>
            </div>
            {/* Text Wrapper */}
            <div className="textWrapper">
                <div className="HeaderWrapper">
                    <h1>Plan your nutritious diet!</h1>
                    <p>Select from our assortment of dietician-approved recipes and meal-plans to meet your health goals!</p>
                    <Link to="/Meals">
                        <button className="Plan-Btn">START PLANNING</button>
                    </Link>
                </div>
            </div>
        </div>
    );
}

export default PlanYourDiet;