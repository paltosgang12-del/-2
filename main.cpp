#include "baza.h"
#include "kot.h"
#include <iostream>

int main() {
    Kot** koty = nullptr;
    int skolko = 0;
    
    BazaKotov::zagruzit("koty.txt", koty, skolko);
    
    int vibor;
    do {
        BazaKotov::menu();
        std::cin >> vibor;
        
        switch (vibor) {
            case 1:
                BazaKotov::pokazat(koty, skolko);
                break;
            case 2:
                BazaKotov::poisk(koty, skolko);
                break;
            case 3:
                BazaKotov::dobavit(koty, skolko);
                break;
            case 4:
                BazaKotov::udalit(koty, skolko);
                break;
            case 5:
                BazaKotov::redakt(koty, skolko);
                break;
            case 6:
                BazaKotov::sohranit("koty.txt", koty, skolko);
                std::cout << "Пока!\n";
                break;
            default:
                std::cout << "Не то\n";
        }
    } while (vibor != 6);
    
    for (int i = 0; i < skolko; i++) {
        delete koty[i];
    }
    delete[] koty;
    
    return 0;
}
