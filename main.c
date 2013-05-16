#include <stdio.h>
#include <stdlib.h>

#define size 9

int field[size][size];

void input_field()
{
    FILE* infile;
    infile=fopen("sudoku_in","r");
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++)
            field[i][j]=getc(infile)-'0';
        getc(infile);
    }
    fclose(infile);
}

void output_field()
{
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++)
            printf("%d",field[i][j]);
        puts("");
    }
}

void foutput_field()
{
    FILE* outfile;
    outfile=fopen("sudoku_out","w");
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fprintf(outfile, "%d", field[i][j]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);
}



int main()
{
    input_field();
    output_field();
    foutput_field();
    return 0;
}
