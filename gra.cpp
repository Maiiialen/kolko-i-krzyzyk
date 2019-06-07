#include <iostream>
#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>
#include "gracz.cpp"
#include "plansza.cpp"

using namespace std;

// klasa gry wykorzystywana do zarządzania rozgrywką, 
//  ruchami graczy oraz menu
// Wielkosc_planszy - wielkosc planszy
// Warunek_wygranej - liczba będąca ilością znaków po sobie warunkująca wygraną
// Obecny_gracz - wskaźnik na gracza, którzy obecnie wykonuje ruch
// Przeciwny_gracz - wskaźnik na gracza, którzy oczekuje na swój ruch
// tryb_gry - napis mający wartość "00", "01" lub "11", warunkuje czy gra toczy się
//  z udziałem człowieka, komputera, czy obu
// Pierwszy - gracz rozpoczynający grę
// Drugi - gracz rozpoczynający w drugiej turze gry
// plansza - wskaźnik na dwuwymiarową macierz znaków
// znaneWyniki - tablica z haszowaniem zapisująca znane ułożenia planszy i wartości
//  optymalne do wygranej
class Gra{
    int Wielkosc_planszy;
    int Warunek_wygranej;
    Gracz *Obecny_gracz;
    Gracz *Przeciwny_gracz;
    string Tryb_gry;
    Gracz Pierwszy;
    Gracz Drugi;
    Plansza *plansza;

    public:
    // konstruktor ustawiający początkowe wartości zmiennych
    Gra();

    // funkcja zarządzająca rozgrywką, kolenością ruchów i sprawdzająca
    //  czy gra powinna toczyć się dalej
    int Rozgrywka();

    // funkcja znajdująca i wykonująca najlepszy ruch komputera
    void Minmax();

    // funkcja składowa funkcji Minmax
    int MaxSzukany(int glebokosc);
    
    // funkcja składowa funkcji Minmax
    int MinSzukany(int glebokosc);
    
    // funkcja wyświetlająca menu, pozwalająca na zmianę warunków gry,
    //  pozwala też na rozpoczęcie gry lub zakończenie programu,
    //  w przypadku rozpoczęcia gry tworzy macierz, będącą planszą do gry
    int menu();
    
    // funkcja wyświetlająca tryb gry - kkto z kim gra na podstawie zmiennej Tryb_gry
    void Tryb();
    
    // funkcja sprawdzająca czy gracz podany w argumencie wygrał
    bool Czy_wygrana(Gracz* gracz);
    
    // funkcja sprawdzająca czy można jeszcze wykonać ruch czy
    //  gra zakończyła się remisem
    bool Czy_remis();
    
    // funkcja pozwalająca wykonać ruch człowieka
    void Ruch_Czlowieka();
    
    // funkcja wywołująca ruch komputera
    void Ruch_Komputera();
    
    // tablica z haszowaniem
    unordered_map<string,int> znaneWyniki;
};



Gra::Gra(){
    Wielkosc_planszy = 3;       // nadanie domyślnej wartości wielkosci planszy
    Warunek_wygranej = 3;       // nadanie domyślnego warunku wygrany
    Tryb_gry = "01";            // nadanie domyślnego trybu gry (człowiek vs komputer)
    Pierwszy.Ustaw_znak('X');   // nadanie domyślnego znaku pierwzsego gracza
    Drugi.Ustaw_znak('O');      // nadanie domyślnego znaku drugiego gracza 
    Obecny_gracz = &Pierwszy;   // nadanie wskaźnika na pierwszego gracza
    Przeciwny_gracz = &Drugi;   // nadanie wskaźnika na drugiego gracza
}

bool Gra::Czy_remis(){
    for(int i=0; i<Wielkosc_planszy; ++i){          // przejście przez całą tablicę
        for(int j=0; j<Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' ')       // jeśli jest możliwość postawienia znaku
                return 0;                           //  nie ma remisu
        }
    }
    return 1;                                       // jeśli nie można postawić już znaku - remis
}

