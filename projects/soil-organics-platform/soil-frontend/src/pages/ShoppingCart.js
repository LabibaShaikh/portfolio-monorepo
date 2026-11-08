import React from "react";
import { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import ChangeQtyBtn from "../components/changeQtyBtn";
import Price from "../components/Price"
import TotalPrice from "../components/TotalPrice";
import "./ShoppingCart.css";
import { getCartItems, removeCartItem } from "../data/repository";

const ITEMS_KEY = "items";

/**
 * Renders the shopping cart page.
 * @returns {JSX.Element} The shopping cart component.
 */
//This page displays items user has added to their cart
function ShoppingCart() {
    
    let total = 0;
    
        //Hook to fetch cart from DB when component mounts
        const [CartItems, setCartItems] = useState([]);

        useEffect(() => {
            getCartItems().then(items => {
                setCartItems(items);
            });
        }, []);

        //Function to add item to cart
        async function removeItemFromCart(item) {
            //Delete item from DB
            await removeCartItem(item.id);
            const updatedItems = await getCartItems();
            setCartItems(updatedItems);
            setFlagForPriceUpdate(prevState => !prevState);
        };

        //Hook to set a trigger for updating prices
        const [flagForPriceUpdate, setFlagForPriceUpdate]  = useState(false);

        //Callback to update price when qty is changed
        function handleQtyChange() {
            setFlagForPriceUpdate(prevState => !prevState);
        };

    return (
        <div className="cartWrapper">
            <div className="Your-Cart-Header">
                <h1>YOUR CART</h1>
            </div>
            <div className="shoppingCartTable">
                <table>
                    <tr>
                        <th>Product</th>
                        <th>Price</th>
                        <th>Quantity</th>
                        <th>Total</th>
                    </tr>
                    {/*Display all cart items as rows here*/}
                    {( CartItems && CartItems.length > 0) ? (CartItems.map((item, index) => (
                        <tr id = {`Item-${item.prodName}`}>
                            <td id="prodName">{item.prodName}</td>
                            <td>${item.price.toFixed(2)}</td>
                            <td id="changeQtyBtn">
                                <ChangeQtyBtn cartItem = {item} onQtyChange={handleQtyChange} />
                            </td>
                            <td id="priceData">
                                <div className="price-and-clear">
                                        <Price cartItem={item} flagUpdate={flagForPriceUpdate} />
                                        <img 
                                        src="../clear_black_24dp.svg" 
                                        alt="remove-item-btn"
                                        id="remove-item-btn"
                                        onClick={() => removeItemFromCart(item)}>
                                        </img>
                                </div>
                            </td>
                        </tr>
                    ))
                ) :  (
                    // Empty cart message
                    <tr>
                        <td>Your cart is empty</td>
                    </tr>)}
                </table>
            </div>
            {/* Order Summary table */}
            <div className="Order-Summary">
                <table>
                    <th colSpan={2}>ORDER SUMMARY</th>
                    <tr id="subtotal-row">
                        <td>Subtotal</td>
                        <td class="rightAlign"><TotalPrice flagUpdate={flagForPriceUpdate}/></td>
                    </tr>
                    <tr id="total-row">
                        <td>TOTAL</td>
                        <td class="rightAlign"><TotalPrice flagUpdate={flagForPriceUpdate}/></td>
                    </tr>
                </table>           
                { CartItems.length > 0 ? 
                (<Link to="/Checkout">
                    <div className="checkout-Btn-Wrapper">
                        <button class="checkout-Btn">PROCEED TO CHECKOUT</button>
                    </div> 
                </Link>) : (
                    null
                )
                } 
                <Link to="/Sales">
                    <div className="continue-Shopping-Btn-Wrapper">
                        <button class="continue-Shopping-Btn">Continue Shopping</button>
                    </div>
                </Link>
            </div>
        </div>
    );
}

export default ShoppingCart;