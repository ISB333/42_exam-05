#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ALLOC_ARRAY(h, w) ({                  \
    char **dest = malloc(h * sizeof(char *)); \
    for (int i = 0; i < h; i++)               \
        dest[i] = malloc(w * sizeof(char));   \
    dest; })

#define FREE_ARRAY(arr, h) \
    for (int i = 0; i < h; i++) \
        free(arr[i]); \
    free(arr);

#define ITER(h, w, y, x, yValue, xValue)   \
    for (int y = yValue; y < h; y++)       \
        for (int x = xValue; x < w; x++)

void gameOfLife(char **arr, int height, int width, int iterations) {
    char **res = ALLOC_ARRAY(height, width);
    ITER(height, width, i, j, 0, 0)
        res[i][j] = arr[i][j];

    for (int iter = 0; iter < iterations; iter++) {
        ITER(height, width, y, x, 0, 0){
            int neighbors = 0;
            ITER(y + 2, x + 2, i, j, y - 1, x - 1) {
                if (i == y && j == x)
                    continue;
                if (i >= 0 && i < height && j >= 0 && j < width && arr[i][j] == 'O')
                    neighbors++;
            }
            res[y][x] = (arr[y][x] == 'O' && (neighbors < 2 || neighbors > 3)) ? ' ' : (arr[y][x] == ' ' && neighbors == 3) ? 'O' : arr[y][x];
        }
        ITER(height, width, i, j, 0, 0)
            arr[i][j] = res[i][j];
    }
    ITER(height, width, i, j, 0, 0)
        res[i][j] = arr[i][j];
    FREE_ARRAY(res, height);
}

int main (int argc, char *argv[]) {
    if (argc != 4)
        return 1;

    int width = atoi(argv[1]), height = atoi(argv[2]), iterations = atoi(argv[3]);

    char **arr = ALLOC_ARRAY(height, width);
    ITER(height, width, i, j, 0, 0)
        (j == width) ? (arr[i][j] = '\0') : (arr[i][j] = ' ');

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
    gameOfLife(arr, height, width, iterations);
    ITER(height, width, y, x, 0 ,0) {
        arr[y][x] ? putchar(arr[y][x]) : (void)0;
        x == width - 1 ? putchar('\n') : (void)0;
    }
    FREE_ARRAY(arr, height);
    return 0;
}