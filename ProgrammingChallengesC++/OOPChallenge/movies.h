#ifndef _MOVIES_H_ // if this symbol hasn't been defined
#define _MOVIES_H_ // than we define it here
#include <vector>
#include <string>
#include <algorithm>
#include "movie.h"
class Movies{
private:
    std::vector <Movie> *movies;
public:
    Movies(std::vector <Movie> movies = {});
    Movies(const Movies &);
    void add_movie(std::string name, std::string rating, int watched);
    void add_movie(Movie);
    void increment_watched(std::string name);
    void display();
};
#endif // else we go there