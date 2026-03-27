#include "baza.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

BazaKotov::BazaKotov()
    : m_koty(nullptr), m_kolichestvo(0), m_imyaFaila("koty.txt") {}

BazaKotov::BazaKotov(const std::string& imyaFaila)
    : m_koty(nullptr), m_kolichestvo(0), m_imyaFaila(imyaFaila) {}

BazaKotov::~BazaKotov() {
    for (int i = 0; i < m_kolichestvo; i++) {
        delete m_koty[i];
    }
    delete[] m_koty;
}

void BazaKotov::udvoitMassiv() {
    Kot** noviy = new Kot*[m_kolichestvo + 1];
    for (int i = 0; i < m_kolichestvo; i++) {
        noviy[i] = m_koty[i];
    }
    delete[] m_koty;
    m_koty = noviy;
}

void BazaKotov::umenshitMassiv(int index) {
    Kot** noviy = new Kot*[m_kolichestvo - 1];
    for (int i = 0, j = 0; i < m_kolichestvo; i++) {
        if (i != index) {
            noviy[j++] = m_koty[i];
        }
    }
    delete[] m_koty;
    m_koty = noviy;
}

bool BazaKotov::zagruzit() {
    std::ifstream f(m_imyaFaila);
    if (!f.is_open()) {
        std::cout << "Файл " << m_imyaFaila << " не найден, создаю новую базу\n";
        return false;
    }
    
    int count = 0;
    std::string line;
    while (std::getline(f, line)) {
        if (line.length() > 0) count++;
    }
    
    f.clear();
    f.seekg(0);
    
    m_koty = new Kot*[count];
    m_kolichestvo = count;
    
    for (int i = 0; i < count; i++) {
        m_koty[i] = new Kot();
        f >> (*m_koty[i]);
    }
    f.close();
    std::cout << "Загружено " << m_kolichestvo << " котов из " << m_imyaFaila << "\n";
    return true;
}

bool BazaKotov::sohranit() const {
    std::ofstream f(m_imyaFaila);
    if (!f.is_open()) {
        std::cout << "Ошибка сохранения в файл " << m_imyaFaila << "\n";
        return false;
    }
    for (int i = 0; i < m_kolichestvo; i++) {
        f << (*m_koty[i]) << "\n";
    }
    f.close();
    std::cout << "Сохранено " << m_kolichestvo << " записей в " << m_imyaFaila << "\n";
    return true;
}

void BazaKotov::sohranitKak(const std::string& novoeImya) {
    m_imyaFaila = novoeImya;
    sohranit();
}

void BazaKotov::pokazat() const {
    if (m_kolichestvo == 0) {
        std::cout << "База пуста\n";
        return;
    }
    std::cout << "\n=== Коты в котокафе ===\n";
    for (int i = 0; i < m_kolichestvo; i++) {
        std::cout << i + 1 << ". "
                  << "Имя: " << m_koty[i]->getImya() << " | "
                  << "Порода: " << m_koty[i]->getPoroda() << " | "
                  << "Возраст: " << m_koty[i]->getVozrast() << " лет | "
                  << "Окрас: " << m_koty[i]->getCvet() << " | "
                  << "Приметы: " << m_koty[i]->getPrimeti() << " | "
                  << (m_koty[i]->getNaMeste() ? "на месте" : "отдыхает") << "\n";
    }
}

void BazaKotov::poisk() const {
    if (m_kolichestvo == 0) {
        std::cout << "Нет котов для поиска\n";
        return;
    }
    
    std::string poImeni = vvodStroki("Имя для поиска (можно пусто): ");
    std::string poPorode = vvodStroki("Порода для поиска (можно пусто): ");
    
    int nashli = 0;
    for (int i = 0; i < m_kolichestvo; i++) {
        bool sovpI = poImeni.empty() ||
                     m_koty[i]->getImya().find(poImeni) != std::string::npos;
        bool sovpP = poPorode.empty() ||
                     m_koty[i]->getPoroda().find(poPorode) != std::string::npos;
        
        if (sovpI && sovpP) {
            if (nashli == 0) std::cout << "\nНайдено:\n";
            std::cout << i + 1 << ". Имя: " << m_koty[i]->getImya()
                      << " | Порода: " << m_koty[i]->getPoroda()
                      << " | Возраст: " << m_koty[i]->getVozrast() << " лет\n";
            nashli++;
        }
    }
    if (nashli == 0) std::cout << "Ничего не найдено\n";
}

