import { render, screen, fireEvent } from "@testing-library/react";
import axios from "axios";
import ShoppingCart from "../../pages/ShoppingCart";
import { act } from "react-dom/test-utils";
import { BrowserRouter } from "react-router-dom";
import React from "react";
import ChangeQtyBtn from "../changeQtyBtn";

//SHOPPING CART UNIT TESTS:
//Provides fake cart items and mock API functions to ShoppingCart component
//Checks whether the following function correctly:
// -> Remove item
// -> Change qty of item
// -> Display Total price of cart

//Mock axios module
jest.mock("axios");

//Global Data
const API_HOST = "http://localhost:4000";
let CartItems;
let container;
let totalPrice;

//Runs once before tests, global data is initialised
beforeAll(() => {
});

//Runs before each test, Shopping Cart is rendered and the container is stored
beforeEach(async () => {
    //Set fake data to fetch
    CartItems = [{id: 1, prodName: "Large Corn - 6 pack", price: 3, qty: 1},
                 {id: 6, prodName: "Dough Delight Co. Wholemeal Bread Loaf", price: 3.5, qty: 1},
                 {id: 12, prodName: "Roasted Chickpeas, 100g", price: 4.8, qty: 1}];

    totalPrice = CartItems[0].price + CartItems[1].price + CartItems[2].price;

    //Define mock fetch functions
    axios.get.mockImplementation((url) => { //Get cart items
        console.log(`Axios called with the url: ${url}`);
        return Promise.resolve({ data: CartItems });
    });
    axios.delete.mockImplementation((url) => { //Remove item from cart
        console.log(`Axios called with the url: ${url}`);
        CartItems.splice(0, 1);
        return Promise.resolve({ data: {message: "Item removed from cart successfully"} });
    });
    axios.put.mockImplementation((url) => {
        console.log(`Axios called with the url: ${url}`); //Change qty on item
        CartItems[0].qty = 2;
        return Promise.resolve({data: {message: "Item quantity was successfully updated."}});
    });

    //Render the component
    await act(async () => {
    render(<BrowserRouter><ShoppingCart><ChangeQtyBtn /></ShoppingCart></BrowserRouter>, container);
    });
});

//UNIT TEST 1:
//Remove item from cart
test("Remove an item from cart", async () => {

    //Retrieve remove item button ('X') on first item
    let itemsTable = document.getElementsByClassName("shoppingCartTable")[0];
    let tableItemRows = itemsTable.querySelectorAll("tr");
    expect(tableItemRows).toHaveLength(4);
    let removeItemBtn = tableItemRows[1].getElementsByTagName("img")[0];

    //Click the button
    await act(async () => {
        fireEvent.click(removeItemBtn);
    });
    
    //Check the item was removed (no. of table rows changed (4 -> 3))
    expect(axios.delete).toHaveBeenCalled();
    itemsTable = document.getElementsByClassName("shoppingCartTable")[0];
    tableItemRows = itemsTable.querySelectorAll("tr");
    expect(tableItemRows).toHaveLength(3);
});

//UNIT TEST 2:
//Change qty on item using mock API function
test("Change qty on item", async () => {
    //Get '+' button on first item 
    const increaseQtyBtn = screen.getAllByText("+")[0];

    //Click the button
    await act(async () => {
        fireEvent.click(increaseQtyBtn);
    });

    //Check the qty has increased (1 -> 2)
    let itemsTable = document.getElementsByClassName("shoppingCartTable")[0];
    let tableItemRows = itemsTable.querySelectorAll("tr");
    let qty = tableItemRows[1].getElementsByTagName("p")[0];
    expect(qty.innerHTML).toBe("2");

});

//UNIT TEST 3:
//Calculate Total price
test("Calculate total price on cart", () => {
    //Get the total price from rendered component
    let totalTable = document.getElementById("total-row");
    let totalData = totalTable.querySelectorAll("td")[1];
    let total = totalData.getElementsByTagName("p")[0];

    //Check the value is equal to the expected total
    expect(total.innerHTML).toBe(`$${totalPrice.toFixed(2)}`);
});
