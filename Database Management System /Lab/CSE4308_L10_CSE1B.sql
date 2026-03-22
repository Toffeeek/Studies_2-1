-- Task1
DO $$
DECLARE
    r       int;
BEGIN
    FOR r IN 1..10 LOOP
        INSERT INTO employees (first_name, last_name, salary, department)
        VALUES('User', r::TEXT, r*1000, 'Testing');
    END LOOP;
END $$;

--Task2
DO $$
DECLARE
    counter     int := 0;
    r           RECORD;
BEGIN
    FOR r in SELECT * FROM employees LOOP
        counter = counter + 1;
    END LOOP;
    RAISE NOTICE 'Manual Count: %', counter;
END $$;

--Task3
DO $$
DECLARE
    r                   RECORD;
BEGIN
    FOR r in SELECT * FROM employees LOOP
        UPDATE employees
        SET salary = ROUND(salary, -2)
        WHERE employee_id = r.employee_id;
        RAISE NOTICE 'Rounded salary for % % to %', r.first_name, r.last_name, r.salary;
    END LOOP;
END $$;

--Task4
DO $$
DECLARE
    highest_salary  NUMERIC := -1e10;
    lowest_salary   NUMERIC:= 1e10;
    r               RECORD;
BEGIN
    SELECT salary
    INTO highest_salary
    FROM employees
    ORDER BY salary DESC
    LIMIT 1;

    SELECT salary
    INTO lowest_salary
    FROM employees
    ORDER BY salary ASC
    LIMIT 1;

    --RAISE NOTICE 'highest salary: %\nlowest salary: %', highest_salary, lowest_salary;

    UPDATE employees
    SET salary =
        CASE
            WHEN salary = highest_salary THEN salary - 1000
            WHEN salary = lowest_salary THEN salary + 1000
            ELSE salary
        END;
END $$;













