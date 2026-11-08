module.exports = (sequelize, DataTypes) =>
  sequelize.define("item", {
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
        type: DataTypes.INTEGER(2),
        allowNull: false
      },
      onSale: {
          type: DataTypes.TINYINT(1),
          allowNull: false
      },
      imgPath: {
        type: DataTypes.STRING(20),
        allowNull: false
      }
    }, {
      // Don't add the timestamp attributes (updatedAt, createdAt).
      timestamps: false
    });