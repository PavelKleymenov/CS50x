-- Write a SQL query to list the names of all songs in increasing order of tempo

-- We don't actually have to put 'ASC' at the end of the query
-- It's present though, only for visual purposes
SELECT name FROM songs ORDER BY tempo ASC;