SELECT movies.title, ratings.rating
FROM movies, ratings
WHERE ratings.movie_id = movies.id AND movies.year = 2010
ORDER BY ratings.rating DESC, movies.title ASC;
