-- 1. What are all the columns and rows in the employees table?
SELECT * 
FROM employees;

-- 2. What are the last names, first names, and job titles of employees?
SELECT last_name, first_name, job_title 
FROM employees;

-- 3. What are the first names, last names, and email addresses of employees who have the job title "President"?
SELECT first_name, last_name, email 
FROM employees 
WHERE job_title = 'President';

-- 4. What are the unique job titles present in the employees table?
SELECT DISTINCT job_title 
FROM employees;

-- 5. How are employees' first names and job titles ordered, with first names sorted in ascending order and job titles sorted in descending order?
SELECT first_name, last_name, job_title 
FROM employees 
ORDER BY first_name ASC, job_title DESC;

-- 6. What are the unique city and state combinations in the customers table?
SELECT DISTINCT city, state 
FROM customers;

-- 7. What are the first names and last names of the first 5 employees in the employees table?
SELECT first_name, last_name 
FROM employees 
LIMIT 5;

-- 8. What are the first names and last names of 5 employees starting from the 11th row in the employees table?
SELECT first_name, last_name 
FROM employees 
LIMIT 5 OFFSET 10;

-- 9. What are the office codes, cities, and phone numbers for offices located in the USA or France?
SELECT office_code, city, phone 
FROM offices 
WHERE country IN ('USA', 'France');

-- 11. Which orderNumber values have a total value of quantityOrdered * priceEach greater than 60,000?
SELECT order_number 
FROM orderdetails 
GROUP BY order_number 
HAVING SUM(quantity_ordered * price_each) > 60000;

-- 12. What are the orderNumber, customerNumber, status, and shippedDate for orders whose total value (based on quantityOrdered * priceEach) exceeds 60,000?
SELECT order_number, customer_number, status, shipped_date
FROM orders
WHERE order_number IN (
    SELECT order_number
    FROM orderdetails
    GROUP BY order_number
    HAVING SUM(quantity_ordered * price_each) > 60000
);

-- 13. What are the employee numbers, last names, and first names of employees whose first name starts with the letter 'A'?
SELECT employee_number, last_name, first_name 
FROM employees 
WHERE first_name LIKE 'A%';

-- 14. What are the employee numbers, last names, and first names of employees whose last name ends with 'on'?
SELECT employee_number, last_name, first_name 
FROM employees 
WHERE last_name LIKE '%on';

-- 15. What are the employee numbers, last names, and first names of employees whose last name does not start with the letter 'B'?
SELECT employee_number, last_name, first_name 
FROM employees 
WHERE last_name NOT LIKE 'B%';

-- 16. What are the customer numbers and contact last names from the customers table combined with the employee numbers and first names from the employees table, with duplicates removed?
SELECT customer_number AS id, contact_last_name AS name 
FROM customers
UNION
SELECT employee_number AS id, first_name AS name 
FROM employees;

-- 17. What are the combined customer numbers and contact last names from the customers table with employee numbers and first names from the employees table, sorted by name and id?
(SELECT customer_number AS id, contact_last_name AS name 
 FROM customers)
UNION
(SELECT employee_number AS id, first_name AS name 
 FROM employees)
ORDER BY name, id;

-- 18. What are the combined customer numbers and contact last names from the customers table with employee numbers and first names from the employees table, sorted by contactLastname and customerNumber?
(SELECT customer_number, contact_last_name 
 FROM customers)
UNION
(SELECT employee_number, first_name 
 FROM employees)
ORDER BY contact_last_name, customer_number;
