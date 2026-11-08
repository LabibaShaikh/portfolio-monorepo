const db = require("../database");
const argon2 = require("argon2");

// Select all cartItems from the database.
exports.all = async (req, res) => {
  const cartItems = await db.cartItem.findAll();

  res.json(cartItems);
};

// Select one cart item from the database.
exports.one = async (req, res) => {
  const cartItem = await db.cartItem.findByPk(req.params.id);

  res.json(cartItem);
};

// Create a cart item in the database.
exports.create = async (req, res) => {
  
  const cartItem = await db.cartItem.create({
    id: req.body.id,
    prodName: req.body.prodName,
    price: req.body.price,
    qty: req.body.qty
  });

  res.json(cartItem);
};

//Remove cart item from database
exports.delete = async (req, res) => {
  // Get cart item to remove
  const cartItem = await db.cartItem.findByPk(req.params.id);
  console.log(cartItem);

  if (cartItem) {
    await cartItem.destroy();
    res.status(200).json({ message: 'Item removed successfully' });
  }
  else {
    console.log("Not found");
    // res.status(404).json({ message: 'Item not found' });
  }
};

//Update qty on a cart item in database
exports.update = async (req, res) => {
  const cartItem = await db.cartItem.findByPk(req.body.id);

  //Update and save the item with new info
  Object.assign(cartItem, req.body);
  await cartItem.save();
  res.json(cartItem);
}