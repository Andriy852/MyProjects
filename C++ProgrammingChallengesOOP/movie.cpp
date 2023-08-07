#include "movie.h"
#include <iostream>

Movie::Movie(std::string name, std::string rating, int watched):
    name{name}, rating{rating}, watched{watched}{};
Movie::Movie(const Movie &source):name{source.name}, rating{source.rating},
watched{source.watched}{};

void Movie::display(){
    std::cout<<name<<"    "<<rating<<"    "<<watched<<std::endl;
}