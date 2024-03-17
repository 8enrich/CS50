SELECT name from people WHERE people.id IN(SELECT person_id from stars JOIN movies ON stars.movie_id = movies.id WHERE movies.title = "Toy Story");
