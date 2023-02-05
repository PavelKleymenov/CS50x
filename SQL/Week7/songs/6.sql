-- Write a SQL query that lists the names of songs that are by Post Malone

-- Access data from both of the tables by taking advantage of the 'relation' concept 
SELECT DISTINCT(name) FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = 'Post Malone');