-- Task1
DO $$
DECLARE
    highest_salary  NUMERIC;
    highest_name    TEXT;
    lowest_name     TEXT;
    lowest_salary   NUMERIC;
BEGIN
    SELECT salary, first_name || ' ' || last_name
    INTO highest_salary, highest_name
    FROM employees
    ORDER BY salary DESC
    LIMIT 1;

    SELECT salary, first_name || ' ' || last_name
    INTO lowest_salary, lowest_name
    FROM employees
    ORDER BY salary ASC
    LIMIT 1;

    RAISE NOTICE 'highest salary employee: % lowest salary employee: %', highest_name, lowest_name;

    UPDATE employees
    SET salary =
        CASE
            WHEN salary = highest_salary THEN salary - 1000
            WHEN salary = lowest_salary THEN salary + 1000
            ELSE salary
        END;
END $$;

-- Task2
DO $$
DECLARE
    r       RECORD;
BEGIN
    FOR r in SELECT * from employees LIMIT 10 LOOP
        RAISE NOTICE 'Generated username: %', LOWER(SUBSTRING(r.first_name FROM 1 for 1) || r.last_name);
    END LOOP;
END $$;

-- Task3
DO $$
DECLARE
    val     INT := 1;
    i       INT;
BEGIN
    FOR i in 1..6 LOOP
        val = val * i;
    END LOOP;
    RAISE NOTICE '6! = %', val;
END $$;

-- Task4
DO $$
DECLARE
    id1     int := -1;
    id2     int := -1;
    id3     int := -1;
    r       RECORD;
BEGIN
    FOR r in SELECT * from employees LOOP
        IF r.department = 'IT' THEN
            IF id1 = -1 THEN
                id1 := r.employee_id;
            ELSIF id2 = -1 THEN
                id2 := r.employee_id;
            ELSIF id3 = -1 THEN
                id3 := r.employee_id;
            ELSE EXIT;
            END IF;
        END IF;
    END LOOP;

    UPDATE employees
    SET department =
        CASE
            WHEN employee_id = id1 OR employee_id = id2 OR employee_id = id3 THEN
                'CyberSec'
            ELSE department
        END;
END $$;









