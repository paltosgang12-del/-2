#ifndef BAZA_H
#define BAZA_H

#include "kot.h"

namespace BazaKotov {
    void zagruzit(const char* file, Kot** &massiv, int &kol);
    void sohranit(const char* file, Kot** massiv, int kol);
    void pokazat(Kot** massiv, int kol);
    void poisk(Kot** massiv, int kol);
    void dobavit(Kot** &massiv, int &kol);
    void udalit(Kot** &massiv, int &kol);
    void redakt(Kot** massiv, int kol);
    void menu();
}

#endif
