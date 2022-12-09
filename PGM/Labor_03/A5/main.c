/*
Eingabe
3 6
*/

/*
Ausgabe
+-+-+-
-+-+-+
+-+-+-
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    printf("+");
                }
                else
                {
                    printf("-");
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    printf("-");
                }
                else
                {
                    printf("+");
                }
            }
        }
        printf("\n");
    }
    return 0;
}
