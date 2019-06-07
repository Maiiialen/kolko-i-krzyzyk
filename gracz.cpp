#include <iostream>

using namespace std;

// klasa ścieżki wykorzystywana w reprezentacji Gracza jako znak
// Znak - znak 'X' albo 'O'
class Gracz{
    char Znak;

    public:

    // funkcja zmieniająca znak w klasie
    void Ustaw_znak(char zn);

    // funkcja zwracająca znak gracza
    char Podaj_znak();
};

void Gracz::Ustaw_znak(char zn){
    Znak = zn;          // ustawienie znaku na nowy, poodany w argumencie
}

char Gracz::Podaj_znak(){
    return Znak;        // zwrócenie wartości zmiennaj Znak
}