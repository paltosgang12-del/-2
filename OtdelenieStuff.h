#ifndef OTDELENIE_STUFF_H
#define OTDELENIE_STUFF_H

#include <string>
#include <vector>
#include "PochtaThings.h"

class Otdel {
public:
    Otdel();
    Otdel(int id, double x, double y, std::string name);

    int getId();
    double getX();
    double getY();
    std::string getName();

    void polozhit(Posylka p);
    bool zabrat(std::string tr);
    Posylka* nayti(std::string tr);
    std::vector<Posylka> vse();
    void ochistit();

private:
    int nomer;
    double x1;
    double y1;
    std::string nazvanie;
    std::vector<Posylka> spisok;
};

#endif
