#include <stdio.h>
#include <stdlib.h>

#define SIZE 9
int field[SIZE][SIZE];

void InputField()
{
    FILE *infile;
    infile = fopen("sudoku_in", "r");
    int i, j;
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
            }
            else {
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
    FILE *outfile;
    outfile = fopen("sudoku_out", "w");
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            fprintf(outfile, "%d", field[i][j]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);
}

int CheckStrings()
{
    int i, j, k;
    int values[SIZE];
    for (i = 0; i < SIZE; ++i) {        
        for (k = 0; k < SIZE; k++) {
            values[k] = 0;       
        }
        for (j = 0; j < SIZE; ++j) {
            if (!field[i][j]) {
                continue;
            }
            if (!values[field[i][j] - 1]) {
                values[field[i][j] - 1] = 1;
            }
            else {
                return 1;
            }
        }
    }
    return 0;
}

int CheckColumns()
{
    int j, i, k;
    int values[SIZE];
    for (j = 0; j < SIZE; ++j) {        
        for (k = 0; k < SIZE; k++) {
            values[k] = 0;
        }
        for (i = 0; i < SIZE; ++i) {
            if (!field[i][j]) {
                continue;
            }
            if (!values[field[i][j] - 1]) {
                values[field[i][j] - 1] = 1;
            }
            else {
                return 1;
            }
        }
    }
    return 0;
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
                    }
                    else {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int SolveSudoku(int i, int j)
{
    int n = 1;
    if (j == 9) {
        j = 0;
        i++;
    }
    if (i == 9) {
        return 0;
    }
    while (1) {
        if (field[i][j]) {            
            if ((j + 1) >= SIZE) {
                i++;
                j = 0;
            } 
            else {
                j++;
            }
        }
        else {
            break;
        }    
    }
    while (1) {
        while (1) {
            field[i][j] = n;
            n++;
            if (!CheckStrings()) {
                if (!CheckColumns()) {
                    if (!CheckBoxes()) {
                        break;
                    }
                }
            }
            if (n >= 10) {
                field[i][j] = 0;
                return 1;
            }
        }
        if (!SolveSudoku(i, (j + 1))) {
            return 0;
        }
    }
}

int main()
{
    InputField();
    DisplaySudoku();
    if (!SolveSudoku(0, 0)) {
        DisplaySudoku();
        FOutputField();
    } else {
        puts("BAD SUDOKU! SORRY!");
    }
    return 0;
}