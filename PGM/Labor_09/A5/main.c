#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct customer
{
    int customerNumber;
    char firstName[20];
    char lastName[20];
    struct customer *next;
} customer;

customer *createCustomer(int customerNumber, char *firstName, char *lastName)
{
    customer *newCustomer = malloc(sizeof(customer));
    newCustomer->customerNumber = customerNumber;
    strcpy(newCustomer->firstName, firstName);
    strcpy(newCustomer->lastName, lastName);
    newCustomer->next = NULL;
    return newCustomer;
}

void addCustomer(customer *root, customer *newCustomer)
{
    customer *current = root;
    while (current->next != NULL && current->next->customerNumber < newCustomer->customerNumber)
    {
        current = current->next;
    }
    newCustomer->next = current->next;
    current->next = newCustomer;
}

void printList(customer *root)
{
    customer *current = root;
    while (current != NULL)
    {
        printf("%d: %s %s\n", current->customerNumber, current->firstName, current->lastName);
        current = current->next;
    }
}

unsigned int customerCount(customer *root)
{
    customer *current = root;
    unsigned int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void clearList(customer *root)
{
    customer *current = root;
    while (current != NULL)
    {
        customer *next = current->next;
        free(current);
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