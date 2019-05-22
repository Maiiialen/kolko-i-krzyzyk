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
    Gra(char znak, int wielkosc, int warunek, int tryb);
    ~Gra();
    void Minmax();
};

Gra::Gra(char znak, int wielkosc, int warunek, int tryb){
    Wielkosc_planszy = wielkosc;
    Obecny_gracz = znak;
    Warunek_wygranej = warunek;
    Tryb_gry = tryb;
    Pierwszy.Ustaw_znak(znak);
    if(znak == 'O')
        Pierwszy.Ustaw_znak('X');
    else
        Drugi.Ustaw_znak('O');
}