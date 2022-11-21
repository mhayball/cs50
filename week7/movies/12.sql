SELECT movies.title
FROM movies, stars, people
WHERE movies.id = stars.movie_id AND stars.person_id = people.id AND people.name = "Helena Bonham Carter" AND stars.movie_id IN
    (SELECT stars.movie_id
    FROM stars, people
    WHERE stars.person_id = people.id AND people.name = "Johnny Depp");
