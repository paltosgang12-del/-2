#ifndef BAZA_KOTOV_HPP
#define BAZA_KOTOV_HPP

#include "kot.h"
#include <string>

class BazaKotov {
private:
    Kot** m_koty;
    int m_kolichestvo;
    std::string m_imyaFaila;

    void udvoitMassiv();
    void umenshitMassiv(int index);

public:
    BazaKotov();
    explicit BazaKotov(const std::string& imyaFaila);
    ~BazaKotov();

    BazaKotov(const BazaKotov&) = delete;
    BazaKotov& operator=(const BazaKotov&) = delete;

    bool zagruzit();
    bool sohranit() const;
    void sohranitKak(const std::string& novoeImya);

    void pokazat() const;
    void poisk() const;
    void dobavit();
    void udalit();
    void redakt();

    int poluchitKolichestvo() const { return m_kolichestvo; }
    
    static int vvodCisla(const std::string& prompt, int min = 1, int max = 1000000);
    static std::string vvodStroki(const std::string& prompt);
    static bool vvodBoolean(const std::string& prompt);
};

#endif
