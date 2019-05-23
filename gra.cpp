#include <iostream>
#include <algorithm>
#include <climits>
#include "gracz.cpp"
#include "plansza.cpp"

using namespace std;

class Gra{
    int Wielkosc_planszy;
    Gracz *Obecny_gracz;
    Gracz *Przeciwny_gracz;
    int Warunek_wygranej;
    int Tryb_gry;
    Gracz Pierwszy;
    Gracz Drugi;
    Plansza *plansza;

    public:
    Gra(char znak, int wielkosc, int warunek, int tryb);
    void Rozgrywka();
    void Minmax();
    int MaxSzukany();
    int MinSzukany();
};

Gra::Gra(char znak, int wielkosc, int warunek, int tryb){
    Wielkosc_planszy = wielkosc;
    Warunek_wygranej = warunek;
    Tryb_gry = tryb;
    plansza = new Plansza(Wielkosc_planszy);
    Pierwszy.Ustaw_znak(znak);
    Obecny_gracz = &Pierwszy;
    if(znak == 'O'){
        Drugi.Ustaw_znak('X');
        Przeciwny_gracz = &Drugi;
    } else {
        Drugi.Ustaw_znak('O');
        Przeciwny_gracz = &Drugi;
    }
}


void Gra::Rozgrywka(){
    Gracz *tymczasowy = Obecny_gracz;
    plansza->Macierz[1][1] = Pierwszy.Podaj_znak();
    plansza->Macierz[2][2] = Drugi.Podaj_znak();
    plansza->Wyswietlanie();
    cout << endl;
    Minmax();
    Obecny_gracz = Przeciwny_gracz;
    Przeciwny_gracz = tymczasowy;
    Minmax();
    plansza->Wyswietlanie();
}

void Gra::Minmax(){
    int wynik = INT_MAX, zmienna, x = -1, y = -1;
    for(int i = 0; i < Wielkosc_planszy; ++i){
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Obecny_gracz->Podaj_znak();
                zmienna = MaxSzukany();
                if(zmienna < wynik){
                    wynik = zmienna;
                    x = i;
                    y = j;
                }
                plansza->Macierz[i][j] = ' ';
            }
        }
    }
    cout << Obecny_gracz->Podaj_znak() << endl;
    cout << "aaa " << x << ", " << y << endl;
    plansza->Macierz[x][y] = Obecny_gracz->Podaj_znak();
}

int Gra::MaxSzukany(){/*
    if(Wygrana(Przeciwny_gracz->Podaj_znak()))
        return 10;
    else if(Obecny_gracz->Podaj_znak())
        return -10;
    else if(Remis())
        return 0;
*/
    int wynik = INT_MIN;
    for(int i = 0; i < Wielkosc_planszy; ++i){
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Przeciwny_gracz->Podaj_znak();
                wynik = max(wynik, MinSzukany());
                plansza->Macierz[i][j] = ' ';
            }
        }
    }
    return wynik;
}

int Gra::MinSzukany(){/*
    if(Wygrana(Przeciwny_gracz->Podaj_znak()))
        return 10;
    else if(Obecny_gracz->Podaj_znak())
        return -10;
    else if(Remis())
        return 0;
*/
    int wynik = INT_MIN;
    for(int i = 0; i < Wielkosc_planszy; ++i){
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Obecny_gracz->Podaj_znak();
                wynik = min(wynik, MaxSzukany());
                plansza->Macierz[i][j] = ' ';
            }
        }
    }
    return wynik;
}