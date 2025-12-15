#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define COPY_GRID(dest, src, h, w) \
    for (int i = 0; i < h; i++) \
        for (int j = 0; j < w; j++) \
            dest[i][j] = src[i][j];
#define ALLOC_ARRAY(dest, h, w) \
    dest = malloc(h * sizeof(char *)); \
    for (int i = 0; i < h; i++) { \
        dest[i] = malloc(w * sizeof(char)); \
    }
#define FREE_ARRAY(arr, h) \
    for (int i = 0; i < h; i++) { \
        free(arr[i]); \
    } \
    free(arr);

void printArray(char **arr, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j])
                putchar(arr[i][j]);
        }
        putchar('\n');
    }
}

int countNeighbors(char **arr, int height, int width, int y, int x) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++) {
        for (int xx = x - 1; xx <= x + 1; xx++) {
            if (yy == y && xx == x)
                continue;
            if (yy >= 0 && yy < height && xx >= 0 && xx < width && arr[yy][xx] == 'o')
                count++;
        }
    }
    return count;
}

void gameOfLife(char **arr, int height, int width, int iterations) {
    char **res;
    ALLOC_ARRAY(res, height, width);
    COPY_GRID(res, arr, height, width);

    for (int iter = 0; iter < iterations; iter++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int neighbors = countNeighbors(arr, height, width, y, x);
                res[y][x] = (arr[y][x] == 'o' && (neighbors < 2 || neighbors > 3)) ? ' ' : (arr[y][x] == ' ' && neighbors == 3) ? 'o' : arr[y][x];
            }
        }
        COPY_GRID(arr, res, height, width);
    }
    COPY_GRID(arr, res, height, width);
    FREE_ARRAY(res, height);
}

int main (int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);

   char **arr = NULL;
   ALLOC_ARRAY(arr, height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = ' ';
        }
    }

    char buffer[10000];
    ssize_t bytes = read(0, buffer, sizeof(buffer));
    buffer[bytes] = '\0';

    int y = 0, x = 0, drawing = 0;
    for (int i = 0; i < bytes; i++) {
        switch (buffer[i]) {
            case 'w':
                y--;  
                break;
            case 'a':
                x--;  
                break;
            case 's':
                y++;  
                break;
            case 'd':
                x++;  
                break;
            case 'x':
                drawing = !drawing;  
                break;
        }
        if (drawing && x >= 0 && x < width && y >= 0 && y < height) 
            arr[y][x] = 'o';  
    }
    gameOfLife(arr, height, width, iterations);
    printArray(arr, height, width);
    FREE_ARRAY(arr, height);

    return 0;
}