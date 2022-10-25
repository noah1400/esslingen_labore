//
//  main.c
//  Sechste-Aufgabe
//
//  Created by Fatih Karayüksel on 11.10.22.
//
//  INPUT: 5454698 35460.545 x
//  OUTPUT:
//  Ganzzahlen    : 0005454698
//  Gleitkommazahl: 35460.54688
//  Zeichen       : x

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a;
    float b;
    char c;
    
    scanf("%d  %f %c", &a, &b, &c);
    printf("Ganzzahlen    : %010d\nGleitkommazahl: %5.5f\nZeichen       : %c\n", a, b, c);
}
