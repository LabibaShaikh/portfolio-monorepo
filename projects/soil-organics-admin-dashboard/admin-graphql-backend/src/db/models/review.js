// src/models/review.js
const defineReview = (sequelize, DataTypes) => {
  return sequelize.define("review", {
    id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true
    },
    userEmail: {
      type: DataTypes.STRING,
      allowNull: false,
      validate: { isEmail: true }
    },
    itemId: {
      type: DataTypes.INTEGER,
      allowNull: false
    },
    reviewText: {
      type: DataTypes.STRING,
      allowNull: false
    },
    rating: {
      type: DataTypes.INTEGER,
      allowNull: false
    },
    isDeleted: {
      type: DataTypes.BOOLEAN,
      allowNull: false,
      defaultValue: false
    },
 
  }, {
    timestamps: false
  });
};

export default defineReview;
