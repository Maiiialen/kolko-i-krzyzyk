#include <iostream>

using namespace std;

class Plansza{
    char **Macierz;
    int wielkosc;

    public:
    Plansza(int wielkosc);
    ~Plansza();
    int Czy_wygrana();
    void Wyswietlanie();
};

Plansza::Plansza(int wiel){
    wielkosc = wiel;
    Macierz = new char* [wielkosc];
    for(int i = 0; i < wielkosc; ++i){
        Macierz[i] = new char [wielkosc];
    }
    for(int i = 0; i < wielkosc; ++i){
        for(int j = 0; j < wielkosc; ++j){
            Macierz[i][j] = ' ';
        }
    }
}

Plansza::~Plansza(){
    for(int i = 0; i < wielkosc; ++i){
        delete Macierz[i];
    }
    delete Macierz;
}

void Plansza::Wyswietlanie(){
    for(int i = 0; i < wielkosc; ++i){
        for(int j = 0; j < wielkosc; ++j){
            cout << Macierz[i][j] << " ";
        }
        cout << endl;
    }
}