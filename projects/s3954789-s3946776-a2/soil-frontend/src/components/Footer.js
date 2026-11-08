import React from "react";
import "./Footer.css";
import { useLocation } from "react-router-dom";

/**
 * Renders the Footer component.
 * @returns {JSX.Element} The rendered Footer component.
 */
function Footer() {
    const location = useLocation();

    let positionFooterStyle = {};

    {location.pathname === "/" ?
    (positionFooterStyle = {bottom : "-1200px"}) : (positionFooterStyle = {bottom : "0px"})}

    return (
        <div className="Footer-container" style={positionFooterStyle}>
            <p>©Soil 2024</p>
            <img src="../X_Icon.png" alt="X_Icon.png" width="35px" height="35px" id="X"/>
            <img src="../Instagram.jpg" alt="Instagram.jpg" width="35px" height="35px" id="Instagram" />
        </div>
    );
}

export default Footer;