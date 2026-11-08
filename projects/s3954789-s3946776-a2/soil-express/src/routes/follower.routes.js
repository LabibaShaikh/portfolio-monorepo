module.exports = (express, app) => {
    const controller = require("../controllers/follower.controller.js");
    const router = express.Router();
  
    //follow a user
    router.post("/", controller.create);

    //unfollow a user 
    router.delete("/", controller.remove);

    //get followed users 
    router.get("/", controller.many);
  
    // Add routes to server.
    app.use("/api/followers", router);
  };