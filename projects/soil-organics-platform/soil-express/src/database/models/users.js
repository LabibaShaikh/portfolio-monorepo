module.exports = (sequelize, DataTypes) => {
  return sequelize.define("users", {
    email: {
      type: DataTypes.STRING,
      allowNull: false,
      primaryKey: true,
      validate: { isEmail: true }
    },
    password: {
      type: DataTypes.STRING,
      allowNull: false
    },
    firstName: {
      type: DataTypes.STRING,
      allowNull: false
    },
    lastName: {
      type: DataTypes.STRING,
      allowNull: true
    },
    dateOfJoining: {
      type: DataTypes.DATE,
      allowNull: false
    },
    blocked: {
      type: DataTypes.BOOLEAN,
      allowNull: false,
      defaultValue: false
    }
  }, {
    tableName: 'users',
    timestamps: false
  });
};


