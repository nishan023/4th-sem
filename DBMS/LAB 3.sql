Consider the following relational schema
    Account (account_number{primary-key}, branch_name, balance)
    Branch (branch_name{primary-key}, branch_city, assets)
    Customer (customer_name{primary-key}, customer_street, customer_city)
    Loan (loan_number{primary-key} branch_name, amount)
    Depositor (customer_name, account_number)
    Borrower ( customer_name, loan_number)
1. Create the tables as mentioned in the above schema. Show the use of primary key and foreign key, unique key and not null constraints

Ans:
    create database db_bct031;

    use db_bct031;

    create table Branch (branch_name varchar(20) not null primary key,
                     branch_city varchar(20),
                     assets varchar(20));
                     
    create table Account_ (account_number int not null unique,
    					   branch_name varchar(20),
                           foreign key (branch_name) references Branch(branch_name), 
                           balance int);

    create table Customer (customer_name varchar(30) not null primary key, 
                           customer_street varchar(20),
                           customer_city varchar(20));

    create table Loan (loan_number int not null primary key,
    				   branch_name varchar(20),
                       foreign key (branch_name) references Branch (branch_name), 
                       amount int);

    create table Depositor (customer_name varchar(30),
                           foreign key (customer_name) references Customer(customer_name),
                           account_number int,
                           foreign key (account_number) references Account_(account_number));

    create table Borrower (customer_name varchar(30),
                           foreign key (customer_name) references Customer(customer_name), 
                           loan_number int,
                           foreign key (loan_number) references Loan(loan_number));

###################################################################################################################################################




2. Insert at least five records in each relations
Ans:
    INSERT INTO Branch(branch_name, branch_city, assets)
VALUES
    ('Thapathali', 'Kathmandu', 'Car'),
    ('Pulchowk', 'Lalitpur', 'House'),
    ('Baneshor', 'Kathmandu', 'Land'),
    ('Tirpureshor', 'Kathmandu', 'Car'),
    ('Gongabu', 'Kathmandu', 'House');

INSERT INTO Account_(account_number, branch_name, balance)
VALUES 
    (6002, 'Gongabu', 90000),
    (6003, 'Tirpureshor', 500000),
    (6004, 'Baneshor', 200000),
    (6005, 'Pulchowk', 40000),
    (6006, 'Thapathali', 80000);

INSERT INTO Customer(customer_name, customer_street, customer_city)
VALUES 
    ('Nathen', 'Gongabu', 'Kathmandu'),
    ('John', 'Baneshor', 'Kathmandu'),
    ('Ella', 'Pulchoek', 'Lalitpur'),
    ('Adam', 'Samakushi', 'Kathmandu'),
    ('Samanta', 'Lagankhel', 'Kathmandu');

INSERT INTO Loan(loan_number, branch_name, amount)
VALUES 
    (1999, 'Gongabu', 99000),
    (2000, 'Baneshor', 160000),
    (2001, 'Pulchowk', 200000),
    (2002, 'Thapathali', 90000),
    (2003, 'Tirpureshor', 60000);

INSERT INTO Depositor(customer_name, account_number)
VALUES 
    ('Nathen', 6002),
    ('Adam', 6006),
    ('Ella', 6003),
    ('John', 6004),
    ('Samanta', 6005);

INSERT INTO Borrower(customer_name, loan_number)
VALUES 
    ('Nathen', 1999),
    ('Adam', 2000),
    ('Ella', 2001),
    ('John', 2002),
    ('Samanta', 2003);


    SELECT * FROM Branch;
    SELECT * FROM Account_;
    SELECT * FROM Customer;
    SELECT * FROM Loan;
    SELECT * FROM Depositor;
    SELECT * FROM Borrower;


###################################################################################################################################################


3. Write an SQL query to list the names of all depositors along with their account number and balance
Ans:
    SELECT 
        D.customer_name,     -- Selecting the customer name from Depositor table
        A.account_number,    -- Selecting the account number from Account_ table
        A.balance            -- Selecting the balance from Account_ table
    FROM 
        Depositor AS D        -- Aliasing Depositor table as D
    JOIN 
        Account_ AS A         -- Aliasing Account_ table as A
    ON 
        D.account_number = A.account_number;  -- Joining condition on account_number

###################################################################################################################################################

4. Write an SQL query to find the names of all customers who have a loan of over 150,000
Ans:
    SELECT 
        Borrower.customer_name
    FROM 
        Loan
    JOIN 
        Borrower
    ON 
        Loan.loan_number = Borrower.loan_number
    WHERE 
        Loan.amount >= 150000;

###################################################################################################################################################

5. Write a query in SQL to increase all accounts with balances over 100,000 by 6% and all other accounts by 5%
Ans:
    set sql_safe_updates=0;

    update Account_
    set balance = balance*1.06
    where balance>=100000;

    update Account_
    set balance=balance*1.05
    where balance<100000;

    set sql_safe_updates=1;

    SELECT * FROM Account_;

###################################################################################################################################################

6. Delete foreign key constraint that is used on ‘account_number’ field of the table ‘Depositor’
Ans:
    i)Find the Constraint Name:
        SELECT
            constraint_name
        FROM
            information_schema.key_column_usage
        WHERE
            table_name = 'Depositor'
            AND column_name = 'account_number';
    
    ii)Drop the Constraint:
        ALTER TABLE Depositor
        DROP CONSTRAINT fk_depositor_account_number;
        

7. Add a foreign key constraint ‘fk_depositor_1’ on field ‘account_number’of the table ‘Depositor’

Ans:
    Alter Table Depositor
    Add constraint fk_depositor_1 
    foreign key (account_number) references Account_(account_number);