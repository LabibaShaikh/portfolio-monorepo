-- Orders table

CREATE TABLE orders(

id TEXT PRIMARY KEY,
customer_email TEXT NOT NULL,
status TEXT NOT NULL CHECK(status IN ('pending', 'fulfilled', 'cancelled;)),
created_at TIMESTAMP NOT NULL DEFAULT NOW()
);

-- Order items table one-to-many

CREATE TABLE order_items(
id SERIAL PRIMARY KEY,
order_id TEXT NOT NULL REFERENCES orders(id) ON DELETE CASCADE;
sku TEXT NOT NULL, 
qty INTEGER NOT NULL CHECK (qty > 0)
);