import db from '../db/index.js';

const resolvers = {
  Query: {
    users: async () => {
      try {
        return await db.Users.findAll();
      } catch (error) {
        throw new Error('Error fetching users');
      }
    },
    items: async () => {
      try {
        return await db.Item.findAll();
      } catch (error) {
        throw new Error('Error fetching items');
      }
    },
    reviews: async () => {
      try {
        return await db.Review.findAll({ where: {isDeleted: 0} });
      } catch (error) {
        throw new Error('Error fetching reviews');
      }
    },
  },

  Mutation: {
    initializeBlockedField: async () => {
      try {
        await db.sequelize.query("ALTER TABLE users ADD COLUMN IF NOT EXISTS blocked BOOLEAN NOT NULL DEFAULT FALSE");
        await db.sequelize.query("UPDATE users SET blocked = FALSE WHERE blocked IS NULL");
        return "Blocked field initialized successfully!";
      } catch (error) {
        throw new Error('Error initializing blocked field');
      }
    },
    updateUserBlockStatus: async (_, { email, blocked }) => {
      try {
        const user = await db.Users.findOne({ where: { email } });
        if (!user) {
          throw new Error("User not found");
        }
        user.blocked = blocked;
        await user.save();
        return user;
      } catch (error) {
        throw new Error('Error updating user block status');
      }
    },
    createItem: async (_, { prodName, price, qty, onSale, imgPath }) => {
      try {
        const item = await db.Item.create({ prodName, price, qty, onSale, imgPath });
        return item;
      } catch (error) {
        throw new Error('Error creating item');
      }
    },
    updateItem: async (_, { id, prodName, price, qty, onSale, imgPath }) => {
      try {
        const item = await db.Item.findByPk(id);
        if (!item) {
          throw new Error('Item not found');
        }
        await item.update({ prodName, price, qty, onSale, imgPath });
        return item;
      } catch (error) {
        throw new Error('Error updating item');
      }
    },
    deleteItem: async (_, { id }) => {
      try {
        const item = await db.Item.findByPk(id);
        if (!item) {
          throw new Error('Item not found');
        }
        await item.destroy();
        return true;
      } catch (error) {
        throw new Error('Error deleting item');
      }
    },
    deleteReview: async (_, { id }) => {
      try {
        const review = await db.Review.findByPk(id);
        if (!review) {
          throw new Error('Review not found');
        }
        review.isDeleted = 1;
        await review.save();
        return true;
      } catch (error) {
        throw new Error('Error deleting review');
      }
    },
  },
};

export default resolvers;
