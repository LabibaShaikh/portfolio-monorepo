const { Sequelize, DataTypes } = require("sequelize");
const config = require("./config.js");
 
// Create Sequelize instance
const sequelize = new Sequelize(config.DB, config.USER, config.PASSWORD, {
  host: config.HOST,
  dialect: config.DIALECT,
  logging: console.log,  // Enable logging for development
});
 
const db = {
  Op: Sequelize.Op
};
 
// Items to add in our db
const items = [
  { prodName: "Large Corn - 6 pack", price: 3.00, qty: 1, onSale: 1, imgPath: "./Corn.jpg" },
  { prodName: "HealthNuts Muesli Bar - 5 pack", price: 3.50, qty: 1, onSale: 1, imgPath: "./MuesliBar.jpg" },
  { prodName: "Nature's Noodle Co. - 500g High Protein Pasta", price: 4.00, qty: 1, onSale: 1, imgPath: "./Pasta.jpg" },
  { prodName: "Fresh Spinach - 300g", price: 4.00, qty: 1, onSale: 1, imgPath: "./Spinach.jpg" },
  { prodName: "Yokos Unsweetened Yoghurt - 500g", price: 2.50, qty: 1, onSale: 1, imgPath: "./Yoghurt.jpg" },
  { prodName: "Dough Delight Co. Wholemeal Bread Loaf", price: 3.50, qty: 1, onSale: 1, imgPath: "./bread.jpg" },
  { prodName: "Fresh Avocado", price: 4.00, qty: 1, onSale: 0, imgPath: "./Avocado.jpg" },
  { prodName: "Black Seedless Grapes", price: 5.70, qty: 1, onSale: 0, imgPath: "./Blackgrapes.jpg" },
  { prodName: "Strawberries 250g punnet", price: 5.00, qty: 1, onSale: 0, imgPath: "./Strawberry.jpg" },
  { prodName: "Fresh Broccoli", price: 2.70, qty: 1, onSale: 0, imgPath: "./Broccoli.jpg" },
  { prodName: "Fresh Cabbage", price: 8.50, qty: 1, onSale: 0, imgPath: "./Cabbage.jpg" },
  { prodName: "Roasted Chickpeas, 100g", price: 4.80, qty: 1, onSale: 0, imgPath: "./Chickpeas.jpg" },
  { prodName: "Smooth Organic Cashew Butter", price: 7.00, qty: 1, onSale: 0, imgPath: "./CashewButter.jpg" },
  { prodName: "Exxatics Organic Jelly Beans - 50g", price: 6.50, qty: 1, onSale: 0, imgPath: "./JellyBeans.jpg" },
  { prodName: "Earth Cold Pressed Pineapple Juice", price: 4.50, qty: 1, onSale: 0, imgPath: "./Juice.jpg" }
];
 
// Include models
db.review = require("./models/review.js")(sequelize, DataTypes);
db.cartItem = require("./models/cartItem.js")(sequelize, DataTypes);
db.item = require("./models/item.js")(sequelize, DataTypes);
db.users = require("./models/users.js")(sequelize, DataTypes);
db.follower = require("./models/follower.js")(sequelize, DataTypes);
 
// Define relationships
db.item.hasMany(db.review);
db.review.belongsTo(db.item, { foreignKey: 'itemId' });
db.users.hasMany(db.review);
db.review.belongsTo(db.users, { foreignKey: 'userEmail' });
db.users.hasMany(db.follower);
db.follower.belongsTo(db.users, { foreignKey: 'userFollowsEmail' });
db.item.hasOne(db.cartItem, { foreignKey: 'id', sourceKey: 'id' });
db.cartItem.belongsTo(db.item, { foreignKey: 'id', targetKey: 'id' });
 
async function seedData() {
  try {
    for (let i = 0; i < items.length; i++) {
      await db.item.create(items[i]);
    }
  } catch (error) {
    console.error('Failed to seed data:', error);
  }
}
 
// Define sync method on db object
db.sync = async (options = {}) => {
  try {
    await sequelize.sync(options);
    await seedData();
    console.log('Database & tables created!');
  } catch (error) {
    console.error('Failed to sync database:', error);
  }
};
 
// Authenticate the connection and sync the database
sequelize.authenticate().then(() => {
  console.log('Connection has been established successfully.');
  db.sync({ force: true });
}).catch(err => {
  console.error('Unable to connect to the database:', err);
});
 
module.exports = db;
