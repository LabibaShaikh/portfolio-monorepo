module.exports = (express, app) => {
    const controller = require("../controllers/item.controller.js");
    const router = express.Router();
  
    // Select multiple items (either sale or standard)
    router.get("/", controller.many);
  
    // Create an item in the database.
    router.put("/", controller.create);
  
    // Add routes to server.
    app.use("/api/items", router);
  };