#include <iostream>

using namespace std;

class Gracz{
    char Znak;

    public:
    void Ustaw_znak(char zn);
    char Podaj_znak();
    void Wykonaj_ruch();
};

void Gracz::Ustaw_znak(char zn){
    Znak = zn;
}

char Gracz::Podaj_znak(){
    return Znak;
}