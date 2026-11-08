import { useState } from "react";
import "./Sales.css";
import { getItems, addCartItem, findCartItem } from "../data/repository";
import ReviewModal from "../components/ReviewModal";
import EditReviewModal from "../components/EditReviewModal";

//This component includes a list of sale items
const ITEMS_KEY = "items";

const saleItems = await getItems(1);

/**
 * Renders the Sales component.
 * This component displays a list of sale items with their descriptions and prices.
 * Users can add items to their cart by clicking on the "Add to cart" button.
 * @returns {JSX.Element} The rendered Sales component.
 */
function Sales() {

    const [isOpen, setIsOpen] = useState(false);
    const [isEditOpen, setIsEditOpen] = useState(false);
    const [reviewToEdit, setReviewToEdit] = useState({});
    const [itemId, setItemId] = useState(null);



    //Function to add item to cart
    async function addItemToCart(item) {
        //Check if item already exists in db
        //If it does, don't add anything
        const response = await findCartItem(item.id);
        if (response !== null) {
            alert("This item has already been added to cart.");
        }
        else {
            delete item.imgPath;
            await addCartItem(item);
            alert("Item has been added to cart!");
        }
    };

    function openReview(id) {
        setIsOpen(true);
        setItemId(id);
    }

    return (
        <div class="Sales-Container">
            <div class="Sales">
                <div class="Heading">
                    <h1>This week's specials</h1>
                </div>
                {saleItems.map((item, index) => (
                <div class="Sale-Item">
                    <img src={`${item.imgPath}`} alt="Standard-Product" onClick={() => addItemToCart(item)}></img>
                    <div class="desc">{item.prodName}<br/><br/>${item.price.toFixed(2)}</div>
                    <button class="Add-to-cart-btn"
                            onClick={() => addItemToCart(item)}>Add to cart</button>
                    <button class="Write-a-review" onClick={() => openReview(item.id)}>Write a review</button>
                </div>
            ))}
            {isOpen ? <ReviewModal itemId={itemId} setIsOpen={setIsOpen} setIsEditOpen={setIsEditOpen} setReviewToEdit={setReviewToEdit}/> : <></>}
            {isEditOpen ? <EditReviewModal reviewToEdit={reviewToEdit} setIsEditOpen={setIsEditOpen}></EditReviewModal> : <></>}
            </div>
        </div>
    );
}

export default Sales;