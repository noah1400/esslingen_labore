#include <stdio.h>

typedef struct numberItem
{
    int number;
    struct numberItem *next;
} numberItem;

void appendNumberItem(numberItem **root, int number)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(numberItem));
        (*root)->number = number;
        (*root)->next = NULL;
        return;
    }
    numberItem *current = *root;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(numberItem));
    current->next->number = number;
    current->next->next = NULL;
}

void printList(numberItem *root)
{
    numberItem *current = root;
    while (current != NULL)
    {
        printf("%d\n", current->number);
        current = current->next;
    }
}

void clearList(numberItem *root)
{
    numberItem *current = root;
    while (current != NULL)
    {
        numberItem *next = current->next;
        free(current);
        current = next;
    }
}