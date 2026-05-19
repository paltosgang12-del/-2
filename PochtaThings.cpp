#include "PochtaThings.h"

Posylka::Posylka() {
    treker = "";
    otpravitel = "";
    poluchatel = "";
    ves = 0;
    izOtdela = -1;
    vOtdel = -1;
    seychasGde = -1;
    ostalosDney = 0;
}

Posylka::Posylka(std::string tr, std::string otpr, std::string pol,
               double ves, int otkuda, int kuda) {
    treker = tr;
    otpravitel = otpr;
    poluchatel = pol;
    this->ves = ves;
    izOtdela = otkuda;
    vOtdel = kuda;
    seychasGde = otkuda;
    ostalosDney = 0;
}

std::string Posylka::getTr() { return treker; }
std::string Posylka::getOtpr() { return otpravitel; }
std::string Posylka::getPol() { return poluchatel; }
double Posylka::getVes() { return ves; }
int Posylka::getOtkuda() { return izOtdela; }
int Posylka::getKuda() { return vOtdel; }
int Posylka::getGde() { return seychasGde; }
int Posylka::getDney() { return ostalosDney; }

void Posylka::setGde(int id) { seychasGde = id; }
void Posylka::setDney(int dn) { ostalosDney = dn; }

void Posylka::proshloDney(int dn) {
    if (ostalosDney > 0) {
        ostalosDney = ostalosDney - dn;
        if (ostalosDney <= 0) {
            ostalosDney = 0;
            seychasGde = vOtdel;
        }
    }
}
