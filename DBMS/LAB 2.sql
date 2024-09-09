DML

Questions

1. Inserting new records into the Customers and Orders tables.
Ans:
    -- Inserting data into the Customers table
        INSERT INTO Customers (FirstName, LastName, Email)
        VALUES ('John', 'Doe', 'john.doe@example.com');

        INSERT INTO Customers (FirstName, LastName, Email)
        VALUES ('Jane', 'Smith', 'jane.smith@example.com');

        -- Inserting data into the Orders table
        -- Note: We assume CustomerID 1 and 2 exist in the Customers table.
        INSERT INTO Orders (CustomerID, OrderDate, TotalAmount)
        VALUES (1, '2024-08-13', 150.75);

        INSERT INTO Orders (CustomerID, OrderDate, TotalAmount)
        VALUES (2, '2024-08-14', 200.00);

2. Updating customer email addresses and order total amounts.
Ans:
    -- Updating a customer's email address
        UPDATE Customers
        SET Email = 'john.newemail@example.com'
        WHERE CustomerID = 1;

        -- Updating the total amount of an order
        UPDATE Orders
        SET TotalAmount = 175.00
        WHERE OrderID = 1;

3. Deleting a customer and an order.
Ans:
        -- Deleting a customer
    DELETE FROM Customers
    WHERE CustomerID = 2;

    -- Deleting an order
    DELETE FROM Orders
    WHERE OrderID = 2;

4. Counting the number of customers and orders.
Ans:
    -- Count the number of customers
    SELECT COUNT(*) AS NumberOfCustomers
    FROM Customers;

    -- Count the number of orders
    SELECT COUNT(*) AS NumberOfOrders
    FROM Orders;

5. Summing up the total amount of all orders.
Ans:
    -- Sum of all order amounts
    SELECT SUM(TotalAmount) AS TotalSales
    FROM Orders;

6. Finding the average order amount.
Ans:
    -- Average order amount
    SELECT AVG(TotalAmount) AS AverageOrderAmount
    FROM Orders;

7. Finding the smallest order amount.
Ans:
    -- Minimum order amount
        SELECT MIN(TotalAmount) AS LowestOrderAmount
        FROM Orders;

8. Finding the largest order amount.
Ans:
    -- Maximum order amount
    SELECT MAX(TotalAmount) AS HighestOrderAmount
    FROM Orders;


#Group by
9. Calculating the total amount of orders for each customer.
Ans:
        -- Total order amount per customer
    SELECT Customers.FirstName, Customers.LastName, SUM(Orders.TotalAmount) AS TotalSpent
    FROM Orders
    JOIN Customers ON Orders.CustomerID = Customers.CustomerID
    GROUP BY Customers.CustomerID, Customers.FirstName, Customers.LastName;

#Having
10. Finding customers who have spent more than $200.

    -- Customers who spent more than $200
    SELECT Customers.FirstName, Customers.LastName, SUM(Orders.TotalAmount) AS TotalSpent
    FROM Orders
    JOIN Customers ON Orders.CustomerID = Customers.CustomerID
    GROUP BY Customers.CustomerID, Customers.FirstName, Customers.LastName
    HAVING SUM(Orders.TotalAmount) > 200;
