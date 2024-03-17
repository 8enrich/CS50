SELECT AVG(rating) from ratings WHERE ratings.movie_id IN(SELECT id from movies WHERE movies.year = 2012);
