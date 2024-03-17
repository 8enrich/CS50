SELECT name FROM people WHERE people.id IN(SELECT DISTINCT(person_id) from stars JOIN movies ON stars.movie_id = movies.id WHERE movies.year = 2004) ORDER BY people.birth;

