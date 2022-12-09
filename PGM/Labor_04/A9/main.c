/*
3 5
*/

/*
Ausgabe
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
16
17
[...]
194
fizzbuzz
196
197
fizz
199
buzz
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= 200; i++) {
        if (i % n == 0 && i % m == 0) {
            printf("fizzbuzz\n");
        }else if (i % n == 0) {
            printf("fizz\n");
        }else if (i % m == 0) {
            printf("buzz\n");
        }else {
            printf("%d\n", i);
        }
    }
    return 0;
}