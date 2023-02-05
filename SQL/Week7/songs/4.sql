-- Write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75

-- Use the 'AND' keyword which allow us to include the rows where all conditions evaluate to true
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;
