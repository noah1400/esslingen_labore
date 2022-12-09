#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SPITZE 1
#define GUT 2
#define BEFRIEDIGEND 3
#define AUSREICHEND 4
#define DURCHGEFALLEN 5
#define JA 1
#define NEIN 0

int main(void)
{
    unsigned int note, bestanden;
    printf("Geben Sie bitte eine Note (1-5) ein: ");
    scanf("%u", &note);
    //   if (note == SPITZE)
    //     bestanden = JA;
    //   else if (note == GUT)
    //     bestanden = JA;
    //   else if (note == BEFRIEDIGEND)
    //     bestanden = JA;
    //   else if (note == AUSREICHEND)
    //     bestanden = JA;
    //   else
    //     bestanden = NEIN;
    switch (note)
    {
    case SPITZE:
    case GUT:
    case BEFRIEDIGEND:
    case AUSREICHEND:
        bestanden = JA;
        break;
    default:
        bestanden = NEIN;
        break;
    }
    bestanden ? printf("\nOK!") : printf("\nNICHT bestanden");
    return 0;
}
