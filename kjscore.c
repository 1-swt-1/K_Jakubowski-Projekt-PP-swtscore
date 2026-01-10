#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//isalpha
#include "kjscore.h"

void wyczysc() {//czysczenie terminala unix
    system("clear");//dla windows: "cls"
}

void cz_buforu() {//czyszczenie buforu wprowadzania
    while (getchar() != '\n');
}

//funkcje do pobierania z klawiatury

int pobierz_int(int min, int max) {
    int liczba;
    while (1) {
       if (scanf("%d", &liczba) == 1) {
            if (liczba >= min && liczba <= max) {
                cz_buforu();
                return liczba;
            } else {
                printf("Błąd! Podaj liczbę z zakresu od %d do %d: ", min, max);
            }
       } else {
            printf("Błąd! To nie jest liczba.\nSpróbuj ponownie: ");
            cz_buforu();
       }
    }
}

void pobierz_tekst(char *cel, int max_len) {
    char bufor[101];
    while (1) {
        scanf("%s", bufor);

        int same_litery = 1;
        for (unsigned long i = 0; i < strlen(bufor); i++) {
            if(!isalpha(bufor[i]) && bufor[i] != '-') {//wykluczamy "-" dla podwojnych nazwisk
                same_litery = 0;
                break;
            }
        }

        if (same_litery && strlen(bufor) < max_len) {
            strcpy(cel, bufor);
            cz_buforu();
            return;
        } else {
            printf("\nBłąd Używaj tylko liter.\nSpróbuj ponownie: ");
            cz_buforu();
        }
    }
}

//pozostałe funkcje
Zawodnik *stworz(char *im, char *naz, int m, int g, int a, char *st) {
    Zawodnik *new = (Zawodnik *)malloc(sizeof(Zawodnik));//"(Zawodnik *)" symboliozuje strukture zawodnik
    if (new == NULL) exit(1);

    strcpy(new->imie, im);
    strcpy(new->nazwisko, naz);
    new->mecze = m;
    new->gole = g;
    new->asysty = a;
    strcpy(new->stan, st);
    new->next = NULL;//nastepny narazie ejst pusty
    return new;
}

void dodaj(Zawodnik **head) {
    char im[51], naz[51], st[51];
    int m, g, a;

    wyczysc();
    printf("===Dodawanie zawodnika===\n");
    printf("Podaj imie: ");
    pobierz_tekst(im, 51);
    printf("Podaj nazwisko: "); 
    pobierz_tekst(naz, 51);
    printf("Mecze: ");          
    m = pobierz_int(0, 100);
    printf("Gole: ");           
    g = pobierz_int(0, 100);
    printf("Asysty: ");         
    a = pobierz_int(0, 100);
    printf("Stan zdrowia (jedno slowo): ");   
    pobierz_tekst(st, 51);

    Zawodnik *new = stworz(im, naz, m, g, a, st); 
    new->next = *head;
    *head = new; 
}

void usun(Zawodnik **head) {
    wyczysc();
    if (*head == NULL) {//gdy nie ma pierwszego zawodnika
        printf("Lista pusta.\nNacisnij ENTER..."); 
        getchar(); 
        return;
    }

    char cel[51];
    printf("Nazwisko do usuniecia: "); 
    pobierz_tekst(cel, 51);

    Zawodnik *p = *head;
    Zawodnik *prev = NULL;
    if (p != NULL && strcmp(p->nazwisko, cel) == 0) {//strcmp zwraca 0 gdy wiadomosci są identyczne
        *head = p->next;
        free(p);
        printf("Usunieto.\nNacisnij ENTER aby kontynuować"); 
        getchar();//pauza żeby wymusic u uzytkownika wcisniecie enteru
        return;
    }

    while (p != NULL && strcmp(p->nazwisko, cel) != 0) {
        prev = p;
        p = p->next;//lączy dwoch zawodników ktorzy byli oddzieleni tym usuniętym
    }

    if (p == NULL) {//jesli p jest puste to nic nie znaleziono
        printf("Nie znaleziono.\n");
    } else {
        prev->next = p->next;//Przestań wskazywać na p, a zacznij wskazywać na to, co stoi za nim (omija zawodnika usunietego)
        free(p);
        printf("Usunieto.\n");
    }
    printf("Naciśnij ENTER aby kontynuować");
    getchar();
}

