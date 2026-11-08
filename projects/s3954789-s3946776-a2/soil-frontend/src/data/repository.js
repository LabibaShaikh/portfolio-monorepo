import axios from "axios";

//CONSTANTS
const API_HOST = "http://localhost:4000";

//Cart Items
async function addCartItem(item) {
    const response = await axios.post(API_HOST + "/api/cartItems", item);

    return response.data;
  }

async function findCartItem(id) {
  const response = await axios.get(API_HOST + `/api/cartItems/select/${id}`);

  return response.data;
}

async function getCartItems() {
  const response = await axios.get(API_HOST + "/api/cartItems");

  return response.data;
}

async function removeCartItem(id) {
  const response = await axios.delete(API_HOST + `/api/cartItems/remove/${id}`);
  return response.data;
}

async function updateCartItem(item) {
  const response = await axios.put(API_HOST + "/api/cartItems", item);
  return response.data;
}

async function getItems(sale) {
  
  const response = await axios.get(API_HOST + "/api/items", { params: {onSale: sale} });

  return response.data;
}

export { addCartItem, 
         findCartItem, 
         getCartItems, 
         removeCartItem, 
         updateCartItem,
         getItems };

