-- task 1
select title, (rental_rate*0.5)+(length*0.1)+(replacement_cost*0.2) as rating 
from film 
order by rating DESC limit 3;

-- task 2
select (c.first_name || ' ' || c.last_name) as name, sum(p.amount) as total_spent
from customer c
inner join payment p on c.customer_id = p.customer_id
group by name;

-- *task 3

-- *task 4
select * cntry.country
from country cntry
left join city ct on cntr.country_id = ct.country_id
left join address addr on addr.city_id = ct.city_id
left join customer cust on cust.address_id = addr.address_id
where count()


-- task 5
create or replace procedure update_customer_email(IN v_cid INT, IN newMail text)
language plpgsql
as $$
declare
begin
    update customer
    set email = newMail
    where customer_id = v_cid;
end;
$$;
call update_customer_email(1, 'abcd');

-- task 6
do $$
declare 
    r   record;
begin
    for r  in   select * 
                from customer c
                inner join rental ren on c.customer_id = ren.customer_id 
    loop

        if r.activebool = true and r.return_date is NULL then
            raise notice 'cid % has active rentals', r.customer_id;
        else
            raise notice 'cid % does not have active rentals', r.customer_id;
        end if;

    end loop;
end $$
language plpgsql;


-- task 7
do $$
begin  
    perform title
    from film
    where rental_rate > 28.0;
end $$
language plpgsql;

-- task 8
do $$
declare 
    start_date      date := '2025-01-27 21:04:51.388625';
    r               record;
begin  
    for r in    select c.customer_id, sum(p.amount) as total_spent
                from customer c
                inner join payment p on c.customer_id = p.customer_id
                where p.payment_date > start_date AND p.payment_date < NOW()
                group by c.customer_id
    loop
        raise notice 'cid: %, total: %', r.customer_id, r.total_spent;
    end loop;
end $$
language plpgsql;

-- task 9
CREATE OR REPLACE FUNCTION didnt_rent(IN ndays INT)
RETURNS TABLE (
    customer_id INT,
    latest_rental DATE
)
AS $$
BEGIN
    RETURN QUERY
    SELECT r.customer_id,
           MAX(r.rental_date)::date AS latest_rental
    FROM rental r
    GROUP BY r.customer_id
    HAVING MAX(r.rental_date) < NOW() - INTERVAL '1 day' * ndays
    ORDER BY MAX(r.rental_date) DESC;
END $$
LANGUAGE plpgsql;
select * from didnt_rent(5);

-- task 10
as



