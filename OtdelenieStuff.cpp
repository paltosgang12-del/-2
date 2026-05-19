#include "OtdelenieStuff.h"

Otdel::Otdel() {
    nomer = -1;
    x1 = 0;
    y1 = 0;
    nazvanie = "";
}

Otdel::Otdel(int id, double x, double y, std::string name) {
    nomer = id;
    x1 = x;
    y1 = y;
    nazvanie = name;
}

int Otdel::getId() { return nomer; }
double Otdel::getX() { return x1; }
double Otdel::getY() { return y1; }
std::string Otdel::getName() { return nazvanie; }

void Otdel::polozhit(Posylka p) {
    spisok.push_back(p);
}

bool Otdel::zabrat(std::string tr) {
    for (int i = 0; i < spisok.size(); i++) {
        if (spisok[i].getTr() == tr) {
            spisok.erase(spisok.begin() + i);
            return true;
        }
    }
    return false;
}

Posylka* Otdel::nayti(std::string tr) {
    for (int i = 0; i < spisok.size(); i++) {
        if (spisok[i].getTr() == tr) {
            return &spisok[i];
        }
    }
    return nullptr;
}

std::vector<Posylka> Otdel::vse() {
    return spisok;
}

void Otdel::ochistit() {
    spisok.clear();
}
