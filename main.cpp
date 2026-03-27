#include "baza.h"
#include <iostream>
#include <string>

void pokazatMenu() {
    std::cout << "\n===== КОТОКАФЕ =====\n";
    std::cout << "1. Показать всех котов\n";
    std::cout << "2. Найти кота\n";
    std::cout << "3. Добавить кота\n";
    std::cout << "4. Удалить кота\n";
    std::cout << "5. Редактировать кота\n";
    std::cout << "6. Сохранить и выйти\n";
    std::cout << "Выбери: ";
}

int main(int argc, char* argv[]) {
    std::string imyaFaila = "koty.txt";
    
    if (argc > 1) {
        imyaFaila = argv[1];
        std::cout << "Использую файл: " << imyaFaila << "\n";
    }
    
    BazaKotov baza(imyaFaila);
    baza.zagruzit();
    
    int vibor;
    do {
        pokazatMenu();
        vibor = BazaKotov::vvodCisla("", 1, 6);
        
        switch (vibor) {
            case 1:
                baza.pokazat();
                break;
            case 2:
                baza.poisk();
                break;
            case 3:
                baza.dobavit();
                break;
            case 4:
                baza.udalit();
                break;
            case 5:
                baza.redakt();
                break;
            case 6:
                baza.sohranit();
                std::cout << "До встречи\n";
                break;
        }
    } while (vibor != 6);
    
    return 0;
}
