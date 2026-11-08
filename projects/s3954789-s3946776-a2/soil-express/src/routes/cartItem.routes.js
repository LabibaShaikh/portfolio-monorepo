module.exports = (express, app) => {
    const controller = require("../controllers/cartItem.controller.js");
    const router = express.Router();
  
    // Select all cart items.
    router.get("/", controller.all);
  
    // Select a single item with id.
    router.get("/select/:id", controller.one);
  
    // Create a new cart item.
    router.post("/", controller.create);

    //Remove a cart item
    router.delete("/remove/:id", controller.delete);

    //Update a cart item
    router.put("/", controller.update);
  
    // Add routes to server.
    app.use("/api/cartItems", router);
  };