bool Gra::Czy_wygrana(Gracz* gracz){
    bool sprawdzenie = 1;
    for(int i=0; i<Wielkosc_planszy; i++) {
        for(int j=0; j<Wielkosc_planszy; j++) {
            if(plansza->Macierz[i][j] == gracz->Podaj_znak()) {  //jesli pole nie jest puste
                if(j+Warunek_wygranej-1 < Wielkosc_planszy) {  //jesli kolejne dwa pola w prawo nie wychodza za plansze
                    for(int k=1; k<Warunek_wygranej; k++) { //przechodzi przez kolejne pola
                        if(plansza->Macierz[i][j] != plansza->Macierz[i][j+k]) {    //jesli ktores nie jest takie samo jak poprzednie
                            sprawdzenie = 0;    //to nie ma tutaj wygranej
                            break;
                        }
                    }
                    if(sprawdzenie) {   //jesli nie znaleziono przeciwskazania do wygranej
                        return 1;    //to wygrana
                    } 
                    else {  //w innym przypadku brak
                        sprawdzenie = 1; //i reset
                    }
                }

                if(i+Warunek_wygranej-1 < Wielkosc_planszy) {  //jesli kolejne dwa pola w dol nie wychodza za plansze
                    for(int k=1; k<Warunek_wygranej; k++) { //przechodzi przez kolejne pola
                        if(plansza->Macierz[i][j] != plansza->Macierz[i+k][j]) {    //jesli ktores nie jest takie samo jak poprzednie
                            sprawdzenie = 0;    //to nie ma tutaj wygranej
                            break;
                        }
                    }
                    if(sprawdzenie) {   //jesli nie znaleziono przeciwskazania do wygranej
                        return 1;    //to wygrana
                    } 
                    else {  //w innym przypadku brak
                        sprawdzenie = 1; //i reset
                    }
                }

                if(i+Warunek_wygranej-1 < Wielkosc_planszy && j+Warunek_wygranej-1 < Wielkosc_planszy) {  //jesli kolejne dwa pola w prawo i w dol nie wychodza za plansze
                    for(int k=1; k<Warunek_wygranej; k++) { //przechodzi przez kolejne pola
                        if(plansza->Macierz[i][j] != plansza->Macierz[i+k][j+k]) {    //jesli ktores nie jest takie samo jak poprzednie
                            sprawdzenie = 0;    //to nie ma tutaj wygranej
                            break;
                        }
                    }
                    if(sprawdzenie) {   //jesli nie znaleziono przeciwskazania do wygranej
                        return 1;    //to wygrana
                    } 
                    else {  //w innym przypadku brak
                        sprawdzenie = 1; //i reset
                    }
                }

                if(i-Warunek_wygranej+1 >= 0 && j+Warunek_wygranej-1 < Wielkosc_planszy) {  //jesli kolejne dwa pola w lewo i w dol nie wychodza za plansze
                    for(int k=1; k<Warunek_wygranej; k++) { //przechodzi przez kolejne pola
                        if(plansza->Macierz[i][j] != plansza->Macierz[i-k][j+k]) {    //jesli ktores nie jest takie samo jak poprzednie
                            sprawdzenie = 0;    //to nie ma tutaj wygranej
                            break;
                        }
                    }
                    if(sprawdzenie) {   //jesli nie znaleziono przeciwskazania do wygranej
                        return 1;    //to wygrana
                    } 
                    else {  //w innym przypadku brak
                        sprawdzenie = 1; //i reset
                    }
                }
            }
        }
    }
    return 0;
}

void Gra::Ruch_Czlowieka(){
    string ruch;
    int one, two;
    do {                // pętla kończąca się gdy podany zostanie odpowiedni zbiór znaków
        cout << endl;
        cout << "Podaj wspolrzedne: "; cin >> ruch;     // podanie współrzędnych kolejnego ruchu
        cout << endl;
        if(ruch.size()==2){         // sprawdzenie czy podana jest odpowiednia ilość znaków
            one = ruch[0]-'0';
            two = ruch[1]-'0';

            if(one>=0 && one<Wielkosc_planszy && two>=0 && two<Wielkosc_planszy){   // sprawdzenie czy podane cyfry mieszą się w przedziale od 0 do Wielkosc_planszy
                if(plansza->Macierz[one][two] == ' '){                              // sprawdzenie czy to miejsce w tablicy nie jest już zajęte 
                    plansza->Macierz[one][two] = Obecny_gracz->Podaj_znak();        // jeśli wszystko jest ok, to wpisz znak
                    break;
                } else {
                    cout << "Bledna wartosc! To pole jest już zajęte" << endl;                              // informacja o podaniu współrzędnych zajętego pola
                }
            } else {
                cout << "Bledna wartosc! Podaj cyfry z przedziału od 0 do " << Wielkosc_planszy << endl;    // informacja o podaniu za dużej wartości
            }
        } else {
            cout << "Bledna wartosc! Podaj dwie cyfry (00)" << endl;                                        // informacja o podaniu zbyt dużej ilości cyfr
        }
    } while(1);
}

