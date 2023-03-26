#include <stdio.h>

#define FIELD_WIDTH 20
#define FIELD_HEIGHT 20

typedef struct {
    int x;
    int y;
    int state;
} Cell;

void readInput(Cell field[FIELD_WIDTH][FIELD_HEIGHT]) {
    int x, y;
    char c;
    while (scanf(" %c", &c) == 1) {
        if (c == 'a') {
            scanf("%d %d", &x, &y);
            field[y][x].state = 1;
        } else {
            break;
        }
    }
}

int countNeighbors(Cell field[FIELD_WIDTH][FIELD_HEIGHT], int x, int y) {
    int neighbors = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!(i == 0 && j == 0)) {
                int neighborX = x + i;
                int neighborY = y + j;
                if (neighborX >= 0 && neighborX < FIELD_WIDTH && neighborY >= 0 && neighborY < FIELD_HEIGHT) {
                    if (field[neighborY][neighborX].state == 1) {
                        neighbors++;
                    }
                }
            }
        }
    }
    return neighbors;
}

void updateField(Cell field[FIELD_WIDTH][FIELD_HEIGHT]) {
    Cell newField[FIELD_WIDTH][FIELD_HEIGHT];
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            int neighbors = countNeighbors(field, x, y);
            if (field[y][x].state == 1) {
                newField[y][x].state = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newField[y][x].state = (neighbors == 3) ? 1 : 0;
            }
            newField[y][x].x = x;
            newField[y][x].y = y;
        }
    }
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            field[y][x] = newField[y][x];
        }
    }
}

void printField(Cell field[FIELD_WIDTH][FIELD_HEIGHT]) {
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            printf("%c", (field[y][x].state == 1) ? '#' : '.');
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    Cell field[FIELD_WIDTH][FIELD_HEIGHT] = {0};
    int gens;
    scanf("%d", &gens);
    readInput(field);
    for (int i = 0; i <= gens; i++) {
        printf("-- Generation: %d\n", i);
        printField(field);
        updateField(field);
    }
    return 0;
}
