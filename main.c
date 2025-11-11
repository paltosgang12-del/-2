#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int** readMatrix(const char* filename, int* N, int* M) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Не удалось открыть файл %s\n", filename);
        exit(1);
    }
    if (fscanf(file, "%d %d", N, M) != 2) {
        printf("ERROR: Неверный формат размеров матрицы\n");
        fclose(file);
        exit(1);
    }

    int** matrix = (int**)malloc(*N * sizeof(int*));
    if (matrix == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < *N; i++) {
        matrix[i] = (int*)malloc(*M * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fclose(file);
            exit(1);
        }
    }

    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *M; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("ERROR: Неверный формат данных в файле\n");
                for (int k = 0; k < *N; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                fclose(file);
                exit(1);
            }
        }
    }
    fclose(file);
    return matrix;
}

void printMatrix(int** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    int N, M;
    int** matrix = readMatrix(filename, &N, &M);
    printf("Исходная матрица:\n");
    printMatrix(matrix, N, M);
    printf("\n");

    int product = 1;
    int diagSize = (N < M) ? N : M;
    for (int i = 0; i < diagSize; i++) {
        product *= matrix[i][i];
    }
    printf("Произведение элементов главной диагонали: %d\n \n", product);

    if (N < 3) {
        printf("ERROR: Матрица должна иметь >=3 строк\n");
        freeMatrix(matrix, N);
        return 1;
    }
    
    int minElement = INT_MAX;
    int minCol = 0;
    for (int j = 0; j < M; j++) {
        if (matrix[2][j] < minElement) {
            minElement = matrix[2][j];
            minCol = j;
        }
    }
    printf("Минимальный элемент в третьей строке: %d\n \n", minElement);

    int temp = matrix[2][minCol];
    matrix[2][minCol] = product;
    printf("Матрица после замены:\n");
    printMatrix(matrix, N, M);

    freeMatrix(matrix, N);
    return 0;
}
