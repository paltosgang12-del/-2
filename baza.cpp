#include "baza.h"
#include <fstream>
#include <iostream>
#include <string>
#include <limits>

void BazaKotov::zagruzit(const char* file, Kot** &massiv, int &kol) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cout << "Файл не найден, создаю новую базу\n";
        kol = 0;
        massiv = nullptr;
        return;
    }
    
    int count = 0;
    std::string line;
    while (std::getline(f, line)) {
        if (line.length() > 0) count++;
    }
    
    f.clear();
    f.seekg(0);
    
    massiv = new Kot*[count];
    kol = count;
    
    for (int i = 0; i < count; i++) {
        massiv[i] = new Kot();
        f >> (*massiv[i]);
    }
    f.close();
    std::cout << "Загружено " << kol << " котов\n";
}

void BazaKotov::sohranit(const char* file, Kot** massiv, int kol) {
    std::ofstream f(file);
    for (int i = 0; i < kol; i++) {
        f << (*massiv[i]) << "\n";
    }
    f.close();
    std::cout << "Сохранено " << kol << " записей\n";
}

void BazaKotov::menu() {
    std::cout << "\n===== КОТОКАФЕ =====\n";
    std::cout << "1. Показать всех\n";
    std::cout << "2. Найти кота\n";
    std::cout << "3. Добавить\n";
    std::cout << "4. Удалить\n";
    std::cout << "5. Редактировать\n";
    std::cout << "6. Сохранить и выйти\n";
    std::cout << "Выбери: ";
}

void BazaKotov::pokazat(Kot** massiv, int kol) {
    if (kol == 0) {
        std::cout << "Пусто\n";
        return;
    }
    std::cout << "\n--- Котики ---\n";
    for (int i = 0; i < kol; i++) {
        std::cout << i+1 << ". "
                  << "Имя: " << massiv[i]->getImya() << " | "
                  << "Порода: " << massiv[i]->getPoroda() << " | "
                  << "Возраст: " << massiv[i]->getVozrast() << " лет | "
                  << "Окрас: " << massiv[i]->getCvet() << " | "
                  << "Приметы: " << massiv[i]->getPrimeti() << " | ";
        if (massiv[i]->getNaMeste())
            std::cout << "на месте\n";
        else
            std::cout << "отдыхает\n";
    }
}

void BazaKotov::poisk(Kot** massiv, int kol) {
    if (kol == 0) {
        std::cout << "Нет котов\n";
        return;
    }
    
    std::cin.ignore(32767, '\n');
    std::string poImeni, poPorode;
    
    std::cout << "Имя (можно пусто): ";
    std::getline(std::cin, poImeni);
    std::cout << "Порода (можно пусто): ";
    std::getline(std::cin, poPorode);
    
    int nashli = 0;
    for (int i = 0; i < kol; i++) {
        bool sovpI = (poImeni.empty() || massiv[i]->getImya().find(poImeni) != std::string::npos);
        bool sovpP = (poPorode.empty() || massiv[i]->getPoroda().find(poPorode) != std::string::npos);
        
        if (sovpI && sovpP) {
            if (nashli == 0) std::cout << "\nНайдено:\n";
            std::cout << i+1 << ". " << massiv[i]->getImya() << " (" << massiv[i]->getPoroda() << ")\n";
            nashli++;
        }
    }
    if (nashli == 0) std::cout << "Ничего\n";
}

void BazaKotov::dobavit(Kot** &massiv, int &kol) {
    std::cin.ignore(32767, '\n');
    std::string i, p, c, prim;
    int v;
    char m;
    
    std::cout << "Кличка: "; std::getline(std::cin, i);
    std::cout << "Порода: "; std::getline(std::cin, p);
    std::cout << "Возраст: "; std::cin >> v; std::cin.ignore();
    std::cout << "Окрас: "; std::getline(std::cin, c);
    std::cout << "Приметы: "; std::getline(std::cin, prim);
    std::cout << "На месте? (y/n): "; std::cin >> m; std::cin.ignore();
    
    bool naM = (m == 'y' || m == 'Y');
    
    Kot** noviy = new Kot*[kol + 1];
    for (int j = 0; j < kol; j++) {
        noviy[j] = massiv[j];
    }
    noviy[kol] = new Kot(i, p, v, c, prim, naM);
    
    delete[] massiv;
    massiv = noviy;
    kol++;
    std::cout << "Добавлен!\n";
}

void BazaKotov::udalit(Kot** &massiv, int &kol) {
    if (kol == 0) {
        std::cout << "Нет котов\n";
        return;
    }
    
    pokazat(massiv, kol);
    std::cout << "Номер для удаления: ";
    int nom;
    std::cin >> nom;
    
    if (nom < 1 || nom > kol) {
        std::cout << "Не так\n";
        return;
    }
    
    delete massiv[nom-1];
    
    Kot** noviy = new Kot*[kol - 1];
    for (int i = 0, j = 0; i < kol; i++) {
        if (i != nom-1) {
            noviy[j] = massiv[i];
            j++;
        }
    }
    
    delete[] massiv;
    massiv = noviy;
    kol--;
    std::cout << "Удалил\n";
}

void BazaKotov::redakt(Kot** massiv, int kol) {
    if (kol == 0) {
        std::cout << "Некого\n";
        return;
    }
    
    pokazat(massiv, kol);
    std::cout << "Номер кота: ";
    int nom;
    std::cin >> nom;
    std::cin.ignore();
    
    if (nom < 1 || nom > kol) {
        std::cout << "Не то\n";
        return;
    }
    
    Kot* k = massiv[nom-1];
    std::string tmp;
    
    std::cout << "Новое имя (" << k->getImya() << "): ";
    std::getline(std::cin, tmp); if (!tmp.empty()) k->setImya(tmp);
    
    std::cout << "Новая порода (" << k->getPoroda() << "): ";
    std::getline(std::cin, tmp); if (!tmp.empty()) k->setPoroda(tmp);
    
    std::cout << "Новый возраст (" << k->getVozrast() << "): ";
    std::getline(std::cin, tmp); if (!tmp.empty()) k->setVozrast(std::stoi(tmp));
    
    std::cout << "Новый окрас (" << k->getCvet() << "): ";
    std::getline(std::cin, tmp); if (!tmp.empty()) k->setCvet(tmp);
    
    std::cout << "Новые приметы (" << k->getPrimeti() << "): ";
    std::getline(std::cin, tmp); if (!tmp.empty()) k->setPrimeti(tmp);
    
    std::cout << "На месте? (y/n, сейчас " << (k->getNaMeste() ? "да" : "нет") << "): ";
    char ch; std::cin >> ch; std::cin.ignore();
    if (ch == 'y' || ch == 'Y') k->setNaMeste(true);
    else if (ch == 'n' || ch == 'N') k->setNaMeste(false);
    
    std::cout << "Обновил\n";
}
