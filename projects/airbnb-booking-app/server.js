require('dotenv').config();
const express      = require('express');
const { MongoClient } = require('mongodb');
const path         = require('path');

const app  = express();
const PORT = process.env.PORT || 3000;
const URI  = process.env.MONGO_URI;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

let db, listingsCol, bookingsCol;
async function startServer() {
  const client = await MongoClient.connect(URI);
  db          = client.db('sample_airbnb');
  listingsCol = db.collection('listingsAndReviews');
  bookingsCol = db.collection('bookings');
  console.log('🌸 Connected to MongoDB');
  app.listen(PORT, () => console.log(`✨ Server running on http://localhost:${PORT}`));
}

// 1) GET /listing — return full details for one listing
app.get('/listing', async (req, res) => {
  const id = req.query.listing_id;
  if (!id) return res.status(400).json({ error: 'Invalid listing_id' });

  try {
    /**
     * Retrieves a single document from the `listingsCol` collection based on the provided `_id`.
     * The document includes specific fields such as name, summary, description, property type, 
     * bedrooms, price, review scores, and address.
     *
     * @param {Object} id - The unique identifier (_id) of the document to retrieve.
     * @returns {Promise<Object|null>} A promise that resolves to the document if found, or `null` if no document matches the query.
     */
    const doc = await listingsCol.findOne(
      { _id: id },   // sample_airbnb uses string _id
      { projection: {
          name:          1,
          summary:       1,
          description:   1,
          property_type: 1,
          bedrooms:      1,
          price:         1,
          review_scores: 1,
          address:       1
        }
      }
    );
    if (!doc) return res.status(404).json({ error: 'Listing not found' });

    res.json({
      listing_id: id,
      name:       doc.name,
      summary:    doc.summary,
      description:doc.description,
      type:       doc.property_type,
      bedrooms:   doc.bedrooms,
      price:      doc.price,
      rating:     doc.review_scores?.review_scores_rating,
      location:   doc.address?.market
    });
  } catch (err) {
    console.error('❌ /listing error:', err);
    res.status(500).json({ error: 'Server error' });
  }
});

// 2) GET /search — return filtered listings
app.get('/search', async (req, res) => {
  const { location, type, bedrooms, priceRange, minRating } = req.query;
  const q = {};
  if (location)  q['address.market']                       = { $regex: new RegExp(location, 'i') };
  if (type)      q.property_type                            = type;
  if (bedrooms)  q.bedrooms                                 = parseInt(bedrooms, 10);
  if (priceRange) {
    const [min, max] = priceRange.split('-').map(Number);
    if (priceRange === '300+')      q.price = { $gte: 300 };
    else if (!isNaN(max))           q.price = { $gte: min, $lte: max };
  }
  if (minRating && !isNaN(minRating)) {
    q['review_scores.review_scores_rating'] = { $gte: parseFloat(minRating) };
  }

  try {
    const docs = await listingsCol
      .find(q)
      .limit(20)
      .project({
        _id:           1,
        name:          1,
        summary:       1,
        price:         1,
        review_scores: 1,
        property_type: 1,
        bedrooms:      1,
        address:       1
      })
      .toArray();

    /**
     * Transforms an array of document objects into an array of listing objects.
     *
     * @typedef {Object} Listing
     * @property {string} listing_id - The unique identifier for the listing.
     * @property {string} name - The name of the listing.
     * @property {string} summary - A brief description of the listing.
     * @property {number} price - The price of the listing.
     * @property {number} [rating] - The review score rating of the listing (optional).
     * @property {string} property_type - The type of property for the listing.
     * @property {number} bedrooms - The number of bedrooms in the listing.
     * @property {string} [location] - The market location of the listing (optional).
     *
     * @param {Array<Object>} docs - The array of document objects to transform.
     * @returns {Listing[]} An array of listing objects.
     */
    const listings = docs.map(d => ({
      listing_id:    d._id,
      name:          d.name,
      summary:       d.summary,
      price:         d.price,
      rating:        d.review_scores?.review_scores_rating,
      property_type: d.property_type,
      bedrooms:      d.bedrooms,
      location:      d.address?.market
    }));

    console.log(`📊 Found ${listings.length} listings; sample id: ${listings[0]?.listing_id}`);
    res.json(listings);

  } catch (err) {
    console.error('❌ /search error:', err);
    res.status(500).json({ error: 'Failed to fetch listings' });
  }
});

// 3) POST /book — insert booking
app.post('/book', async (req, res) => {
  const id = req.body.listing_id;
  if (!id) return res.status(400).send('Invalid listing_id');

  try {
    /**
     * Retrieves a single listing document from the database by its ID.
     * The returned document includes only the `name`, `property_type`, and `price` fields.
     *
     * @constant
     * @type {Promise<Object|null>}
     * @property {string} name - The name of the listing.
     * @property {string} property_type - The type of property (e.g., apartment, house).
     * @property {number} price - The price of the listing.
     * @returns {Promise<Object|null>} A promise that resolves to the listing document or `null` if not found.
     */
    const lst = await listingsCol.findOne(
      { _id: id },
      { projection: { name: 1, property_type: 1, price: 1 } }
    );
    if (!lst) {
      console.error('❌ Listing not found:', id);
      return res.status(404).send('Listing not found');
    }

    await bookingsCol.insertOne({
      ...req.body,
      listing_name:  lst.name,
      listing_type:  lst.property_type,
      listing_price: lst.price,
      created_at:    new Date()
    });

    console.log('✅ Booking saved for listing_id', id);
    res.send('✅ Booking successful! Thank you.');

  } catch (err) {
    console.error('❌ /book error:', err);
    res.status(500).send('Failed to book');
  }
});

// 4) GET /bookings — return all bookings
app.get('/bookings', async (req, res) => {
  try {
    /**
     * Retrieves all booking documents from the database, sorted in descending order by their creation date.
     * 
     * @constant {Array} all - An array of booking documents retrieved from the database.
     * @async
     */
    const all = await bookingsCol.find().sort({ created_at: -1 }).toArray();
    console.log(`📋 Returning ${all.length} bookings`);
    res.json(all);
  } catch (err) {
    console.error('❌ /bookings error:', err);
    res.status(500).json({ error: 'Failed to fetch bookings' });
  }
});

startServer().catch(err => {
  console.error('Startup error:', err);
  process.exit(1);
});
