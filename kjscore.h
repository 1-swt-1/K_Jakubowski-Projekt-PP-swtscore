#ifndef SCORE_H
#define SCORE_H

//struktura naszego zawodnika
typedef struct Zawodnik {
    char imie[51];
    char nazwisko[51];
    int mecze;
    int gole;
    int asysty;
    char stan[51];
    struct Zawodnik *next;
    
} Zawodnik;

//prototypy funkcji



void wyczysc();//do czyszczenia terminala

void dodaj(Zawodnik **head);//head to bedzie adres pierwszego elementu z listy
void wyswietl(Zawodnik *head);
void wczytaj(Zawodnik *head);
void zwolnij(Zawodnik *head);//w celu zwolnienia pamieci ram przy zamknieciu programu 
//dodane zostaną potem inne kluczowe konieczne funkcje

void sortuj(Zawodnik *head);




#endif