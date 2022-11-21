SELECT DISTINCT(people.name)
FROM people, movies, stars
WHERE people.id = stars.person_id AND stars.movie_id = movies.id AND movies.year = 2004
ORDER BY people.birth;
