const db = require("../database");
const argon2 = require("argon2");

// Select one item from the database.
exports.one = async (req, res) => {
    const item = await db.item.findByPk(req.params.id);
  
    res.json(item);
  };

//Select sale items from the database
exports.many = async (req, res) => {
    const saleItems = await db.item.findAll({where: { onSale: req.query.onSale }});
  
    res.json(saleItems);
  };
  
// Create an item in the database.
exports.create = async (req, res) => {

const item = await db.item.create({
    id: req.body.id,
    prodName: req.body.prodName,
    price: req.body.price,
    qty: req.body.qty,
    onSale: req.body.onSale,
    imgPath: req.body.imgPath
});

res.json(item);
};