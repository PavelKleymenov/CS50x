-- Write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year

SELECT name FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movie_id = movies.id
WHERE year = "2004" ORDER BY birth