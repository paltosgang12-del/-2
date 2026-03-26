#ifndef KOT_H
#define KOT_H

#include <iostream>
#include <string>

class Kot {
private:
    std::string imya;
    std::string poroda;
    int vozrast;
    std::string cvet;
    std::string primeti;
    bool naMeste;

public:
    Kot();
    Kot(std::string i, std::string p, int v, std::string c, std::string prim, bool m);

    std::string getImya();
    std::string getPoroda();
    int getVozrast();
    std::string getCvet();
    std::string getPrimeti();
    bool getNaMeste();

    void setImya(std::string i);
    void setPoroda(std::string p);
    void setVozrast(int v);
    void setCvet(std::string c);
    void setPrimeti(std::string prim);
    void setNaMeste(bool m);

    friend std::ostream& operator<<(std::ostream& os, Kot& k);
    friend std::istream& operator>>(std::istream& is, Kot& k);
};

inline std::ostream& operator<<(std::ostream& os, Kot& k) {
    os << k.imya << "|" << k.poroda << "|" << k.vozrast << "|"
       << k.cvet << "|" << k.primeti << "|" << (k.naMeste ? "1" : "0");
    return os;
}

inline std::istream& operator>>(std::istream& is, Kot& k) {
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
            k.imya = str.substr(0, pos1);
            k.poroda = str.substr(pos1 + 1, pos2 - pos1 - 1);
            k.vozrast = std::stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
            k.cvet = str.substr(pos3 + 1, pos4 - pos3 - 1);
            k.primeti = str.substr(pos4 + 1, pos5 - pos4 - 1);
            k.naMeste = (str.substr(pos5 + 1) == "1");
        }
    }
    return is;
}

#endif
