#include <iostream>
#include "movies.h"

int main(){
    Movies my_movies;
    // my_movies.display();
    my_movies.add_movie("Fight Club", "Pg-13", 2);
    my_movies.add_movie("Midnight in Paris", "Pg", 1);
    my_movies.add_movie("Star Wars", "Pg", 0);
    // my_movies.display();
    my_movies.add_movie("Midnight in Paris", "Pg", 2);
    my_movies.add_movie("Forest Gamp", "Cool", 3);
    my_movies.display();
    my_movies.increment_watched("Fight Club");
    my_movies.increment_watched("Star Wars");
    my_movies.increment_watched("Zebra");
    my_movies.display();
}