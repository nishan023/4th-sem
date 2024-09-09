DDL

show databases;

create database db_bct031;

use db_bct031;

show tables;

describe student;

Questions

1. Creating a new table Employees with columns for employee ID, first name, last name, and hire date.
Ans:
	CREATE TABLE Employees (
    		EmployeeID SERIAL PRIMARY KEY,     -- SERIAL auto-increments and is a primary key
    		FirstName VARCHAR(50) NOT NULL,    -- FirstName is a variable character field with a maximum length of 50
    		LastName VARCHAR(50) NOT NULL,     -- LastName is a variable character field with a maximum length of 50
    		HireDate DATE                      -- HireDate is a date field
		);

2. Adding a new column Email to the Employees table.
Ans: 
	ALTER TABLE Employees
	ADD COLUMN Email VARCHAR(100);

3.  Deleting the Employees table.
Ans:
	DROP TABLE Employees;

4.  Renaming the Employees table to Staff.
Ans:
	ALTER TABLE Employees
	RENAME TO Staff;

5. First, add the Age column, then apply a domain constraint.
Ans:
	ALTER TABLE Employees
	ADD COLUMN Age INT CHECK (Age >= 0);

6. The Customers table will include a primary key and some additional customer details.
Ans:
	CREATE TABLE Customers (
    		CustomerID SERIAL PRIMARY KEY,    -- Auto-incrementing primary key
    		FirstName VARCHAR(50) NOT NULL,   -- Customer's first name
    		LastName VARCHAR(50) NOT NULL,    -- Customer's last name
    		Email VARCHAR(100) UNIQUE NOT NULL,  -- Customer's email, must be unique
    		CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP  -- Timestamp for when the record was created
		);

7. The Orders table will include a foreign key that references the Customers table.
Ans:
	CREATE TABLE Orders (
		OrderID SERIAL PRIMARY KEY,       -- Auto-incrementing primary key for orders
		CustomerID INT NOT NULL,          -- Foreign key to reference the customer
		OrderDate DATE NOT NULL,          -- Date of the order
		TotalAmount DECIMAL(10, 2) NOT NULL,  -- Total amount for the order, with 2 decimal places
		FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)  -- Referential integrity constraint
	);

8. Referential Integrity: Enforcing a foreign key relationship between the Orders table and the Customers table.
Ans:
	ALTER TABLE Orders
		ADD CONSTRAINT fk_Customer
		FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID);

9. Drop database
Ans:
	Drop Database db_bct031;




