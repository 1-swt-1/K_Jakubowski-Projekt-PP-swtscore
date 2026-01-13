#ifndef SCORE_H
#define SCORE_H

#include <string.h>
#include <ctype.h>//isalpha

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
void cz_buforu();//czyszczenie buforu

int pobierz_int(int min, int max);
void pobierz_tekst(char *cel, int max_len);

void dodaj(Zawodnik **head);//head to bedzie adres pierwszego elementu z listy
void usun(Zawodnik **head);

void zapisz(Zawodnik *head, char *nazwa_pliku);
void wczytaj(Zawodnik **head, char *nazwa_pliku);

void wyswietl(Zawodnik *head);
void wyszukaj(Zawodnik *head);
void zwolnij(Zawodnik *head);//w celu zwolnienia pamieci ram przy zamknieciu programu 

void sortuj_gole(Zawodnik *head);
void sortuj_nazwisko(Zawodnik *head);


#endif