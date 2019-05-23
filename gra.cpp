#include <iostream>
#include "gracz.cpp"
#include "plansza.cpp"

using namespace std;

class Gra{
    int Wielkosc_planszy;
    char Obecny_gracz;
    int Warunek_wygranej;
    int Tryb_gry;
    Gracz Pierwszy;
    Gracz Drugi;
    Plansza *plansza;

    public:
    Gra(char znak, int wielkosc, int warunek, int tryb);
    //~Gra();
    void Rozgrywka();
    void Minmax();
};

Gra::Gra(char znak, int wielkosc, int warunek, int tryb){
    Wielkosc_planszy = wielkosc;
    Obecny_gracz = znak;
    Warunek_wygranej = warunek;
    Tryb_gry = tryb;
    plansza = new Plansza(Wielkosc_planszy);
    Pierwszy.Ustaw_znak(znak);
    if(znak == 'O')
        Drugi.Ustaw_znak('X');
    else
        Drugi.Ustaw_znak('O');
}


void Gra::Rozgrywka(){
    plansza->Macierz[1][1] = Pierwszy.Podaj_znak();
    plansza->Macierz[2][2] = Drugi.Podaj_znak();
    plansza->Wyswietlanie();
}