void zapisz(Zawodnik *head, char *nazwa_pliku) {
    FILE *f = fopen(nazwa_pliku, "w");
    if (f == NULL) {
        printf("Bląd otwarcia pliku do zapisu!\n");
        printf("Naciśnij ENTER aby kontynuować"); 
        getchar();
        return;
    }

    Zawodnik *p = head;//wskaźnik do chodzenia po liście od początku
    while (p != NULL) {
        fprintf(f, "imię:%s nazwisko:%s mecze:%d gole:%d asysty:%d stan_zdrowia:%s\n", 
            p->imie, p->nazwisko, p->mecze, p->gole, p->asysty, p->stan);
        p = p->next;
    }
    fclose(f);
    wyczysc();
    printf("Zapisano zmiany do pliku: %s\n", nazwa_pliku);
    printf("Naciśnij ENTER aby kontynuować"); 
    getchar(); 
}

void wczytaj(Zawodnik **head, char *nazwa_pliku) {
    FILE *f = fopen(nazwa_pliku, "r");//otwarcie pliku w trybie odczytu (read)
    if (f == NULL) return;//brak pliku to nie błąd, po prostu pusta lista na start

    char im[51], naz[51], st[51];
    int m, g, a;
    while (fscanf(f, "imię:%s nazwisko:%s mecze:%d gole:%d asysty:%d stan_zdrowia:%s\n", im, naz, &m, &g, &a, st) == 6) {
        Zawodnik *new = stworz(im, naz, m, g, a, st);//tworzenie zawodnika w pamięci na podstawie linii z pliku
        new->next = *head;//doklejanie go do budowanej listy
        *head = new;//aktualizacja początku listy
    }
    fclose(f);
}

void sortuj_gole(Zawodnik *head) {

}

void sortuj_nazwisko(Zawodnik *head) {

}

void wyswietl(Zawodnik *head) { //funkcja drukująca całą kadrę na ekranie
    int wyb = -1; //zmienna na wybór opcji sortowania (cos innego niż 0,1,2)
    while (wyb != 0) {
        wyczysc();
        printf("|=================Kadra zespolu==================|\n");
        printf("|Imie||Nazwisko||Mecze||Gole||Asysty||StanZdrowia|\n");
        printf("|================================================|\n");
        
        Zawodnik *p = head;
        while (p != NULL) {
            printf("| %s %s M:%d G:%d A:%d %s\n", 
                p->imie, p->nazwisko, p->mecze, p->gole, p->asysty, p->stan);
            p = p->next; //skok do następnej osoby
        }

        printf("|================================================|\n");
        printf("1. Sortuj po golach strzelonych\n");
        printf("2. Sortuj alfabetycznie (po nazwisku)\n");
        printf("0. Wyjscie\n");
        printf("|================================================|\n");
        printf("Wybieram: ");
        
        wyb = pobierz_int(0, 2);

        if (wyb == 1) { //jeśli wybrano sortowanie po golach
            sortuj_gole(head);
        } else if (wyb == 2) {
            sortuj_nazwisko(head);
        }
    }
}

//funkcja czyszcząca pamięć RAM przed zamknięciem programu
void zwolnij(Zawodnik *head) { 
    while (head != NULL) { //pętla działa dopóki w liście są elementy
        Zawodnik *tmp = head; //zapamiętanie adresu obecnego zawodnika
        head = head->next; //przesunięcie głowy listy na następną osobę
        free(tmp);
    }
}

void wyszukaj(Zawodnik *head) {

}



