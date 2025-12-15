#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int count_neighbors(char **board, int width, int height, int x, int y) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i == y && j == x) 
                continue;
            if (i >= 0 && i < height && j >= 0 && j < width && board[i][j] == 'o')
                count++;
        }
    }
    return count;
}

void game_of_life_iteration(char **board, int width, int height) {
    char **new_board = malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        new_board[i] = malloc(width + 1);
        for (int j = 0; j < width; j++) {
            int neighbors = count_neighbors(board, width, height, j, i);
            if (board[i][j] == 'o')
                new_board[i][j] = (neighbors == 2 || neighbors == 3) ? 'o' : ' ';
            else
                new_board[i][j] = (neighbors == 3) ? 'o' : ' ';
        }
        new_board[i][width] = '\0';
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

void print_board(char **board, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    
    char **board = malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        board[i] = malloc(width + 1);
        for (int j = 0; j < width; j++) {
            board[i][j] = ' ';
        }
        board[i][width] = '\0';
    }
    
    int x = 0, y = 0, pen_down = 0;
    char cmd;
    while (read(0, &cmd, 1) > 0) {
        if (cmd == 'x') 
            pen_down = !pen_down;
        if (cmd == 'w') 
            y--;
        if (cmd == 's') 
            y++;
        if (cmd == 'a') 
            x--;
        if (cmd == 'd') 
            x++;
        if (pen_down && x >= 0 && x < width && y >= 0 && y < height) {
            board[y][x] = 'o';
        }
    }
    
    for (int i = 0; i < iterations; i++)
        game_of_life_iteration(board, width, height);
    print_board(board, width, height);
    
    return 0;
}