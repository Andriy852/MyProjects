#ifndef _PRINTABLE_H_
#define _PRINTABLE_H_
#include <iostream>
class Printable{
    friend std::ostream &operator<<(std::ostream &, const Printable &);
public:
    virtual ~Printable(){};
    virtual void print(std::ostream &) const = 0;
};

#endif