#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int width, height, iterations;

#define ALLOC_ARRAY(h, w) ({                  \
    char **dest = malloc(h * sizeof(char *)); \
    for (int i = 0; i < h; i++)               \
        dest[i] = malloc(w * sizeof(char));   \
    dest; })

#define FREE_ARRAY(arr) \
    for (int i = 0; i < height; i++) \
        free(arr[i]); \
    free(arr);

int countNeighbors(char **arr, int y, int x) {
    int neighbors = 0;
    for (int yy = y - 1; yy <= y + 1; yy++) {
        for (int xx = x - 1; xx <= x + 1; xx++) {
            if (yy == y && xx == x)
                continue;
            if (yy >= 0 && yy < height && xx >= 0 && xx < width && arr[yy][xx] == 'O')
                neighbors++;
        }
    }
    return neighbors;
}

void gameOfLife(char **arr) {
    char **res = ALLOC_ARRAY(height, width);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            res[y][x] = arr[y][x];

    for (int iter = 0; iter < iterations; iter++) {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++) {
                int neighbors = countNeighbors(arr, y, x);
                res[y][x] = (arr[y][x] == 'O' && (neighbors < 2 || neighbors > 3)) ? ' ' : (arr[y][x] == ' ' && neighbors == 3) ? 'O' : arr[y][x];
            }
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                arr[y][x] = res[y][x];
    }
    FREE_ARRAY(res);
}

int main (int argc, char *argv[]) {
    if (argc != 4)
        return 1;

    width = atoi(argv[1]), height = atoi(argv[2]), iterations = atoi(argv[3]);

    char **arr = ALLOC_ARRAY(height, width);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            (x == width) ? (arr[y][x] = '\0') : (arr[y][x] = ' ');

    int y = 0, x = 0, drawing = 0;
    char cmd;
    while (read(0, &cmd, 1) > 0) {
            if (cmd == 'w')
                y--;  
            else if (cmd == 'a')
                x--;  
            else if (cmd == 's')
                y++;  
            else if (cmd == 'd')
                x++;  
            else if (cmd == 'x')
                drawing = !drawing;  
        if (drawing && x >= 0 && x < width && y >= 0 && y < height) 
            arr[y][x] = 'O';  
    }
    gameOfLife(arr);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            arr[y][x] ? putchar(arr[y][x]) : (void)0;
            x == width - 1 ? putchar('\n') : (void)0;
        }
    }
    FREE_ARRAY(arr);
    return 0;
}