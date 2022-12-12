#include <stdio.h>
#include <string.h>

typedef struct Kunde
{
    int kundennummer;
    char vorname[20];
    char nachname[20];
} Kunde;

int main(int argc, char *argv[])
{
    Kunde kunde1 = {1, "Hans", "Maurer"};
    Kunde kunde2;
    kunde2.kundennummer = 2;
    scanf("%d %s %s", &kunde2.kundennummer, kunde2.vorname, kunde2.nachname);
    printf("%d: %s %s\n", kunde1.kundennummer, kunde1.vorname, kunde1.nachname);
    printf("%d: %s %s", kunde2.kundennummer, kunde2.vorname, kunde2.nachname);
}