-- Write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred

SELECT DISTINCT(name) FROM people
JOIN stars ON people.id = person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN(
SELECT DISTINCT(movies.title) FROM people
JOIN stars ON people.id = person_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = "Kevin Bacon" AND birth = "1958")
AND name != "Kevin Bacon";