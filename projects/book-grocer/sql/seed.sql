INSERT INTO orders (id, customer_id, status)
VALUES ('01001', 'user.example@mail.com', 'PENDING');

INSERT INTO order_items (order_id, sku, qty)
VALUES
('01001', 'BK001', 2),
('01001', 'BK002', 1);
