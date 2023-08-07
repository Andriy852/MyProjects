#ifndef _MOVIE_H_ // if this symbol hasn't been defined
#define _MOVIE_H_ // than we define it here
#include <string>

class Movie{
private:
    std::string name;
    std::string rating;
    int watched;
public:
    Movie(std::string name="None", std::string rating="None", int watched = 0);
    Movie(const Movie &);
    void display();
    void set_name(std::string name){this->name = name;}
    void set_rating(std::string rating_val){rating = rating_val;}
    std::string get_name() const{return name;}
    std::string get_rating() const{return rating;}
    void increment_watched(){watched++;}

};

#endif // else we go there