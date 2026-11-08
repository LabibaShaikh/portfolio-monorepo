import React from "react";
import { useState, useEffect } from "react";
import { getCartItems } from "../data/repository";

function TotalPrice({ flagUpdate }) {

    //Function to calculate total price
    let total = 0; 
    function calcTotalPrice(items) {
        for (let i = 0; i < items.length; i++) {
            total += items[i].qty * items[i].price;
        }
        return total;
    }

    //Hook to control price state 
    const [totalPrice, setTotalPrice] = useState(0);

    useEffect(() => { 
        getCartItems().then(items => {
            const total = calcTotalPrice(items);
            setTotalPrice(total);
        })
    }, [flagUpdate]);

    return (
        <p>${totalPrice.toFixed(2)}</p>
    );
};

export default TotalPrice;