int Gra::Rozgrywka(){
    Gracz *tymczasowy;
    char znak;

    for(int i=0; 1; ++i){       // niekończąca się pętla
        if(!Czy_wygrana(Przeciwny_gracz)){      //sprawdzenie czy nie ma jeszcze wygranej
            if(!Czy_remis()){                   // sprawdzenie czy są jeszcze możliwe ruchy
                system("cls");
                plansza->Wyswietlanie();        // wyświetlanie planszy
                if(Tryb_gry[i%2] == '0'){       // decyzja czy jest to ruch człowieka czy komputera na podstawie trybu gry
                    Ruch_Czlowieka();           // wywołanie funkcji obsługującej ruch człowieka
                } else {
                    Ruch_Komputera();           // wywołanie funkcji obługującej ruch komputera
                }
                tymczasowy = Obecny_gracz;      // nadanie możliwości ruchudrugiemu graczowi
                Obecny_gracz = Przeciwny_gracz;
                Przeciwny_gracz = tymczasowy;
            } else {                            // jeśli remis, zakończ grę, wyświetl planszę i podaj wynik
                system("cls");
                plansza->Wyswietlanie();
                cout << "Remis!!!" << endl;
            cin >> znak;
            system("cls");
                return 0;
            }
        } else {                                // jeśli wygrana, zakończ grę, wyświetl planszę i podaj wynik
            cout << endl;
            system("cls");
            plansza->Wyswietlanie();
            cout << "Wygral gracz " << Przeciwny_gracz->Podaj_znak() << "!!!" << endl;
            cin >> znak;
            system("cls");
            return 0;
        }
    }
}


void Gra::Ruch_Komputera(){
    Minmax();       // wywołanie funkcji Minmax
}

void Gra::Minmax(){
    int glebokosc = 0;      // ustawienie głębokości obliczeń copozwoli wybrać najlepszą opcję
    int wynik = INT_MAX, zmienna, x = -1, y = -1;
    for(int i = 0; i < Wielkosc_planszy; ++i){      // sprawdzanie dla każdego pola najlepszego ruchu 
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Obecny_gracz->Podaj_znak();
                zmienna = MaxSzukany(glebokosc);        // wywolanie funkcji MaxSzukany z argumentem glembokość
                if(zmienna < wynik){
                    wynik = zmienna;
                    x = i;
                    y = j;
                }
                plansza->Macierz[i][j] = ' ';       // wrócenie do dawnego stanu gry, usunięcie śladów testów
            }
        }
    }
    plansza->Macierz[x][y] = Obecny_gracz->Podaj_znak();    // wykonanie najlepszego ruchu
}

int Gra::MaxSzukany(int glebokosc){
    string napis;
    for(int i=0; i<Wielkosc_planszy; i++) {         // zapis obecnego stanu planszy - znaków z tablicy do napisu
        for(int j=0; j<Wielkosc_planszy; j++) {
            napis += plansza->Macierz[i][j];
        }
    }
    auto szukaj = znaneWyniki.find(napis);      // sprawdzenie czy obecny stan planszy jest już znany - był już napotkany
    if (szukaj != znaneWyniki.end()) {
        return szukaj->second;                  //jesli tak to zwraca jego wczesniej wyliczona wartosc
    }

    if(Czy_wygrana(Przeciwny_gracz))    // sprawdzenie czy w tym ruchu wugrałby człowiek
        return 10-glebokosc;
    else if(Czy_wygrana(Obecny_gracz))  // sprawdzenie czy w tym ruchu wygrałby komputer
        return -10+glebokosc;
    else if(Czy_remis())                // sprawdzenie czy takie ustawienie doprowadzi do remisu
        return 0;

    int wynik = INT_MIN;
    for(int i = 0; i < Wielkosc_planszy; ++i){          // sprawdzanie kolejnych ruchów od danego stanu gry
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Przeciwny_gracz->Podaj_znak();
                wynik = max(wynik, MinSzukany(glebokosc+1));
                plansza->Macierz[i][j] = ' ';
            }
        }
    }
    znaneWyniki.insert({napis, wynik});     // zapisanie danego stanu planszy i wyniku otrzymanego z funkcji do tablicy haszującej
    return wynik;
}

