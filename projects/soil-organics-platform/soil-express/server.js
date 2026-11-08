// server.js
const express = require("express");
const cors = require("cors");
const db = require("./src/database");

const app = express();

app.use(express.json());
app.use(cors());

const userRoutes = require('./src/routes/users.routes');
//THIS MIGHT BE CAUSING AN ERROR WITH THE SHOPPING CART FUNCTIONS
//IF IT IS, CHANGE TO THE ONE ON LINE 15
const cartItemRoutes = require("./src/routes/cartItem.routes");
require("./src/routes/review.routes.js")(express, app);
require("./src/routes/cartItem.routes.js")(express, app);
require("./src/routes/item.routes.js")(express, app);
require("./src/routes/follower.routes.js")(express, app);

app.use('/api/users', userRoutes);
app.use('/api/cartItems', cartItemRoutes);

app.get("/", (req, res) => {
  res.json({ message: "Hello World!" });
});

db.sync({ alter: true }).then(() => {
  const PORT = process.env.PORT || 4000;
  app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
  });
}).catch(error => {
  console.error('Failed to sync database:', error);
  process.exit(1);
});

module.exports = app;
