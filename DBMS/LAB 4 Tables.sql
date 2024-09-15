CREATE TABLE offices (
  office_code VARCHAR(10) PRIMARY KEY,
  city VARCHAR(50) NOT NULL,
  phone VARCHAR(50) NOT NULL,
  address_line1 VARCHAR(50) NOT NULL,
  address_line2 VARCHAR(50),
  state VARCHAR(50),
  country VARCHAR(50) NOT NULL,
  postal_code VARCHAR(15) NOT NULL,
  territory VARCHAR(10) NOT NULL
);

--------------------------------------------------------


CREATE TABLE employees (
  employee_number SERIAL PRIMARY KEY,
  last_name VARCHAR(50) NOT NULL,
  first_name VARCHAR(50) NOT NULL,
  extension VARCHAR(10) NOT NULL,
  email VARCHAR(100) NOT NULL,
  office_code VARCHAR(10) NOT NULL,
  reports_to INT,
  job_title VARCHAR(50) NOT NULL,
  FOREIGN KEY (reports_to) REFERENCES employees(employee_number),
  FOREIGN KEY (office_code) REFERENCES offices(office_code)
);

-------------------------------------------------------------------

CREATE TABLE customers (
  customer_number SERIAL PRIMARY KEY,
  customer_name VARCHAR(50) NOT NULL,
  contact_last_name VARCHAR(50) NOT NULL,
  contact_first_name VARCHAR(50) NOT NULL,
  phone VARCHAR(50) NOT NULL,
  address_line1 VARCHAR(50) NOT NULL,
  address_line2 VARCHAR(50),
  city VARCHAR(50) NOT NULL,
  state VARCHAR(50),
  postal_code VARCHAR(15),
  country VARCHAR(50) NOT NULL,
  sales_rep_employee_number INT,
  credit_limit DECIMAL(10, 2),
  FOREIGN KEY (sales_rep_employee_number) REFERENCES employees(employee_number)
);

--------------------------------------------------------------------------

CREATE TABLE productlines (
  product_line VARCHAR(50) PRIMARY KEY,
  text_description VARCHAR(4000),
  html_description TEXT,
  image BYTEA
);





------------------------------------------------------------
CREATE TABLE products (
  product_code VARCHAR(15) PRIMARY KEY,
  product_name VARCHAR(70) NOT NULL,
  product_line VARCHAR(50) NOT NULL,
  product_scale VARCHAR(10) NOT NULL,
  product_vendor VARCHAR(50) NOT NULL,
  product_description TEXT NOT NULL,
  quantity_in_stock SMALLINT NOT NULL,
  buy_price DECIMAL(10, 2) NOT NULL,
  msrp DECIMAL(10, 2) NOT NULL,
  FOREIGN KEY (product_line) REFERENCES productlines(product_line)
);

-------------------------------------------------------------------


CREATE TABLE payments (
  customer_number INT NOT NULL,
  check_number VARCHAR(50) NOT NULL,
  payment_date DATE NOT NULL,
  amount DECIMAL(10, 2) NOT NULL,
  PRIMARY KEY (customer_number, check_number),
  FOREIGN KEY (customer_number) REFERENCES customers(customer_number)
);

--------------------------------------------------------------------------


CREATE TABLE orders (
  order_number SERIAL PRIMARY KEY,
  order_date DATE NOT NULL,
  required_date DATE NOT NULL,
  shipped_date DATE,
  status VARCHAR(15) NOT NULL,
  comments TEXT,
  customer_number INT NOT NULL,
  FOREIGN KEY (customer_number) REFERENCES customers(customer_number)
);

------------------------------------------------------

CREATE TABLE orderdetails (
  order_number INT NOT NULL,
  product_code VARCHAR(15) NOT NULL,
  quantity_ordered INT NOT NULL,
  price_each DECIMAL(10, 2) NOT NULL,
  order_line_number SMALLINT NOT NULL,
  PRIMARY KEY (order_number, product_code),
  FOREIGN KEY (order_number) REFERENCES orders(order_number),
  FOREIGN KEY (product_code) REFERENCES products(product_code)
);









