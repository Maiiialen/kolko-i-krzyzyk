#include <iostream>

using namespace std;

class Gracz{
    char Znak;

    public:
    Gracz();
    void Ustaw_znak(char zn);
    void Wykonaj_ruch();
};

void Gracz::Ustaw_znak(char zn){
    Znak = zn;
}