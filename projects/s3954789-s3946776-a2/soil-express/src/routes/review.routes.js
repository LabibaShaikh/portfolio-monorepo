module.exports = (express, app) => {
  const controller = require("../controllers/review.controller.js");
  const router = express.Router();

  // Select all reviews in the DB
  router.get("/", controller.all);

  // Select all reviews for an item.
  router.get("/select/:id", controller.many);

  // Create a new review.
  router.post("/", controller.create);

  //Delete a review
  router.delete("/remove/:id", controller.delete);

  //Update a review
  router.put("/", controller.update);

  // Add routes to server.
  app.use("/api/reviews", router);
};
