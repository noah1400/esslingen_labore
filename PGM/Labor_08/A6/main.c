#include <stdio.h>

char getFirstCapitalLetter(char *str)
{
    if (*str == '\0')
    {
        return ' ';
    }
    if (*str >= 'A' && *str <= 'Z')
    {
        return *str;
    }
    return getFirstCapitalLetter(str + 1);
}

int main(int argc, char *argv[])
{
    char str[100];
    scanf("%s", str);
    printf("%c", getFirstCapitalLetter(str));
    return 0;
}
