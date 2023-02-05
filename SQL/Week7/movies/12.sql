-- Write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred

SELECT movies.title FROM people
JOIN stars ON people.id = person_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = "Johnny Depp" AND movies.title IN(
SELECT movies.title FROM people
JOIN stars ON people.id = person_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = "Helena Bonham Carter");