const defineFollower = (sequelize, DataTypes) => {
  return sequelize.define("follower", {
    userEmail: {
      type: DataTypes.STRING,
      allowNull: false,
    },
    userFollowsEmail: {
      type: DataTypes.STRING,
      allowNull: false,
    }
  }, {
    timestamps: false
  });
};

export default defineFollower;
