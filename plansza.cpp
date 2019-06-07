#include <iostream>

using namespace std;

// klasa planszy wykorzystywana w reprezentacji planszy jako macierz
// wielkosc - wielkosc planszy
// Macierz - wskaźnik na dwuwymiarową macierz znaków
class Plansza{
    int wielkosc;

    public:
    char **Macierz;

    // konstruktor tworzący macierz o odpowiednich rozmiarach podanych w
    //  argumencie i wypełnia macierz znakami spacji
    Plansza(int wielkosc);

    // destruktor planszy usuwający macierz
    ~Plansza();

    // funkcja wyświetlająca planszę
    //  obramowanie oraz znaki z macierzy
    void Wyswietlanie();
};

Plansza::Plansza(int wiel){
    wielkosc = wiel;
    Macierz = new char* [wielkosc];         // utworzenie tablicy dynamicznej o danej wielkości
    for(int i = 0; i < wielkosc; ++i){      // utworzenie w każdym elemencie tablicy, tablicy znaków
        Macierz[i] = new char [wielkosc];
    }
    for(int i = 0; i < wielkosc; ++i){      // nadanie wszystkim alementom tablicy znak spacji
        for(int j = 0; j < wielkosc; ++j){
            Macierz[i][j] = ' ';
        }
    }
}

Plansza::~Plansza(){
    for(int i = 0; i < wielkosc; ++i){      // usunięcie wszystkich wierszy tablicy 
        delete Macierz[i];
    }
    delete Macierz;                         // usunięcie tablicy dynamicznej
}

void Plansza::Wyswietlanie(){
    cout << "+";        // wyświetlenie pierwszej linii poziomej
    for(int i = 0; i<wielkosc; ++i)
        cout << "---+";
    cout << endl;
    

    for(int i = 0; i < wielkosc; ++i){
        for(int j = 0; j < wielkosc; ++j){
            cout << "| " << Macierz[i][j] << " ";       // wyświetlenie linii pionowej
        }
        cout << "|" << endl;       // wyswietlenie ostatniej linii pionowej

        cout << "+";        // wyświetlenie linii poziomej
        for(int i = 0; i<wielkosc; ++i)
            cout << "---+";
        cout << endl;
    }
}