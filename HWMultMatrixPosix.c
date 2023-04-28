#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int **matrix_a;
int **matrix_b;
int **result;
int row_a, col_a, row_b, col_b, max_cols;

void *FirstThread() {
    for (int row=0; row<row_a; ++row) {
        if (row%2 != 1) {
            for (int col=0;col<col_b;++col) {
                for (int i=0; i<max_cols;++i) {
                    result[row][col] += matrix_a[row][i] * matrix_b[i][col];
                }
            }   
        }
    }
}

void *SecondThread() {
    for (int row=0; row<row_a; ++row) {
        if (row%2 == 1) {
            for (int col=0;col<col_b;++col) {
                for (int i=0;i<max_cols;++i) {
                    result[row][col] += matrix_a[row][i] * matrix_b[i][col];
                }
            }
        }
    }
}

#define NUM_THREADS 2

int main () {
    //Create first matrix
    printf("Enter rows of first matrix:\n");
    scanf("%i", &row_a);
    printf("Enter cols of first matrix:\n");
    scanf("%i", &col_a);
    matrix_a = (int**)malloc(row_a*sizeof(int*));
    for (int i=0;i<row_a;++i) {
        matrix_a[i] = (int*)malloc(col_a*sizeof(int));
    }
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < row_a; ++i) {
        for (int j = 0; j < col_a; ++j) {
            printf("Matrix A [%i][%i] = ", i, j);
            scanf("%i", &matrix_a[i][j]);
        }
    }
    printf("\n*********************************\n");
    printf("Matrix A:\n");
    for (int i=0;i<row_a;++i) {
        for (int j=0;j<col_a;++j) {
            printf("%d\t",matrix_a[i][j]);
        }
        printf("\n");
    }

    //Create second matrix
    printf("\n*********************************\n");
    printf("Enter rows of second matrix:\n");
    scanf("%i", &row_b);
    printf("Enter cols of second matrix:\n");
    scanf("%i", &col_b);
    matrix_b = (int**)malloc(row_b*sizeof(int*));
    for (int i=0;i<row_b;++i) {
        matrix_b[i] = (int*)malloc(col_b*sizeof(int));
    }
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < row_b; ++i) {
        for (int j = 0; j < col_b; ++j) {
            printf("Matrix B [%i][%i] = ", i, j);
            scanf("%i", &matrix_b[i][j]);
        }
    }
    printf("\n*********************************\n");
    printf("Matrix B:\n");
    for (int i=0;i<row_b;++i) {
        for (int j=0;j<col_b;++j) {
            printf("%d\t",matrix_b[i][j]);
        }
        printf("\n");
    }
        if (col_a != row_b) {
        printf("\nError!\nThe number of matrix row elements is not equal to the number of column elements of the second matrix.\nMultiplication is impossible\n");
        return 0;
    }

    max_cols = col_a;
    //Create result matrix
    result = (int**)malloc(row_a*sizeof(int*));
    for (int i=0;i<row_a;++i) {
        result[i] = (int*)malloc(col_b*sizeof(int));
    }

    pthread_t th1,th2;
    if (pthread_create(&th1,NULL,&FirstThread,NULL) != 0) {
        printf("Error! Can't create first thread\n");
        return 0;
    }
    if (pthread_create(&th2,NULL,&SecondThread,NULL) != 0) {
        printf("Error! Can't create second thread\n");
        return 0;
    }
    if (pthread_join(th1,NULL) != 0) {
        printf("Error! Can't join first thread\n");
        return 0;
    }
    if (pthread_join(th2,NULL) != 0) {
        printf("Error! Can't join second thread\n");
        return 0;
    }
    printf("\n*********************************\n");
    printf("Result of multiplication of matrix:\n");
    for (int i=0;i<row_a;++i) {
        for (int j=0;j<col_b;++j) {
            printf("%d\t",result[i][j]);
        }
        printf("\n");
    }
    printf("\n*********************************\n");
    //Delete matrix from memory
    for(int i = 0; i < row_a; ++i) free(matrix_a[i]);
    free(matrix_a);
    for(int i = 0; i < row_b; ++i) free(matrix_b[i]);
    free(matrix_b);
    for(int i = 0; i < row_a; ++i) free(result[i]);
    free(result);
    return 0;
}