#include "movies.h"
#include <iostream>

Movies::Movies(std::vector <Movie> movies_vec){
    movies = new std::vector <Movie>;
    *movies = movies_vec;
}

Movies::Movies(const Movies &source): Movies(*source.movies){};
void Movies::add_movie(std::string name, std::string rating, int watched){
    bool there{false};
    for (Movie &movie:*movies){
        if (movie.get_name()==name) there = true;
    }
    if (!there){
        Movie movie_to_add = Movie{name, rating, watched};
        (*movies).push_back(movie_to_add);
    }
    else{
        std::cout<<"The movie "<<name<<" is already in the list"<<std::endl;
    }
}

void Movies::add_movie(Movie movie_to_add){
    bool there{false};
    for (Movie &movie:*movies){
        if (movie.get_name()==movie_to_add.get_name()){there = true;}
    }
    if (!there){
        (*movies).push_back(movie_to_add);
    }
    else{
        std::cout<<"The movie "<<movie_to_add.get_name()<<" is already in the list"<<std::endl;
    }
}

void Movies::display(){
    if ((*movies).size()==0){
        std::cout<<"No movies in the list"<<std::endl;
    }
    for (Movie &movie:*movies){
        movie.display();
        std::cout<<"--------------------------------"<<std::endl;
    }
}

void Movies::increment_watched(std::string name){
    bool there{false};
    for (Movie &movie:*movies){
        if (movie.get_name()==name) {
            movie.increment_watched();
            there = true;
        }
    }
    if (!there) std::cout<<"ERROR - THE MOVIE "<<name<<" IS NOT IN THE LIST"<<std::endl;
}