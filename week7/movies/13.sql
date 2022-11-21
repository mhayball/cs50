SELECT DISTINCT(people.name)
FROM stars, people
WHERE stars.person_id = people.id AND stars.movie_id IN
    (SELECT stars.movie_ID
    FROM stars
    WHERE stars.person_id =
        (SELECT people.id
        FROM people
        WHERE people.name = "Kevin Bacon" AND birth = 1958))
    AND people.name <> "Kevin Bacon";
