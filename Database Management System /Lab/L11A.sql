--- task1
CREATE OR REPLACE FUNCTION project_future_revenue(p_months_ahead IN INT, A OUT NUMERIC)
LANGUAGE plpgsql
AS $$
DECLARE
    growth      NUMERIC;
    revPrev     NUMERIC;
    revPrevPrev NUMERIC;
BEGIN
    SELECT SUM(total_value)
    INTO revPrev
    FROM orders
    WHERE order_date > CURRENT_DATE - INTERVAL '30 days';

    SELECT SUM(total_value)
    INTO revPrevPrev
    FROM orders
    WHERE order_date > CURRENT_DATE - INTERVAL '60 days';

    revPrevPrev := revPrevPrev - revPrev;

    IF revPrevPrev = 0 THEN 
        growth := 0;
        RAISE NOTICE 'Division by zero';
    ELSE
            growth := (revPrev/revPrevPrev);
    END IF;
    

    A := revPrev * power((1 + growth), p_months_ahead);
END;
$$;

SELECT project_future_revenue(5);


--- task 2
CREATE OR REPLACE PROCEDURE apply_bulk_discounts(p_min_qty IN INT, p_discount_pct IN INT)
LANGUAGE plpgsql
AS $$
DECLARE
    r RECORD;
    v_quantity INT;
BEGIN 
    FOR r IN SELECT * FROM orders 
    WHERE status = 'PENDING' LOOP    
        SELECT quantity 
        INTO v_quantity 
        FROM order_items 
        WHERE order_id = r.order_id;

            IF v_quantity >= p_min_qty THEN   
                UPDATE order_items
                SET 
                    unit_price = unit_price * (100 - p_discount_pct) / 100.0
                WHERE order_id = r.order_id;
                
                RAISE NOTICE 'Order % needs recalculation', r.order_id;

                UPDATE orders
                SET total_value = v_quantity * (SELECT unit_price 
                                               FROM order_items 
                                               WHERE order_id = r.order_id)
                WHERE order_id = r.order_id;

            END IF;
    END LOOP;
END;
$$;

CALL apply_bulk_discounts(3, 20);



------ task 3
CREATE OR REPLACE PROCEDURE anonymize_inactive_customers (p_anonymized_count OUT INT)
LANGUAGE plpgsql
AS $$
DECLARE 
    r       RECORD;
BEGIN
    p_anonymized_count := 0;
    FOR r IN SELECT DISTINCT ON (customer_id) customer_id, order_date, order_id 
    FROM orders 
    ORDER BY customer_id, order_date DESC LOOP
        IF CURRENT_DATE > r.order_date + INTERVAL '720 days' THEN
            UPDATE customers 
            SET 
                name = 'ANONYMIZED',
                region = 'UNKNOWN',
                loyalty_tier = 'Bronze'
            WHERE customer_id = r.customer_id;
            p_anonymized_count := p_anonymized_count + 1;
        END IF;
    END LOOP;
END;
$$;

CALL anonymize_inactive_customers(NULL);
        


                    














