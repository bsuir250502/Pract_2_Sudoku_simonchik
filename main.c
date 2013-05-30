#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int field[SIZE][SIZE];

void InputField()
{
    int i, j;
    FILE *infile;
    infile = fopen("sudoku_in", "r");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            field[i][j] = getc(infile) - '0';
        }
        getc(infile);
    }
    fclose(infile);
}

void DisplaySudoku()
{
    int i, j;
    printf("====================\n\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (j == 2 || j == 5 || j == 8) {
                printf("%2d ", field[i][j]);
            } else {
                printf("%2d", field[i][j]);
            }
        }
        puts("");
        if (i == 2 || i == 5 || i == 8) {
            puts("");
        }
    }
}

void FOutputField()
{
    int i, j;
    FILE *outfile;
    outfile = fopen("sudoku_out", "w");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            fprintf(outfile, "%d", field[i][j]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);
}

int CheckCellXCellY()
{
    int x, y, i, j;
    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (field[y][x]) {
                for (j = 0; j < SIZE; j++) {
                    if (field[y][x] == field[y][j] && j != x) {
                        return 0;
                    }
                }
                for (i = 0; i < SIZE; i++) {
                    if (field[y][x] == field[i][x] && i != y) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int CheckBoxes()
{
    int i, j, k, ik, jk;
    int values[SIZE];
    for (i = 0; i < SIZE; i += 3) {
        for (j = 0; j < SIZE; j += 3) {
            for (k = 0; k < SIZE; k++) {
                values[k] = 0;
            }
            for (ik = i; ik < i + 3; ++ik) {
                for (jk = j; jk < j + 3; ++jk) {
                    if (!field[ik][jk]) {
                        continue;
                    }
                    if (!values[field[ik][jk] - 1]) {
                        values[field[ik][jk] - 1] = 1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int Check()
{
    if (CheckCellXCellY()) {
        if (CheckBoxes()) {
            return 1;
        }
    }
    return 0;
}

int SolveSudoku(int i, int j)
{
    int flag;
    int correct = 1;
    int current_value = 1;
    while (1) {
        if (j > 8) {
            i++;
            j = 0;
        }
        if (i == SIZE) {
            return 1;
        }

        if (current_value == 1 && field[i][j]) {
            flag = 1;
        } else {
            flag = 0;
        }

        if (current_value > SIZE) {
            field[i][j] = 0;
            return 0;
        }

        if (!flag) {
            field[i][j] = current_value;
        }

        if (Check()) {
            correct = SolveSudoku(i, j + 1);
        }
        if (!correct || !Check()) {
            current_value++;
            continue;
        }
        if (flag && !correct) {
            return 0;
        }
        return 1;
    }
}

int main()
{
    InputField();
    DisplaySudoku();
    if (Check()) {
        SolveSudoku(0, 0);
        DisplaySudoku();
        FOutputField();
    } else {
        puts("BAD SUDOKU! SORRY!");
    }
    return 0;
}
