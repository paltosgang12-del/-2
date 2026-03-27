#include "kot.h"

Kot::Kot()
    : m_imya(""), m_poroda(""), m_vozrast(0),
      m_cvet(""), m_primeti(""), m_naMeste(false) {}

Kot::Kot(const std::string& imya, const std::string& poroda, int vozrast,
         const std::string& cvet, const std::string& primeti, bool naMeste)
    : m_imya(imya), m_poroda(poroda), m_vozrast(vozrast),
      m_cvet(cvet), m_primeti(primeti), m_naMeste(naMeste) {}

std::string Kot::getImya() const { return m_imya; }
std::string Kot::getPoroda() const { return m_poroda; }
int Kot::getVozrast() const { return m_vozrast; }
std::string Kot::getCvet() const { return m_cvet; }
std::string Kot::getPrimeti() const { return m_primeti; }
bool Kot::getNaMeste() const { return m_naMeste; }

void Kot::setImya(const std::string& imya) { m_imya = imya; }
void Kot::setPoroda(const std::string& poroda) { m_poroda = poroda; }
void Kot::setVozrast(int vozrast) { m_vozrast = vozrast; }
void Kot::setCvet(const std::string& cvet) { m_cvet = cvet; }
void Kot::setPrimeti(const std::string& primeti) { m_primeti = primeti; }
void Kot::setNaMeste(bool naMeste) { m_naMeste = naMeste; }

std::ostream& operator<<(std::ostream& os, const Kot& kot) {
    os << kot.m_imya << "|" << kot.m_poroda << "|" << kot.m_vozrast << "|"
       << kot.m_cvet << "|" << kot.m_primeti << "|" << (kot.m_naMeste ? "1" : "0");
    return os;
}

std::istream& operator>>(std::istream& is, Kot& kot) {
    std::string str;
    if (std::getline(is, str)) {
        size_t pos1 = str.find('|');
        size_t pos2 = str.find('|', pos1 + 1);
        size_t pos3 = str.find('|', pos2 + 1);
        size_t pos4 = str.find('|', pos3 + 1);
        size_t pos5 = str.find('|', pos4 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos &&
            pos3 != std::string::npos && pos4 != std::string::npos &&
            pos5 != std::string::npos) {
            kot.m_imya = str.substr(0, pos1);
            kot.m_poroda = str.substr(pos1 + 1, pos2 - pos1 - 1);
            kot.m_vozrast = std::stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
            kot.m_cvet = str.substr(pos3 + 1, pos4 - pos3 - 1);
            kot.m_primeti = str.substr(pos4 + 1, pos5 - pos4 - 1);
            kot.m_naMeste = (str.substr(pos5 + 1) == "1");
        }
    }
    return is;
}
