/* Create a N*N Markov matrix.
   Check whether a N*N matrix is Markov. */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 10 /* max rows/columns */

void readSquare(float [][MAXN], int N);
int isMarkov(float [][MAXN], int N);
void parseMarkov(float [][MAXN], int N);
float sumRow(float [][MAXN], int N, int idx);
float sumColumn(float [][MAXN], int N, int idx);
void fillSquare(float [][MAXN], int N);
void printSquare(float [][MAXN], int N);
int invalidRow(float [][MAXN], int N, int idx);
int invalidColumn(float [][MAXN], int N, int idx);


int main(int argc, char **argv) {
    int N;
    float square[MAXN][MAXN];

    /* program argument -create: generate and print a Markov matrix that
       has 4 decimal digits */
    if (argc == 3) {
        if (strcmp(argv[1], "-create") == 0) {
            N = atoi(argv[2]);
            if (N > MAXN) {
                return 0;
            }
            srand(time(0));

            /* create a Markov matrix */
            fillSquare(square, N);
            while (!isMarkov(square, N)) {
                fillSquare(square, N);
            }
            printf("%d\n", N);
            printSquare(square, N);
        }
    }


    /* program argument -check: examine if a matrix is Markov */
    else if (argc == 2) {
        if (strcmp(argv[1], "-check") == 0) {
            scanf("%d", &N);
            if (N > MAXN) {
                return 0;
            }
            readSquare(square, N);
            parseMarkov(square, N);
            printf("MARKOV %s\n", isMarkov(square, N) ? "YES" : "NO");
        }
    }

    else {
        printf("a.out -create {positive integer number}\n");
    }
    return 0;
}

/* Reads a N*N matrix from stdin */
void readSquare(float square[][MAXN], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%f", &square[i][j]);
        }
    }
}

/* Checks whether a N*N matrix is a Markov matrix.
Returns: 1 if matrix is Markov, 0 otherwise. */
int isMarkov(float square[][MAXN], int N) {
    int i;

    for (i = 0; i < N; i++) {
        if (invalidRow(square, N, i) || invalidColumn(square, N, i)) {
            return 0;
        }
    }
    return 1;
}

/* For each row/column of a Markov matrix, it prints to stdout whether it
   is valid or not */
void parseMarkov(float square[][MAXN], int N) {
    int i;

    for (i = 0; i < N; i++) {
        printf("ROW %d %s\n", i + 1,
                invalidRow(square, N, i) ? "NO" : "YES");
    }
    for (i = 0; i < N; i++) {
        printf("COLUMN %d %s\n", i + 1,
                invalidColumn(square, N, i) ? "NO" : "YES");
    }
}

/* Returns the sum of entries of the row that has index idx */
float sumRow(float square[][MAXN], int N, int idx) {
    float sum = 0.0;
    int column;

    for (column = 0; column < N; column++) {
        sum += square[idx][column];
    }
    return sum;
}

/* Returns the sum of entries of the column that has index idx */
float sumColumn(float square[][MAXN], int N, int idx) {
    float sum = 0.0;
    int row;

    for (row = 0; row < N; row++) {
        sum += square[row][idx];
    }
    return sum;
}

/* Creates a random N*N Markov matrix */
void fillSquare(float square[][MAXN], int N) {
    int k, j;
    float Max, E, sumRowVal, sumColumnVal;

    /* arrays for the sum of each row/column */
    float sumRowVector[MAXN] = {0.0}, sumColumnVector[MAXN] = {0.0};

    /* initialize matrix to 0 */
    for (k = 0; k < N; k++) {
        for (j = 0; j < N; j++) {
            square[k][j] = 0.0;
        }
    }

    /* fill the matrix */
    for (k = 0; k < N; k++) {
        for (j = 0; j < N; j++) {
            sumRowVal = sumRow(square, N, k);
            sumColumnVal = sumColumn(square, N, j);
            Max = (sumRowVal > sumColumnVal) ? sumRowVal : sumColumnVal;
            if (k == N - 1) {
                E = 1 - sumColumnVal;
            }
            else if (j == N - 1) {
                E = 1 - sumRowVal;
            }
            else if (Max < 0.0001) {
                E = (float) rand() / RAND_MAX;
            }
            else {
                E = (1 - Max) * ((float) rand() / RAND_MAX);
            }
            
            /* 4 decimal digits */
            E = 0.0001 * ((int) (10000 * E));

            square[k][j] = E;
            sumRowVector[k] += E;
            sumColumnVector[j] += E;
        }
    }
}

/* Prints a N*N matrix to stdout */
void printSquare(float square[][MAXN], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.4f ", square[i][j]);
        }
        printf("\n");
    }
}

/* Checks whether the row that has index idx is a valid Markov matrix row.
Returns: 1 if row is valid, 0 otherwise. */
int invalidRow(float square[][MAXN], int N, int idx) {
    int column;
    float sumRowVal;

    for (column = 0; column < N; column++) {
        if (square[idx][column] < 0 || square[idx][column] > 1) {
            return 1;
        }
    }
    sumRowVal = sumRow(square, N, idx);
    return sumRowVal > 1.00001 || sumRowVal < 0.99999;
}

/* Checks whether column with index idx is a valid Markov matrix column.
Returns: 1 if column is valid, 0 otherwise. */
int invalidColumn(float square[][MAXN], int N, int idx) {
    int row;
    float sumColumnVal;

    for (row = 0; row < N; row++) {
        if (square[row][idx] < 0 || square[row][idx] > 1) {
            return 1;
        }
    }
    sumColumnVal = sumColumn(square, N, idx);
    return sumColumnVal > 1.00001 || sumColumnVal < 0.99999;
}