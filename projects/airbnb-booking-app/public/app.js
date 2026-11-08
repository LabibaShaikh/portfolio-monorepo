// public/app.js

console.clear();
console.log('🛠️ app.js loaded');

const resultsDiv    = document.getElementById('results');
const paginationDiv = document.getElementById('pagination');
const searchForm    = document.getElementById('searchForm');

let allListings  = [];
let currentPage  = 1;
const perPage    = 5;

// Fisher–Yates shuffle
function shuffle(arr) {
  for (let i = arr.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [arr[i], arr[j]] = [arr[j], arr[i]];
  }
}

// Render a list of cards linking to listing.html + Book Now
function renderListings(listings) {
  resultsDiv.innerHTML = '';
  listings.forEach(l => {
    const price = (l.price && typeof l.price === 'object')
      ? (l.price.$numberDecimal || l.price.toString())
      : l.price;
    const rating = (l.rating != null)
      ? `${(l.rating/20).toFixed(1)}/5 ⭐`
      : 'No rating';

    const card = document.createElement('div');
    card.className = 'listing';
    card.innerHTML = `
      <h3>
        <a href="listing.html?listing_id=${l.listing_id}">
          ${l.name}
        </a>
      </h3>
      <p>${l.summary || 'No summary.'}</p>
      <p>Type: ${l.property_type||'N/A'} | Beds: ${l.bedrooms||'N/A'}</p>
      <p>Price: $${price ?? 'N/A'} | Rating: ${rating}</p>
      <p>
        <a class="btn" href="booking.html?listing_id=${l.listing_id}">
          Book Now →
        </a>
      </p>
    `;
    resultsDiv.appendChild(card);
  });
}

// Pagination controls
function renderPagination() {
  paginationDiv.innerHTML = '';
  const total = allListings.length;
  const pages = Math.ceil(total / perPage);
  if (pages <= 1) return;

  if (currentPage > 1) {
    const prev = document.createElement('button');
    prev.textContent = '← Previous';
    prev.onclick     = () => renderPage(currentPage - 1);
    paginationDiv.appendChild(prev);
  }

  paginationDiv.appendChild(
    document.createTextNode(` Page ${currentPage} of ${pages} `)
  );

  if (currentPage < pages) {
    const next = document.createElement('button');
    next.textContent = 'Next →';
    next.onclick     = () => renderPage(currentPage + 1);
    paginationDiv.appendChild(next);
  }
}

function renderPage(page) {
  currentPage = page;
  const start = (page - 1) * perPage;
  renderListings(allListings.slice(start, start + perPage));
  renderPagination();
}

// On initial load, show 5 random
async function performInitialLoad() {
  try {
    const res      = await fetch('/search');
    const listings = await res.json();
    shuffle(listings);
    renderListings(listings.slice(0, perPage));
    paginationDiv.innerHTML = '';
  } catch (err) {
    console.error('Initial load error:', err);
  }
}

// On search, fetch & paginate
async function performSearch() {
  const params = new URLSearchParams({
    location:   document.getElementById('location').value,
    type:       document.getElementById('type').value,
    bedrooms:   document.getElementById('bedrooms').value,
    priceRange: document.getElementById('priceRange').value,
    minRating:  document.getElementById('minRating').value
  });
  console.log('🔍 /search?' + params);
  const res      = await fetch(`/search?${params}`);
  const listings = await res.json();
  allListings    = listings;
  renderPage(1);
}

// Hook up search form
if (searchForm) {
  searchForm.addEventListener('submit', e => {
    e.preventDefault();
    performSearch();
  });
}

// On DOM ready: random sample
document.addEventListener('DOMContentLoaded', performInitialLoad);

// 2) Load & Display Bookings
/**
 * Asynchronously loads booking data from the server and updates the DOM
 * to display current and past bookings.
 *
 * Fetches booking data from the `/bookings` endpoint, processes the data,
 * and dynamically creates booking cards to display in the appropriate
 * sections of the page. Current bookings are displayed in the "current-bookings"
 * section, while past bookings are displayed in the "past-bookings" section.
 *
 * Booking cards include details such as the property name, booking dates,
 * guest name, and price. If no bookings are available, a placeholder message
 * is displayed in each section.
 *
 * @async
 * @function loadBookings
 * @returns {Promise<void>} Resolves when the booking data has been fetched
 *                          and the DOM has been updated.
 */
async function loadBookings() {
  const resp = await fetch('/bookings');
  const bs   = await resp.json();
  const now  = new Date();

  const curDiv  = document.getElementById('current-bookings');
  const pastDiv = document.getElementById('past-bookings');
  curDiv.innerHTML  = '';
  pastDiv.innerHTML = '';

  bs.forEach(b => {
    const start = new Date(b.start_date);
    const end   = new Date(b.end_date);
    const isPast = end < now;

    let price = b.listing_price;
    if (price && typeof price === 'object') {
      price = price.$numberDecimal ?? price.toString();
    }
    price = price ?? 'N/A';

    // DD/MM/YYYY formatting
    const startStr = start.toLocaleDateString('en-GB', { day:'2-digit', month:'2-digit', year:'numeric' });
    const endStr   = end.toLocaleDateString('en-GB',   { day:'2-digit', month:'2-digit', year:'numeric' });

    const card = document.createElement('div');
    card.className = 'booking-card';
    card.innerHTML = `
      <div class="booking-header">
        <h4>${b.listing_name || 'Unknown Property'}</h4>
        <span>${startStr} → ${endStr}</span>
      </div>
      <div class="booking-details">
        <p><strong>Guest:</strong> ${b.client_name}</p>
        <p><strong>Price:</strong> $${price}</p>
      </div>
    `;
    (isPast ? pastDiv : curDiv).appendChild(card);
  });

  if (!curDiv.children.length)  curDiv.innerHTML  = '<p>No current bookings</p>';
  if (!pastDiv.children.length) pastDiv.innerHTML = '<p>No past bookings</p>';
}
window.loadBookings = loadBookings;
