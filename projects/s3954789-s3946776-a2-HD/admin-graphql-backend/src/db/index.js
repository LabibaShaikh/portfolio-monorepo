import { Sequelize, DataTypes } from 'sequelize';
import config from './config.js'; 

import defineCartItem from './models/cartItem.js';
import defineFollower from './models/follower.js';
import defineItem from './models/item.js';
import defineReview from './models/review.js';
import defineUsers from './models/users.js';

// Create Sequelize instance
const sequelize = new Sequelize(config.DB, config.USER, config.PASSWORD, {
  host: config.HOST,
  dialect: config.DIALECT,
  logging: console.log, // Enable logging for development
});

const CartItem = defineCartItem(sequelize, DataTypes);
const Follower = defineFollower(sequelize, DataTypes);
const Item = defineItem(sequelize, DataTypes);
const Review = defineReview(sequelize, DataTypes);
const Users = defineUsers(sequelize, DataTypes);

// Define relationships
Item.hasMany(Review);
Review.belongsTo(Item, { foreignKey: 'itemId' });
Users.hasMany(Review);
Review.belongsTo(Users, { foreignKey: 'userEmail' });
Users.hasMany(Follower);
Follower.belongsTo(Users, { foreignKey: 'userFollowsEmail' });

const db = {
  sequelize,
  CartItem,
  Follower,
  Item,
  Review,
  Users
};

export default db;
