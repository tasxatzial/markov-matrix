/* Functionality:
   1. Create a N*N Markov matrix (N <= 10)
   2. Check whether a N*N matrix is Markov (N <= 10) */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAXN 10 /* max rows, columns */
#define THRESHOLD 1e-12

void readSquare(double [][MAXN], int N);
int isMarkov(double [][MAXN], int N);
void parseMarkov(double [][MAXN], int N);
double sumRow(double [][MAXN], int N, int idx);
double sumColumn(double [][MAXN], int N, int idx);
void fillSquare(double [][MAXN], int N);
void printSquare(double [][MAXN], int N);
int invalidRow(double [][MAXN], int N, int idx);
int invalidColumn(double [][MAXN], int N, int idx);


int main(int argc, char **argv) {
    int N;
    double square[MAXN][MAXN];

    /* program argument -create: generate and print a Markov matrix */
    if (argc == 3) {
        if (strcmp(argv[1], "-create") == 0) {
            N = atoi(argv[2]);
            if (N > MAXN || N <= 0) {
                printf("%d: dimensions out of bounds\n", N);
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
            if (N > MAXN || N <= 0) {
                printf("%d: dimensions out of bounds\n", N);
                return 0;
            }
            readSquare(square, N);
            parseMarkov(square, N);
            printf("MARKOV %s\n", isMarkov(square, N) ? "YES" : "NO");
        }
    }

    else {
        printf("Create matrix (max N = 10):\n./markov -create <N>\n");
        printf("Check matrix:\n./markov -check < input_file\n");
    }
    return 0;
}

/* Reads a N*N matrix from stdin */
void readSquare(double square[][MAXN], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%lf", &square[i][j]);
        }
    }
}

/* Checks whether a N*N matrix is a Markov matrix.
Returns: 1 if matrix is Markov, 0 otherwise. */
int isMarkov(double square[][MAXN], int N) {
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
void parseMarkov(double square[][MAXN], int N) {
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
double sumRow(double square[][MAXN], int N, int idx) {
    double sum = 0.0;
    int column;

    for (column = 0; column < N; column++) {
        sum += square[idx][column];
    }
    return sum;
}

/* Returns the sum of entries of the column that has index idx */
double sumColumn(double square[][MAXN], int N, int idx) {
    double sum = 0.0;
    int row;

    for (row = 0; row < N; row++) {
        sum += square[row][idx];
    }
    return sum;
}

/* Creates a random N*N Markov matrix */
void fillSquare(double square[][MAXN], int N) {
    int k, j;
    double Max, E, sumRowVal, sumColumnVal;

    /* arrays for the sum of each row/column */
    double sumRowVector[MAXN] = {0.0}, sumColumnVector[MAXN] = {0.0};

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
            else if (Max < DBL_MIN) {
                E = (double) rand() / RAND_MAX;
            }
            else {
                E = (1 - Max) * ((double) rand() / RAND_MAX);
            }

            square[k][j] = E;
            sumRowVector[k] += E;
            sumColumnVector[j] += E;
        }
    }
}

/* Prints a N*N matrix to stdout */
void printSquare(double square[][MAXN], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", square[i][j]);
        }
        printf("\n");
    }
}

/* Checks whether the row that has index idx is a valid Markov matrix row.
Returns: 1 if row is valid, 0 otherwise. */
int invalidRow(double square[][MAXN], int N, int idx) {
    int column;
    double sumRowVal;

    for (column = 0; column < N; column++) {
        if (square[idx][column] < 0 || square[idx][column] > 1) {
            return 1;
        }
    }
    sumRowVal = sumRow(square, N, idx);
    return fabs(sumRowVal - 1) > THRESHOLD;
}

/* Checks whether column with index idx is a valid Markov matrix column.
Returns: 1 if column is valid, 0 otherwise. */
int invalidColumn(double square[][MAXN], int N, int idx) {
    int row;
    double sumColumnVal;

    for (row = 0; row < N; row++) {
        if (square[row][idx] < 0 || square[row][idx] > 1) {
            return 1;
        }
    }
    sumColumnVal = sumColumn(square, N, idx);
    return fabs(sumColumnVal - 1) > THRESHOLD;
}
