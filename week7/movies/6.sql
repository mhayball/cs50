SELECT AVG(ratings.rating)
FROM movies, ratings
WHERE ratings.movie_id = movies.id AND movies.year = 2012;
