-- Write a SQL query that lists the names of the songs that feature other artists

-- Surround the assigned entry by '%" signs on both edges
-- to get at every value matching the one placed between these placeholders
SELECT name FROM songs WHERE name LIKE '%feat.%';