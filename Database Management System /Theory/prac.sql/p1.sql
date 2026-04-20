-- 1
create or replace function getTotalPaid(sid INT)
returns INT
language plpgsql
as $$
declare
    v_sum INT;
begin
    select coalesce(sum(amount), 0)
    into v_sum
    from payment
    where student_id = sid;
    return v_sum;
end;
$$;

-- 2
create or replace function getTotalEnrolled(sid INT)
returns INT
language plpgsql
as $$
declare 
    v_count INT;
begin
    select count(*)
    into v_count
    from enrollment
    where student_id = sid;
    return v_count;
end;
$$;

-- 3
create or replace function get_letter_grade(p_marks NUMERIC)
returns CHAR
language plpgsql
as $$
declare 
    grade char;
begin
    IF p_marks >= 80 THEN
    grade := 'A';
    ELSIF p_marks >= 70 THEN
        grade := 'B';
    ELSIF p_marks >= 60 THEN
        grade := 'C';
    ELSIF p_marks >= 50 THEN
        grade := 'D';
    ELSE
        grade := 'F';
    END IF;

    return grade;
end;
$$;  

-- 4
create or replace function is_scholarship_eligible(p_student_id INT)
returns boolean
language plpgsql
as $$
declare
    v_cgpa NUMERIC(3,2);
begin
    select cgpa
    into v_cgpa
    from student
    where student_id = p_student_id;

    if v_cgpa >= 3.75 then return true;
    else                  return false;
    end if;
end;
$$;

-- 5
create or replace function remaining_seats(p_course_id INT)
returns int
language plpgsql
as $$
declare
    currEnrollment INT;
    v_cap          INT;

begin
    select count(*)
    into currEnrollment
    from enrollment
    where course_id = p_course_id;

    select capacity
    into v_cap
    from course
    where course_id = p_course_id;

    return v_cap - currEnrollment;
end;
$$;

-- 6
create or replace function dept_avg_cgpa(p_dept_id INT)
returns float
language plpgsql
as $$
declare
    avg_cgpa float;
begin
    select avg(cgpa)
    into avg_cgpa
    from student
    where dept_id = p_dept_id
    return avg_cgpa;
end;
$$;

