#include <iostream>
#include "gracz.cpp"

using namespace std;

class Gra{
    int Wielkosc_planszy;
    char Obecny_gracz;
    int Warunek_wygranej;
    int Tryb_gry;
    Gracz Pierwszy;
    Gracz Drugi;

    public:
    Gra();
    ~Gra();
    void Minmax();
};