import React from "react";
import { Link } from "react-router-dom";
import "../components/DIYVeggies.css";

/**
 * Renders the DIYVeggies component.
 * 
 * @returns {JSX.Element} The rendered DIYVeggies component.
 */
function DIYVeggies() {
        //STYLING
        //Image Container
        const DIYVeggiesStyle = {
            position: "relative",
            width: "100%",
            height: "500px",
            float: "right",
            backgroundColor: "blue"
        };

        const textStyle = {
            position: "absolute",
            display: "flex",
            flexDirection: "column",
            justifyContent: "center",
            alignItems: "center",
            top: "0px",
            right: "0px",
            height: "500px",
            width: "900px",
            backgroundColor: "#FFF9C7"
        };

    return (
        //Image wrapper
        <div className="DIYVeggies">
            <img src="/GardenToolkit.png" alt="GardenToolkit.png" width="1020px" height="500px"/>
            {/* Text Wrapper */}
            <div className="text">
                <h1>Grow your own veggies with our beginner friendly toolkit for gardening!</h1>
                <Link to="/DIYToolkit">
                    <button class="Learn-More-Btn">Learn More</button>
                </Link>
                
            </div>
        </div>
    );
}

export default DIYVeggies;