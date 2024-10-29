Aggregate Functions and SQL Joins


Questions

1. What productCode and productName are associated with each orderNumber?
Ans:
    SELECT A.product_code, A.product_name, B.order_number
    FROM products A
    INNER JOIN orderDetails B ON A.product_code = B.product_code;

2. What are the customerNumber, customerName, orderNumber, and status for all customers and their orders?
Ans:
    SELECT c.customer_number, customer_name, order_number, o.status
    FROM customers c
    LEFT JOIN orders o ON c.customer_number = o.customer_number;


3. What are the customerNumber, orderNumber, status, and customerName for all orders and their associated customers?
Ans:
    SELECT o.customer_number, order_number, o.status, customer_name
    FROM orders o
    RIGHT JOIN customers c ON o.customer_number = c.customer_number;

4. What are the customerNumber, customer_name, salesRepEmployeeNumber, last_name, and first_name for customers and their sales representatives?
Ans:
    SELECT c.customer_number, c.customer_name, c.sales_rep_employee_number, e.last_name, e.first_name
    FROM customers c
    LEFT OUTER JOIN employees e ON c.sales_rep_employee_number = e.employee_number;

5. What are the customerNumber, customerName, employeeNumber, lastName, and firstName for employees and their associated customers?
Ans:
    SELECT c.customer_number, c.customer_name, e.employee_number, e.last_name, e.first_name
    FROM customers c
    RIGHT OUTER JOIN employees e ON c.sales_rep_employee_number = e.employee_number;

6. How can you perform a FULL OUTER JOIN between customers and employees in MySQL?
Ans:
    (SELECT c.customer_number, c.customer_name, e.employee_number, e.last_name, e.first_name
    FROM customers c
    LEFT JOIN employees e ON c.sales_rep_employee_number = e.employee_number)
    UNION
    (SELECT c.customer_number, c.customer_name, e.employee_number, e.last_name, e.first_name
    FROM customers c
    RIGHT JOIN employees e ON c.sales_rep_employee_number = e.employee_number);

7. What are the customerNumber, orderNumber, status, and customerName for all orders with associated customers?
Ans:
    SELECT o.customer_number, order_number, o.status, customer_name
    FROM orders o
    JOIN customers c ON o.customer_number = c.customer_number;

8. What are the customerNumber, orderNumber, status, and customerName for all orders with associated customers using a natural join?
Ans:
    SELECT o.customer_number, o.order_number, o.status, c.customer_name
	FROM orders o
	NATURAL JOIN customers c;


9. What are the customerNumber, orderNumber, status, and customerName for all orders with associated customers using an inner join?
Ans:
	SELECT o.customer_number, o.order_number, o.status, c.customer_name
	FROM orders o
	INNER JOIN customers c ON o.customer_number = c.customer_number;


10. What are the customerNumber, orderNumber, status, and customerName for orders and customers using a join on customerNumber?
Ans:
    SELECT o.customer_number, o.order_number, o.status, c.customer_name
	FROM orders o
	JOIN customers c USING (customer_number);


11. How can you perform a join across three tables: customers, orders, and orderdetails?
Ans:
    SELECT c.customer_number, c.customer_name, o.order_number, od.product_code
	FROM customers c
	LEFT OUTER JOIN orders o ON c.customer_number = o.customer_number
	INNER JOIN orderdetails od ON o.order_number = od.order_number;


12. What are the customerNumber, checkNumber, and amount from payments where (customerNumber, checkNumber) is not in a set of pairs with smaller amounts?
Ans:
    SELECT p.customer_number, p.check_number, p.amount
	FROM payments p
	WHERE (p.customer_number, p.check_number) NOT IN (
    SELECT q.customer_number, q.check_number
    FROM payments q
    WHERE q.amount < (
        SELECT MAX(r.amount)
        FROM payments r
        WHERE r.customer_number = q.customer_number
          AND r.check_number = q.check_number
    )
);


13. What are the customerNumber and customerName for customers whose names contain the substring 'toys'?
Ans:
	SELECT customer_number, customer_name
	FROM customers
	WHERE customer_name LIKE '%toys%';




15. What are the firstName, lastName, and extension for employees whose extensions match the pattern 'x_ _ _ '?
Ans:
    SELECT first_name, last_name, extension
	FROM employees
	WHERE extension LIKE 'x___';  -- Note: _ is a wildcard for a single character, so 'x___' matches x followed by exactly three characters.


16. What are the firstName and lastName (converted to uppercase) for employees?
Ans:
	SELECT first_name, UPPER(last_name) AS last_name
	FROM employees;


17. What are the productCode and productName for products with stock quantities less than 100 that are also listed in the orderdetails?
Ans:
  SELECT p.product_code, p.product_name
  FROM products p
  WHERE p.quantity_in_stock < 100
  AND EXISTS (
    SELECT 1
    FROM orderdetails o
    WHERE p.product_code = o.product_code
  );

-- 18. What are the ordernumber, total number of items (itemsCount), and total price (total) for orders with total price greater than 1000 and items count greater than 600?
-- Ans:
--     SELECT order_number, 
--        SUM(quantity_ordered) AS items_count, 
--        SUM(price_each * quantity_ordered) AS total
-- 	FROM orderdetails
-- 	GROUP BY order_number
-- 	HAVING total > 1000 AND items_count > 600;


19. What are the ordernumber and itemsCount for orders where the total number of items is greater than 300?
Ans:
    SELECT order_number, items_count
	FROM (
    SELECT order_number, 
           SUM(quantity_ordered) AS items_count
    FROM orderdetails
    GROUP BY order_number
) AS t
WHERE t.items_count > 300;

















