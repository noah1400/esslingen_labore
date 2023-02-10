#include <stdio.h>

int tree_width(int height)
{ // max width of the tree -2 (for the / and \)
    return height * 2 + 2;
}

void tree_print_piece(int height, int index)
{
    int limit = 3;
    if (index == height - 1)
    {
        limit = 2; // dont print the last row of the last piece
    }
    for (int i = 0; i < limit; i++)
    {
        for (int j = 0; j < height + 1 - index - i; j++)
        {
            printf(" "); // spaces before the /
        }
        printf("/");
        for (int j = 0; j < i * 2 + index * 2; j++)
        {
            if (i == 2 && (j == 0 || j == (i + index) * 2 - 1))
            {
                printf("_"); // first and last char of the last row
            }
            else if (j % 4 == 1)
            {
                printf("i"); // "i" if j is a multiple of 4 + 1 (1, 5, 9, ...) 
            }
            else
            {
                printf(" "); // space otherwise
            }
        }
        printf("\\\n"); // closing / with \ and newline
    }
    if (index != height - 1)
    {
        tree_print_piece(height, index + 1); // print next piece
    }
    else if (index == height - 1)
    { // print the last row of the last piece
        printf("/");
        for (int i = 0; i < tree_width(height); i++)
        {
            printf("_");
        }
        printf("\\\n");
    }
}

void tree_print_log_row(int height)
{
    int i;
    for (i = 0; i < tree_width(height) / 2; i++)
    {
        printf(" ");
    }
    printf("##\n");
}

void tree_log(int height)
{ // could be done with case statements and a loop but this is more readable imo
    if (height == 1)
    {
        tree_print_log_row(height);
    }
    else if (height == 2)
    {
        tree_print_log_row(height);
        tree_print_log_row(height);
    }
    else
    {
        tree_print_log_row(height);
        tree_print_log_row(height);
        tree_print_log_row(height);
    }
}

int main(void)
{
    // read height
    int height;
    scanf("%d", &height);
    // print tree
    tree_print_piece(height, 0);
    // print log
    tree_log(height);
    return 0;
}