void BazaKotov::dobavit() {
    std::string imya = vvodStroki("Кличка: ");
    std::string poroda = vvodStroki("Порода: ");
    int vozrast = vvodCisla("Возраст: ", 0, 30);
    std::string cvet = vvodStroki("Окрас: ");
    std::string primeti = vvodStroki("Приметы: ");
    bool naMeste = vvodBoolean("На месте? (y/n): ");
    
    udvoitMassiv();
    m_koty[m_kolichestvo] = new Kot(imya, poroda, vozrast, cvet, primeti, naMeste);
    m_kolichestvo++;
    
    std::cout << "Кот добавлен\n";
}

void BazaKotov::udalit() {
    if (m_kolichestvo == 0) {
        std::cout << "Нет котов для удаления\n";
        return;
    }
    
    pokazat();
    int nomer = vvodCisla("Номер кота для удаления: ", 1, m_kolichestvo);
    
    delete m_koty[nomer - 1];
    umenshitMassiv(nomer - 1);
    m_kolichestvo--;
    
    std::cout << "Кот удалён\n";
}

void BazaKotov::redakt() {
    if (m_kolichestvo == 0) {
        std::cout << "Нет котов для редактирования\n";
        return;
    }
    
    pokazat();
    int nomer = vvodCisla("Номер кота для редактирования: ", 1, m_kolichestvo);
    
    Kot* kot = m_koty[nomer - 1];
    
    std::cout << "\n--- Редактирование кота ---\n";
    std::string imya = vvodStroki("Новое имя (" + kot->getImya() + "): ");
    if (!imya.empty()) kot->setImya(imya);
    
    std::string poroda = vvodStroki("Новая порода (" + kot->getPoroda() + "): ");
    if (!poroda.empty()) kot->setPoroda(poroda);
    
    int vozrast = vvodCisla("Новый возраст (" + std::to_string(kot->getVozrast()) + "): ", 0, 30);
    if (vozrast >= 0) kot->setVozrast(vozrast);
    
    std::string cvet = vvodStroki("Новый окрас (" + kot->getCvet() + "): ");
    if (!cvet.empty()) kot->setCvet(cvet);
    
    std::string primeti = vvodStroki("Новые приметы (" + kot->getPrimeti() + "): ");
    if (!primeti.empty()) kot->setPrimeti(primeti);
    
    bool naMeste = vvodBoolean("На месте? (y/n, сейчас " +
                                std::string(kot->getNaMeste() ? "да" : "нет") + "): ");
    kot->setNaMeste(naMeste);
    
    std::cout << "Кот отредактирован\n";
}

int BazaKotov::vvodCisla(const std::string& prompt, int min, int max) {
    int znachenie;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        
        std::stringstream ss(input);
        if (ss >> znachenie && znachenie >= min && znachenie <= max) {
            return znachenie;
        }
        std::cout << "ERROR: Введите число от " << min << " до " << max << "\n";
    }
}

std::string BazaKotov::vvodStroki(const std::string& prompt) {
    std::cout << prompt;
    std::string result;
    std::getline(std::cin, result);
    return result;
}

bool BazaKotov::vvodBoolean(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        
        if (input == "y" || input == "Y" || input == "yes" || input == "YES") {
            return true;
        }
        if (input == "n" || input == "N" || input == "no" || input == "NO") {
            return false;
        }
        std::cout << "Введите y или n\n";
    }
}
