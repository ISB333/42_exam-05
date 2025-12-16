#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int		rows, cols;
char empty, obstacle, full;
char	*line = NULL;
char	**map;

#define printMap()                      \
	for (int i = 0; i < rows; i++)      \
		fprintf(stdout, "%s", map[i]);

#define FREE_ARRAY(arr, h)      \
	for (int i = 0; i < h; i++) \
		free(arr[i]);           \
	free(arr);

#define LEN(str) ({            \
	int	ij = 0;                \
	while (str && str[++ij]);  \
	ij; })

int isInvalidMap() {
    int lineWithBox = 0;
    for (int i = 0; map[i]; i++) {
        int lastLen = i > 0 ? LEN(map[i - 1]) : 0; 
        for (int j = 0; map[i][j]; j++) {
            if (map[i][j] == obstacle)
                lineWithBox = 1;
            if ((map[i][j] != empty && map[i][j] != obstacle && map[i][j] != full) && j != LEN(map[i]) - 1)
                return 1;
            if (!(map[i][j] >= 32 && map[i][j] <= 126) && j != LEN(map[i]) - 1)
                return 1;
        }
        if (map[i][LEN(map[i]) - 1] != '\n' && i != rows - 1)
            return 1;
        else if (i != rows - 1)
            map[i][LEN(map[i])] = '\0';
    }
    if (!lineWithBox || (empty == obstacle || empty == full || obstacle == full))
        return 1;
    return cols = LEN(map[0]), 0;
}

int canPlaceSquare(int row, int col, int size) {
    if (row + size > rows || col + size > cols)
        return 0;
    
    for (int i = row; i < row + size; i++)
        for (int j = col; j < col + size; j++)
            if (map[i][j] != empty)
                return 0;
    return 1;
}

void findBiggestSquare() {
    int max_size = 0, best_row = 0, best_col = 0;
    
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int size = max_size + 1; size <= rows && size <= cols; size++)
                if (canPlaceSquare(i, j, size)) {
                    max_size = size;
                    best_row = i;
                    best_col = j;
                } else {
                    break;
                }
    
    for (int i = best_row; i < best_row + max_size; i++)
        for (int j = best_col; j < best_col + max_size; j++)
            map[i][j] = full;
}

void init(FILE *file) {
	size_t	read = 0, len = 0;

    fscanf(file, "%d %c %c %c\n", &rows, &empty, &obstacle, &full);
    map = malloc((rows + 1) * sizeof(char *));
    map[rows] = NULL;

	for (int i = 0; i < rows; i++) {
		map[i] = malloc((getline(&line, &len, file) + 1) * sizeof(char));
		for (int j = 0; j < LEN(line); j++)
			map[i][j] = line[j];
		map[i][LEN(line)] = '\0';
	}
}

void	solveBSQ(FILE *file) {
    init(file);

    if (isInvalidMap())
        fprintf(stderr, "map error\n");
    else
        findBiggestSquare();

	printMap();
	FREE_ARRAY(map, rows);
	free(line);
}

int	main(int argc, char *argv[]) {
	if (argc > 2)
		return (fprintf(stderr, "map error\n"));
	if (argc == 1)
		return (1);

	FILE *file = fopen(argv[1], "r");
	if (!file)
		fprintf(stderr, "map error\n");

	solveBSQ(file);
	fclose(file);
}