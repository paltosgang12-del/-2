#ifndef POCHTA_THINGS_H
#define POCHTA_THINGS_H

#include <string>

class Posylka {
public:
    Posylka();
    Posylka(std::string tr, std::string otpr, std::string pol,
           double ves, int otkuda, int kuda);

    std::string getTr();
    std::string getOtpr();
    std::string getPol();
    double getVes();
    int getOtkuda();
    int getKuda();
    int getGde();
    int getDney();

    void setGde(int id);
    void setDney(int dn);
    void proshloDney(int dn);

private:
    std::string treker;
    std::string otpravitel;
    std::string poluchatel;
    double ves;
    int izOtdela;
    int vOtdel;
    int seychasGde;
    int ostalosDney;
};

#endif
