#include <stdio.h>

int main(int argc, char *argv[])
{
    char field[20][20] = {0}; // game field
    int gens;                 // number of generations
    scanf("%d", &gens);       // input by user
    while (1)
    { // runs till 'break;'
        char c;
        scanf(" %c", &c); // read next char
        if (c == 'a')
        { // break at char 'e'
            int i, j;
            scanf("%d %d", &i, &j); // scan coordinates
            field[j][i] = 1;        // setting cell to state alive
        }
        else
        {
            break;
        }
    }
    // calculate and print generations
    for (int i = 0; i <= gens; i++)
    {
        printf("-- Generation: %d\n", i);
        // iterating over each cell
        for (int k = 0; k < 20; k++)
        {
            for (int l = 0; l < 20; l++)
            {
                // print current generation
                if ((field[k][l] & 1) == 1)
                {
                    printf("%c", '#'); // alive
                }
                else
                {
                    printf("%c", '.'); // dead
                }

                // counting neighbors of field[k][l]
                int neighbors = 0;
                for (int y = -1; y < 2; y++)
                {
                    for (int x = -1; x < 2; x++)
                    {
                        if (!(x == 0 && y == 0))
                        {
                            if (k + y < 20 &&
                                k + y >= 0 &&
                                l + x < 20 &&
                                l + x >= 0)
                            {
                                if ((field[k + y][l + x] & 1) == 1)
                                {
                                    neighbors++;
                                }
                            }
                        }
                    }
                }
                // rules
                // Any live cell with two or three live neighbours survives.
                // Any dead cell with three live neighbours becomes a live cell.
                // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
                if ((field[k][l] & 1) == 1 &&
                    (neighbors == 2 || neighbors == 3))
                {
                    field[k][l] |= (1 << 1);
                }
                else if ((field[k][l] & 1) == 0 &&
                         neighbors == 3)
                {
                    field[k][l] |= (1 << 1);
                }
                else if ((field[k][l] & 1) == 1)
                {
                    field[k][l] &= ~(1 << 1);
                }
            }
            printf("\n");
        }

        // setting gamefield to new generation
        for (int a = 0; a < 20; a++)
        {
            for (int b = 0; b < 20; b++)
            {
                field[a][b] >>= 1;
            }
        }
    }
    return 0;
}