int Gra::MinSzukany(int glebokosc){
    string napis;
    for(int i=0; i<Wielkosc_planszy; i++) {         // zapis obecnego stanu planszy - znaków z tablicy do napisu
        for(int j=0; j<Wielkosc_planszy; j++) {
            napis += plansza->Macierz[i][j];
        }
    }
    auto szukaj = znaneWyniki.find(napis);      // sprawdzenie czy obecny stan planszy jest już znany - był już napotkany 
    if (szukaj != znaneWyniki.end()) {
        return szukaj->second;                  //jesli tak to zwraca jego wczesniej wyliczona wartosc
    }

    if(Czy_wygrana(Przeciwny_gracz))    // sprawdzenie czy w tym ruchu wugrałby człowiek
        return 10-glebokosc;
    else if(Czy_wygrana(Obecny_gracz))  // sprawdzenie czy w tym ruchu wygrałby komputer
        return -10+glebokosc;
    else if(Czy_remis())                // sprawdzenie czy takie ustawienie doprowadzi do remisu
        return 0;

    int wynik = INT_MIN;
    for(int i = 0; i < Wielkosc_planszy; ++i){          // sprawdzanie kolejnych ruchów od danego stanu gry
        for(int j = 0; j < Wielkosc_planszy; ++j){
            if(plansza->Macierz[i][j] == ' '){
                plansza->Macierz[i][j] = Obecny_gracz->Podaj_znak();
                wynik = min(wynik, MaxSzukany(glebokosc+1));
                plansza->Macierz[i][j] = ' ';
            }
        }
    }
    znaneWyniki.insert({napis, wynik});     // zapisanie danego stanu planszy i wyniku otrzymanego z funkcji do tablicy haszującej
    return wynik;
}

void Gra::Tryb(){
    if(Tryb_gry[0] == '1')      // jeśli '1' jest to komputer
        cout << "komputer";
    else
        cout << "czlowiek";     // jeśli '0' jest to człowiek

    cout << " vs ";

    if(Tryb_gry[1] == '1')
        cout << "komputer";     // jeśli '1' jest to komputer
    else
        cout << "czlowiek";     // jeśli '0' jest to człowiek
}

