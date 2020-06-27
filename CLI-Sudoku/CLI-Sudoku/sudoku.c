#include <stdio.h>
#include <stdint.h>

#include "sudoku.h"

typedef enum {
    false,
    true
}bool;

void main();
void updateplot();
void checkSquare();
void checkLine();
void checkColumn();
void checkPlot();
void insertNumber();

int mysudoku[9][9];
char* NumberColor = ANSI_COLOR_RESET;

bool boxcheck = false;
bool linecheck = false;
bool columncheck = false;

void main() {
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            mysudoku[j][i] = i + 1;
        }
    }
    checkPlot();
    updateplot();
    while (true) {
        insertNumber();
        checkPlot();
        updateplot();
        if (boxcheck && linecheck && columncheck) {
            break;
        }
    }
    printf("You have sucessfully solved this puzzle!");
}

void checkPlot() {
    checkSquare();
    checkLine();
    checkColumn();
}

void checkSquare() {
    uint16_t flagmapsmall = 0;
    uint16_t flagmapbig = 0;

    for (int i = 0; i < 9; i++) {
        flagmapsmall = 0;
        for (int j = 0; j < 9; j++) {
            flagmapsmall |= 1 << mysudoku[i][j] - 1;
        }
        if (flagmapsmall == 511) {
            flagmapbig |= 1 << i;
        }
    }
    if (flagmapbig == 511) {
        boxcheck = true;
    }
    else {
        boxcheck = false;
    }
}

void checkLine() {
    uint16_t flagmapsmall = 0;
    uint16_t flagmapbig = 0;
    uint16_t someoffset = 0;
    uint8_t smallmapcounter = 0;

    for (int n = 0; n < 3; n++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    flagmapsmall |= 1 << mysudoku[0][someoffset] - 1;
                    someoffset++;
                }
                someoffset += 6;
            }
            if (flagmapsmall == 511) {
                flagmapbig |= 1 << smallmapcounter;
            }
            flagmapsmall = 0;
            smallmapcounter++;
            someoffset -= 24;
        }
        someoffset += 18;
    }
    if (flagmapbig == 511) {
        linecheck = true;
    }
    else {
        linecheck = false;
    }
}

void checkColumn() {
    uint16_t flagmapsmall = 0;
    uint16_t flagmapbig = 0;
    uint16_t someoffset = 0;
    uint8_t smallmapcounter = 0;

    for (int n = 0; n < 3; n++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    flagmapsmall |= 1 << mysudoku[0][someoffset] - 1;
                    someoffset += 3;
                }
                someoffset += 18;
            }
            if (flagmapsmall == 511) {
                flagmapbig |= 1 << smallmapcounter;
            }
            flagmapsmall = 0;
            smallmapcounter++;
            someoffset -= 80;
        }
        someoffset += 6;
    }
    if (flagmapbig == 511) {
        linecheck = true;
    }
    else {
        linecheck = false;
    }
}

void insertNumber() {
    int inputnum;
    int bigblock;
    int smallblock;
    printf("Enter input number: ");
    scanf_s("%d", &inputnum);
    while (inputnum < 1 || inputnum > 9) {
        printf("The number must be from 1 to 9: ");
        scanf_s("%d", &inputnum);
    }
    printf("Enter the big block number: ");
    scanf_s("%d", &bigblock);
    while (bigblock < 1 || bigblock > 9) {
        printf("The number must be from 1 to 9: ");
        scanf_s("%d", &bigblock);
    }
    printf("Enter the small block number: ");
    scanf_s("%d", &smallblock);
    while (smallblock < 1 || smallblock > 9) {
        printf("The number must be from 1 to 9: ");
        scanf_s("%d", &smallblock);
    }
    mysudoku[bigblock - 1][smallblock - 1] = inputnum;
}

void updateplot() {
    printf(ANSI_COLOR_RED"-------------------------------------\n");
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[0][0], mysudoku[0][1], mysudoku[0][2], NumberColor, mysudoku[1][0], mysudoku[1][1], mysudoku[1][2], NumberColor, mysudoku[2][0], mysudoku[2][1], mysudoku[2][2]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[0][3], mysudoku[0][4], mysudoku[0][5], NumberColor, mysudoku[1][3], mysudoku[1][4], mysudoku[1][5], NumberColor, mysudoku[2][3], mysudoku[2][4], mysudoku[2][5]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[0][6], mysudoku[0][7], mysudoku[0][8], NumberColor, mysudoku[1][6], mysudoku[1][7], mysudoku[1][8], NumberColor, mysudoku[2][6], mysudoku[2][7], mysudoku[2][8]);
    printf(BORDER_COLOR"-------------------------------------\n");
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[3][0], mysudoku[3][1], mysudoku[3][2], NumberColor, mysudoku[4][0], mysudoku[4][1], mysudoku[4][2], NumberColor, mysudoku[5][0], mysudoku[5][1], mysudoku[5][2]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[3][3], mysudoku[3][4], mysudoku[3][5], NumberColor, mysudoku[4][3], mysudoku[4][4], mysudoku[4][5], NumberColor, mysudoku[5][3], mysudoku[5][4], mysudoku[5][5]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[3][6], mysudoku[3][7], mysudoku[3][8], NumberColor, mysudoku[4][6], mysudoku[4][7], mysudoku[4][8], NumberColor, mysudoku[5][6], mysudoku[5][7], mysudoku[5][8]);
    printf(BORDER_COLOR"-------------------------------------\n");
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[6][0], mysudoku[6][1], mysudoku[6][2], NumberColor, mysudoku[7][0], mysudoku[7][1], mysudoku[7][2], NumberColor, mysudoku[8][0], mysudoku[8][1], mysudoku[8][2]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[6][3], mysudoku[6][4], mysudoku[6][5], NumberColor, mysudoku[7][3], mysudoku[7][4], mysudoku[7][5], NumberColor, mysudoku[8][3], mysudoku[8][4], mysudoku[8][5]);
    printf(BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-""%s""-----------"BORDER_COLOR"-\n", NumberColor, NumberColor, NumberColor);
    printf(BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|""%s"" %d | %d | %d "BORDER_COLOR"|"ANSI_COLOR_RESET"\n",
        NumberColor, mysudoku[6][6], mysudoku[6][7], mysudoku[6][8], NumberColor, mysudoku[7][6], mysudoku[7][7], mysudoku[7][8], NumberColor, mysudoku[8][6], mysudoku[8][7], mysudoku[8][8]);
    printf(BORDER_COLOR"-------------------------------------\n"ANSI_COLOR_RESET);
}