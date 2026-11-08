module.exports = (sequelize, DataTypes) =>
    sequelize.define("follower", {
        //Adds columns to the table in our database
        userEmail: {
            type: DataTypes.STRING,
            allowNull: false,
        },
        userFollowsEmail: {
            type: DataTypes.STRING,
            allowNull: false,
        }
      }, {
        // Don't add the timestamp attributes (updatedAt, createdAt).
        timestamps: false
      });