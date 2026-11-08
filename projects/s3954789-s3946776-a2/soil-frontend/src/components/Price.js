import React, { useState, useEffect } from "react";
import { findCartItem } from "../data/repository";

//Function to calculate price of each product 
//boolean flagUpdate from parent triggers a re-render of this component
const Price = ({ cartItem, itemPrice, flagUpdate }) => {

    //Hook to control price state 
    const [price, setPrice] = useState(cartItem.price);

    //Re-renders JSX containing price each time 
    //price value changes
    useEffect(() => { 
        findCartItem(cartItem.id).then(result => {
            const newPrice = result.qty * result.price;
            setPrice(newPrice);
        });
    }, [flagUpdate]);

    return (
        <p>${price.toFixed(2)}</p>
    );
};

export default Price;