#ifndef KOT_HPP
#define KOT_HPP

#include <iostream>
#include <string>

class Kot {
private:
    std::string m_imya;
    std::string m_poroda;
    int m_vozrast;
    std::string m_cvet;
    std::string m_primeti;
    bool m_naMeste;

public:
    Kot();
    Kot(const std::string& imya, const std::string& poroda, int vozrast,
        const std::string& cvet, const std::string& primeti, bool naMeste);

    std::string getImya() const;
    std::string getPoroda() const;
    int getVozrast() const;
    std::string getCvet() const;
    std::string getPrimeti() const;
    bool getNaMeste() const;

    void setImya(const std::string& imya);
    void setPoroda(const std::string& poroda);
    void setVozrast(int vozrast);
    void setCvet(const std::string& cvet);
    void setPrimeti(const std::string& primeti);
    void setNaMeste(bool naMeste);

    friend std::ostream& operator<<(std::ostream& os, const Kot& kot);
    friend std::istream& operator>>(std::istream& is, Kot& kot);
};

#endif
