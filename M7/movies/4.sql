SELECT title from movies WHERE movies.id IN(SELECT movie_id from ratings WHERE ratings.rating = 10.0);

