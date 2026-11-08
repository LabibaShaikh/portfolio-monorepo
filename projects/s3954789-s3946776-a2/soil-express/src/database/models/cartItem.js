module.exports = (sequelize, DataTypes) =>
  sequelize.define("cartItem", {
      //Adds columns to the table in our database
     
      id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
      },
      prodName: {
        type: DataTypes.STRING(100),
        allowNull: false
      },
      price: {
        type: DataTypes.DOUBLE(5, 2),
        allowNull: false
      },
      qty: {
        type: DataTypes.INTEGER(1),
        allowNull: false
      }
    }, {
      // Don't add the timestamp attributes (updatedAt, createdAt).
      timestamps: false
    });