import express from 'express';
const router = express.Router();

// Example REST endpoint
router.get('/status', (req, res) => {
  res.send({ status: 'API is running' });
});

export default router;
