-- Write a SQL query to list the titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in, starting with the highest rated

SELECT movies.title FROM people
JOIN stars ON people.id = person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;