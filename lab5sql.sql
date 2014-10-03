use okilo;
select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 1: Names and cities of customers who have a loan at Perryridge branch.' as '';
SELECT customer.customer_name, customer.customer_city
FROM customer, borrower, loan
WHERE loan.branch_name = 'Perryridge' AND loan.loan_number = borrower.loan_number AND customer.customer_name = borrower.customer_name;

select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 2: Names of customers on streets with names ending in "Hill".' as '';
SELECT customer.customer_name
FROM customer
WHERE customer.customer_street like '%Hill';

select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 3: Names of customers with accounts at a branch where Hayes has.' as '';
SELECT distinct depositor.customer_name
FROM depositor,account
WHERE depositor.account_number = account.account_number AND account.branch_name in (SELECT account.branch_name
FROM account, depositor
WHERE depositor.customer_name = 'Hayes' AND depositor.account_number = account.account_number);

select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 4: Names of branches with average balance above 700.' as '';
SELECT branch_name, avg (balance)
FROM account
group by branch_name
having avg(balance) > 700;

select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 5: Loan data, ordered by decreasing amounts, then increasing loan numbers.' as '';
SELECT * from loan
order by amount desc;

SELECT * from loan
order by loan_number asc;


