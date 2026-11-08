import React from "react";
import "./Header.css";
import { Link } from "react-router-dom";

/* Header Component includes:
   - Logo
   - Shopping Cart
*/

/**
 * Renders the header component.
 * @returns {JSX.Element} The header component.
 */
function Header() {
    return (
        <div className="HeaderWrapper">
            <header className="Header">
                <div className="Header-Logo">SOIL</div>
            </header>
        </div>

    );
}


export default Header;