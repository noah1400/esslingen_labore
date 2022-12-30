#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct customer
{
    // Jeder Kunde hat eine Kundennummer, einen Vornamen und einen Nachnamen
    int customerNumber;
    char firstName[20];
    char lastName[20];
    struct customer *next;
} customer;

// Diese Funktion erstellt einen neuen Kunden und gibt einen Zeiger darauf zurück
customer *createCustomer(int customerNumber, char *firstName, char *lastName)
{
    // Hier wird Speicherplatz für einen neuen Kunden reserviert
    customer *newCustomer = malloc(sizeof(customer));

    // Die Felder des Kunden werden mit den übergebenen Werten initialisiert
    newCustomer->customerNumber = customerNumber;
    strcpy(newCustomer->firstName, firstName);
    strcpy(newCustomer->lastName, lastName);

    // Der nächste Kunde ist zunächst noch nicht definiert und wird daher auf NULL gesetzt
    newCustomer->next = NULL;

    // Der Zeiger auf den neuen Kunden wird zurückgegeben
    return newCustomer;
}

// Diese Funktion fügt einen neuen Kunden in eine Kundenliste ein
void addCustomer(customer *root, customer *newCustomer)
{
    // Hier wird der Anfang der Liste auf das erste Element gesetzt
    customer *current = root;

    // Solange es noch ein nächstes Element gibt 
    // und die Kundennummer des nächsten Kunden kleiner ist als die Kundennummer des neuen Kunden...
    while (current->next != NULL && current->next->customerNumber < newCustomer->customerNumber)
    {
        // ...wird zum nächsten Kunden gesprungen
        current = current->next;
    }

    // Hier wird der Zeiger des neuen Kunden auf den nächsten Kunden gesetzt
    newCustomer->next = current->next;

    // Und der Zeiger des aktuellen Kunden wird auf den neuen Kunden gesetzt
    current->next = newCustomer;
}

// Diese Funktion gibt alle Kunden in der Liste aus
void printList(customer *root)
{
    // Hier wird der Anfang der Liste auf das erste Element gesetzt
    customer *current = root;

    // Solange es noch ein aktuelles Element gibt...
    while (current != NULL)
    {
        // ...wird die Kundennummer, der Vorname und der Nachname ausgegeben
        printf("%d: %s %s\n", current->customerNumber, current->firstName, current->lastName);

        // Dann wird zum nächsten Kunden gesprungen
        current = current->next;
    }
}

// Diese Funktion gibt die Anzahl der Kunden in der Liste zurück
unsigned int customerCount(customer *root)
{
    // Hier wird der Anfang der Liste auf das erste Element gesetzt
    customer *current = root;

    // Der Zähler für die Anzahl der Kunden wird initialisiert
    unsigned int count = 0;

    // Solange es noch ein aktuelles Element gibt...
    while (current != NULL)
    {
        // ...wird der Zähler um 1 erhöht
        count++;

        // Dann wird zum nächsten Kunden gesprungen
        current = current->next;
    }

    // Die Anzahl der Kunden wird zurückgegeben
    return count;
}

// Diese Funktion löscht alle Kunden in der Liste
void clearList(customer *root)
{
    // Hier wird der Anfang der Liste auf das erste Element gesetzt
    customer *current = root;

    // Solange es noch ein aktuelles Element gibt...
    while (current != NULL)
    {
        // ...wird der Zeiger auf den nächsten Kunden gesichert
        customer *next = current->next;

        // Dann wird der Speicherplatz für den aktuellen Kunden freigegeben
        free(current);

        // Der Zeiger wird auf den nächsten Kunden gesetzt
        current = next;
    }
}

int main(int argc, char *argv[])
{
    customer *root = NULL;
    root = createCustomer(1, "Hans", "Maurer");
    addCustomer(root, createCustomer(3, "Tatjana", "Roth"));
    addCustomer(root, createCustomer(2, "Anna-Maria", "Schmidt"));
    printf("Momentan sind %u Kunden erfasst.\n", customerCount(root));
    printList(root);
    clearList(root);
    root = NULL;

    printf("Momentan sind %u Kunden erfasst.\n", customerCount(root));
    printList(root);
    return 0;
}