int Gra::menu(){
    int wybor = 0, zmienna = 0, wartosc = 0;
    char cos;
    do{             // pętla kończąca się gdy wyborem będzie zakończenie programu
        ala:
        cout << "obecne ustawienia:" << endl;           // wyświetlenie obecnych ustawień
        cout << "\t wielkosc planszy " << Wielkosc_planszy << "x" << Wielkosc_planszy << endl;
        cout << "\t warunek wygranej: " << Warunek_wygranej << " pod rzad" << endl;
        cout << "\t tryb gry : ";
        Tryb();
        cout << endl;
        if(Tryb_gry == "01"){       // wyświrtlenie różnych omunikatów zależnie od tryby gry
            cout << "\t \t znak czlowieka: " << Pierwszy.Podaj_znak() << endl;
            cout << "\t \t znak komputera: " << Drugi.Podaj_znak() << endl;
        } else {
            cout << "\t \t znak pierwszego gracza: " << Pierwszy.Podaj_znak() << endl;
            cout << "\t \t znak drugiego gracza: " << Drugi.Podaj_znak() << endl;
        }
        cout << "\t gracz rozpoczynajacy gre: " << Obecny_gracz->Podaj_znak() << endl;
        
        cout << endl;           // wyświetlenie możliwych wyborów
        cout << "1. rozpocznij gre" << endl;
        cout << "2. zakoncz" << endl;
        
        cout << endl;

        cout << "zmiana ustawien:" << endl;
        cout << "\t 3. ustaw wielkosc planszy" << endl;
        cout << "\t 4. ustaw warunek wygranej" << endl;
        cout << "\t 5. ustaw tryb gry" << endl;
        cout << "\t 6. zmiana znaku" << endl;

        cout << endl;
        cout << "wybierz opcje: "; cin >> wybor;        // pobranie liczby od gracza
        switch (wybor){
            case 1:                                         // jeśli rozpoczęcie gry to
                plansza = new Plansza(Wielkosc_planszy);    //  utwórz planszę
                system("cls");
                Rozgrywka();                                //  i zacznij grę
                break;
            case 2:         // jeśli zakończ grę to zwróć 0
                return 0;
            case 3:
                do{         // pętla kończąca się gdy podany zostanie odpowiedni zbiór znaków
                    cout << "podaj wielkosc planszy (1-5): "; cin >> wartosc;   // pobranie liczby
                    if(wartosc >= 1 && wartosc <= 5){       // sprawdzenie czy liczba jest w odpowiednim przedziale
                        Wielkosc_planszy = wartosc;         // zmiana wartości zmiennej
                        break;
                    } else {
                        system("cls");
                        cout << "bledna wartosc!!!" << endl;    // informacja o błędnej wartości podanej
                        cout << endl;
                    }
                }while(1);
                break;
            case 4:
                do{         // pętla kończąca się gdy podany zostanie odpowiedni zbiór znaków
                    cout << "podaj nowy warunek wygranej (nie wiekszy niz wielkosc planszy): "; cin >> zmienna;     // pobranie liczby od gracza
                    if(zmienna > 0 && zmienna <= Wielkosc_planszy){
                        Warunek_wygranej = zmienna;
                        break;
                    } else {
                        system("cls");
                        cout << "bledna wartosc!!!" << endl;    // informacja o błędnej wartości
                        cout << endl;
                    }
                } while (1);
                break;
            case 5:
                do{         // pętla kończąca się gdy podany zostanie odpowiedni zbiór znaków
                    cout << "podaj nowy tryb gry:" << endl;     // wyświetlenie opcji trybów
                    cout << "1. komputer vs komputer" << endl;
                    cout << "2. czlowiek vs komputer" << endl;
                    cout << "3. czlowiek vs czlowiek" << endl;
                    cin >> wartosc;         // pobranie wartości od gracza
                    if(wartosc == 1){       // ustawienie nowego trynu
                            Tryb_gry = "11";
                            break;
                    } else if(wartosc == 2) {
                            Tryb_gry = "01";
                            break;
                    } else if(wartosc == 3) {
                            Tryb_gry = "00";
                            break;
                    } else {
                        system("cls");
                        cout << "bledna wartosc!!!" << endl;    // informacja o błędnej wartości
                        cout << endl;
                    }
                }while(1);
                break;
            case 6:
                do{         // pętla kończąca się gdy podany zostanie odpowiedni zbiór znaków
                    cout << "podaj znak ";          // pobranie znaku jaki ma posiadać teraz pierwszy gracz
                    if(Tryb_gry == "01"){           // różne komunikaty zależne od wybranego trybu gry
                        cout << "czlowieka (X, O): "; cin >> cos;
                        if(cos == 'X'){
                            Pierwszy.Ustaw_znak('X');       // nadawanie wybranego znaku
                            Drugi.Ustaw_znak('O');          // nadawanie przeciwnego znaku do wybranego
                            break;
                        } else if(cos == 'O'){
                            Pierwszy.Ustaw_znak('O');       // nadawanie wybranego znaku
                            Drugi.Ustaw_znak('X');          // nadawanie przeciwnego znaku do wybranego
                            break;
                        } else{
                            system("cls");
                            cout << "bledna wartosc!!!" << endl;        // informacja o błędnym znaku
                            cout << endl;
                        }
                    } else {
                        cout << "pierwszego gracza (X, O): "; cin >> cos;
                        if(cos == 'X'){
                            Pierwszy.Ustaw_znak('X');       // nadawanie wybranego znaku
                            Drugi.Ustaw_znak('O');          // nadawanie przeciwnego znaku do wybranego
                            break;
                        } else if(cos == 'O'){
                            Pierwszy.Ustaw_znak('O');       // nadawanie wybranego znaku
                            Drugi.Ustaw_znak('X');          // nadawanie przeciwnego znaku do wybranego
                            break;
                        } else{
                            system("cls");
                            cout << "bledna wartosc!!!" << endl;        // informacja o błędnym znaku
                            cout << endl;
                        }
                    }
                }while(1);
                break;
            default:
                system("cls");
                cout << "bledna wartosc!!!" << endl;        // informacja o podaniu znaku z poza przedziału
                cout << endl;
                goto ala;
        }
    } while(1);
    return -1;
} 