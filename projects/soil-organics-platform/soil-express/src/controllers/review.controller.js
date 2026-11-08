const db = require("../database");

// Get the number of reviews currently in the db
exports.all = async (req, res) => {
  const reviews = await db.review.findAll();

  res.json(reviews);
}

// Select all reviews for a specific item.
exports.many = async (req, res) => {
  const reviews = await db.review.findAll({
    where: {
      itemId: req.params.id,
    },
  });
  res.json(reviews);
};

// Create a review in the database.
exports.create = async (req, res) => {
  const review = await db.review.create({
    rating: req.body.rating,
    reviewText: req.body.reviewText,
    itemId: req.body.itemId,
    userEmail: req.body.userEmail
  });
  res.json(review);
};

exports.delete = async (req, res) => {
  //Get review to remove
  console.log(req.params.id);
  const review = await db.review.findByPk(req.params.id);
  console.log(review);

  if (review) {
    await review.destroy();
    res.status(200).json({ message: 'Item removed successfully' });
  }
  else {
    console.log("Not found");
  }

};

//Update review in DB
exports.update = async (req, res) => {
  const review = await db.review.findByPk(req.body.id);
  console.log(req.body.id);

  //Update and save the review with new info
  Object.assign(review, req.body);
  await review.save();
  res.json(review);
};
