// src/models/item.js
const defineItem = (sequelize, DataTypes) => {
  return sequelize.define("item", {
    id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true
     
    },
    prodName: {
      type: DataTypes.STRING,
      allowNull: false
    },
    price: {
      type: DataTypes.DOUBLE,
      allowNull: false
    },
    qty: {
      type: DataTypes.INTEGER,
      allowNull: false
    },
    onSale: {
      type: DataTypes.TINYINT,
      allowNull: false
    },
    imgPath: {
      type: DataTypes.STRING(20),
      allowNull: false,
    },
  },
   {
    timestamps: false
  });
};

export default defineItem;
