import React from "react";
import { useNavigate } from "react-router-dom";
import { useEffect, useState } from "react";
import useCheckout from "../components/useCheckout";
import validate from '../components/CheckoutValidationRules';
import { useAuth } from '../components/AuthContext';
import { getCartItems, removeCartItem } from "../data/repository";
import "./Checkout.css";

/**
 * Renders the Checkout component.
 * 
 * @returns {JSX.Element} The rendered Checkout component.
 */
const Checkout = () => {

    const { isUserLoggedIn } = useAuth(); // Use the useAuth hook to get the login status
    
    //Store values, errors and updates to the form
    const {
        values,
        errors,
        handleChange,
        handleSubmit,
      } = useCheckout(submitPayment, validate);

    //Hook to navigate to Payment Confirmation page
    const navigate = useNavigate();

    //Upon successful submission, redirects to Payment Confirmation page
    function submitPayment() {
        if (!isUserLoggedIn) {
            alert("Please sign in to complete your purchase.");
        }
        else {
            navigate("/Checkout/PaymentConfirm");
        }
    };

    //Calculate total price for order summary
    const [items, setItems] = useState([]);
    let total = 0;

    //Get purchased items from DB
    useEffect(() => {
        getCartItems().then(result => {
            setItems(result);
            for (let i = 0; i < result.length; i++) {
                total += result[i].price * result[i].qty;
            };
        });
    }, []);

    return (
        <div className="CheckoutWrapper">
            <div className="checkoutFormWrapper">
                    <form onSubmit={handleSubmit} noValidate> 
                    <div className="checkoutContainer">           
                        <h1>Checkout</h1>
                        <h2>Shipping Details</h2>
                        {/* Fields that require validation have className '...is-danger' */}
                        <input className={`input ${errors.email && 'is-danger'}`} 
                            type="email" name="email" placeholder="Email" onChange={handleChange} 
                            value={values.email || ''} required /><br />
                                {errors.email && (
                                    <p className="help is-danger">{errors.email}</p>
                                )}         
                        <input type="text" id="fname" name="fname" placeholder="First Name" required /><br />
                        <input type="text" id="lname" name="lname" placeholder="Last Name" required /><br />
                        <input type="text" id="address" name="address" placeholder="Address" required /><br />
                        <input type="text" id="suburb" name="suburb" placeholder="Suburb" required /><br />
                        <input className={`input ${errors.postcode && 'is-danger'}`}
                            type="text" id="postcode" name="postcode" placeholder="Postcode" onChange={handleChange}
                            value={values.postcode || ''} required /><br />
                        <input type="text" id="phone" name="phone" placeholder="Phone" required /><br />
                        </div>
                    <div className="paymentContainer">
                        <h2>Payment</h2>
                        <input className={`input ${errors.cardNumber && 'is-danger'}`} 
                            type="cardNumber" name="cardNumber" placeholder="Card number" onChange={handleChange} 
                            value={values.cardNumber || ''} required /><br />
                            {errors.cardNumber && (
                            <p className="help is-danger">{errors.cardNumber}</p>
                            )}
                        <input className={`input ${errors.nameoncard && 'is-danger'}`} 
                            type="nameoncard" name="nameoncard" placeholder="Name on card" onChange={handleChange} 
                            value={values.nameoncard || ''} required /><br />
                            {errors.nameoncard && (
                            <p className="help is-danger">{errors.nameoncard}</p>
                            )}
                        <input className={`input ${errors.expiry && 'is-danger'}`} 
                            type="expiry" name="expiry" placeholder="Expiration date (MM/YY)" onChange={handleChange}
                            value={values.expiry || ''} required /><br />
                            {errors.expiry && (
                            <p className="help is-danger">{errors.expiry}</p>
                            )}
                        <input className={`input ${errors.cvc && 'is-danger'}`} 
                            type="cvc" name="cvc" placeholder="CVC" onChange={handleChange} 
                            value={values.cvc || ''} required /><br />
                            {errors.cvc && (
                            <p className="help is-danger">{errors.cvc}</p>
                            )}
                        <button type="submit" className="continueToPayment">Pay Now</button>
                    </div>
                    
                </form>    
            </div>
            {/* Order Summary Table */}
            <div className="Order-Purchase-Summary">
                <table>
                    <th colSpan={2}>ORDER SUMMARY</th>
                    {items.map(item => (
                        <tr id="item-listing">
                            <td>{item.prodName} x {item.qty}</td>
                            <td class="rightAlign">${(item.price * item.qty).toFixed(2)}</td>
                        </tr>
                    ))}
                    <tr id="total-row">
                        <td>TOTAL</td>
                        <td class="rightAlign">${(total).toFixed(2)}</td>
                    </tr>
                </table>
            </div>
        </div>

    );

};

export default Checkout;