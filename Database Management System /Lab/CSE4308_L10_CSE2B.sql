--Task 1
DO $$
DECLARE
    v_salary   NUMERIC;
    v_name     TEXT;
    v_pension  NUMERIC;
BEGIN
    SELECT first_name || ' ' || last_name, salary
    INTO v_name, v_salary
    FROM employees
    WHERE employee_id = 10;

    v_pension := v_salary * 0.65;

    RAISE NOTICE 'Employee % will receive a pension of %',
        v_name, v_pension;
END $$;

--Task 2
DO $$
DECLARE
    v_name   TEXT;
    v_salary NUMERIC;
BEGIN
    SELECT first_name || ' ' || last_name, salary
    INTO v_name, v_salary
    FROM employees
    ORDER BY salary DESC
    LIMIT 1;

    RAISE NOTICE 'Highest paid employee: % with salary %',
        v_name, v_salary;
END $$;

--Task 3
DO $$
DECLARE
    rec RECORD;
    v_building TEXT;
BEGIN
    FOR rec IN
        SELECT first_name || ' ' || last_name AS full_name,
               department
        FROM employees
    LOOP
        IF rec.department IN ('IT', 'Operations') THEN
            v_building := 'Building A';
        ELSIF rec.department IN ('HR', 'Management') THEN
            v_building := 'Building B';
        ELSE
            v_building := 'Annex C';
        END IF;

        RAISE NOTICE '% from % is assigned to %',
            rec.full_name, rec.department, v_building;
    END LOOP;
END $$;

--Task 4
DO $$
DECLARE
    counter INT := 1;
BEGIN
    WHILE counter <= 10 LOOP
        RAISE NOTICE '7 x % = %',
            counter, 7 * counter;
        counter := counter + 1;
    END LOOP;
END $$;
