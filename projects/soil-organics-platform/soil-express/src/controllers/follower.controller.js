const db = require("../database");


//follow a user
exports.create = async (req, res) => {
    const userToFollow = await db.follower.create({
        userEmail: req.body.userEmail,
        userFollowsEmail: req.body.userFollowsEmail
      });
  res.json("User followed successfully");
};

//unfollow a user
exports.remove = async (req, res) => {
    const userToUnfollow = await db.follower.findOne({ 
        where: {
            userEmail: req.query.userEmail,
            userFollowsEmail: req.query.userFollowsEmail
        }
    });
    console.log(userToUnfollow.id);
    
    if(userToUnfollow) {
        await userToUnfollow.destroy();
        res.status(200).json({ message: 'Follower removed successfully' });
    }
    else {
        res.status(404).json({ message: 'Follower not found' });
    }
};

//get followed users - works
exports.many = async (req, res) => {
    const followedUsers = await db.follower.findAll({where : {userEmail: req.query.userEmail}});
    
    if (followedUsers) {
        res.json(followedUsers);
    }
    else {
        res.json({message: 'Follower not found'});
    }
    
};