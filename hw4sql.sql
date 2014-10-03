use okilo;
select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 1: Names and ages of each employee who works in the Hardware department.' as '';
SELECT ename, age
from emp, works
where emp.eid = works.eid AND works.did = (select dept.did
from dept
where dept.dname = 'Hardware');


select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 2:  DID and the number of employees that work in each department with more than 20 employees.' as '';
SELECT works.did, count(distinct works.eid)
from works
group by did
having count(distinct works.eid) > 20;


select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 3: Name of each employee whose salary exceeds the average salary of all employees.' as '';
SELECT emp.ename, salary
from emp
where salary > (select avg(salary)
from emp)
group by emp.eid;


select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 4: Manager IDs of managers who manage only departments with budgets greater than $1 million.' as '';
SELECT dept.managerid
from dept
where dept.budget > 1000000;




select '- - - - - - - - - - - - - - - - - - - - - - - - - - - -'
from dual;
select 'Query 5: Information of employees who work in the ‘Operations’ departments with the output should be ordered by ename' as '';
SELECT emp.eid, ename, age, salary
from emp, works
where emp.eid = works.eid AND works.did = (select dept.did
from dept
where dept.dname = 'Operations')
order by ename asc;