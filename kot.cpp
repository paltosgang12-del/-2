#include "kot.h"

Kot::Kot() {
    imya = "";
    poroda = "";
    vozrast = 0;
    cvet = "";
    primeti = "";
    naMeste = false;
}

Kot::Kot(std::string i, std::string p, int v, std::string c, std::string prim, bool m) {
    imya = i;
    poroda = p;
    vozrast = v;
    cvet = c;
    primeti = prim;
    naMeste = m;
}

std::string Kot::getImya() { return imya; }
std::string Kot::getPoroda() { return poroda; }
int Kot::getVozrast() { return vozrast; }
std::string Kot::getCvet() { return cvet; }
std::string Kot::getPrimeti() { return primeti; }
bool Kot::getNaMeste() { return naMeste; }

void Kot::setImya(std::string i) { imya = i; }
void Kot::setPoroda(std::string p) { poroda = p; }
void Kot::setVozrast(int v) { vozrast = v; }
void Kot::setCvet(std::string c) { cvet = c; }
void Kot::setPrimeti(std::string prim) { primeti = prim; }
void Kot::setNaMeste(bool m) { naMeste = m; }
