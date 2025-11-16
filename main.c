#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long bubble_swaps = 0, bubble_comparisons = 0;
long long insertion_swaps = 0, insertion_comparisons = 0;
long long merge_swaps = 0, merge_comparisons = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void puzir(int arr[], int n) {
    bubble_swaps = 0;
    bubble_comparisons = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            bubble_comparisons++;
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                bubble_swaps++;
            }
        }
    }
}

void vstavka(int arr[], int n) {
    insertion_swaps = 0;
    insertion_comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        insertion_comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            insertion_swaps++;
            insertion_comparisons++;
            j--;
        }
        arr[j + 1] = key;
        if (j + 1 != i) insertion_swaps++;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        merge_comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        merge_swaps++;
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        merge_swaps++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        merge_swaps++;
    }
    
    free(L);
    free(R);
}

void sliyanie(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sliyanie(arr, left, mid);
        sliyanie(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int n) {
    merge_swaps = 0;
    merge_comparisons = 0;
    sliyanie(arr, 0, n - 1);
}

int* copyArray(int original[], int n) {
    int *copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    memcpy(copy, original, n * sizeof(int));
    return copy;
}

int* generateRandomArray(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int isSorted(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i+1]) {
            return 0;
        }
    }
    return 1;
}

void testSort(void (*sortFunc)(int[], int), int arr[], int n,
              const char* sortName, double *time_taken,
              long long *swaps, long long *comparisons) {
    int *testArr = copyArray(arr, n);
    clock_t start = clock();
    sortFunc(testArr, n);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        *time_taken = seconds;
        if (strcmp(sortName, "Пузырьком") == 0) {
            *swaps = bubble_swaps;
            *comparisons = bubble_comparisons;
        }
        else if (strcmp(sortName, "Вставками") == 0) {
            *swaps = insertion_swaps;
            *comparisons = insertion_comparisons;
        }
        else if (strcmp(sortName, "Слиянием") == 0) {
            *swaps = merge_swaps;
            *comparisons = merge_comparisons;
        }
        if (!isSorted(testArr, n)) {
            printf("ERROR: массив не отсортирован для %s!\n", sortName);
        }
        
        free(testArr);
    }

    void printTableHeader(void) {
        printf("\n┌─────────────┬────────────┬──────────────┬────────────┬───────────────┬────────-────┐\n");
        printf("│ Размер      │ Алгоритм   │ Время(сек)   │Перестановки│   Сравнения   │Эффективность│\n");
        printf("├─────────────┼────────────┼──────────────┼────────────┼───────────────┼───────────-─┤\n");
    }

    void printTableRow(int size, const char* algorithm, double time,
                      long long swaps, long long comparisons, int sorted) {
        printf("│ %-11d │ %-10s  │ %-12.6f │ %-10lld │ %-13lld │",
               size, algorithm, time, swaps, comparisons);
        if (time < 0.001) printf(" ТОП!        │\n");
        else if (time < 0.01) printf(" Отлично     │\n");
        else if (time < 0.1) printf(" Нормально   │\n");
        else if (time < 1.0) printf(" Пойдет      │\n");
        else if (time < 10.0) printf(" Плохо    │\n");
        else printf(" Ужасно     │\n");
    }

    void printTableFooter(void) {
        printf("└─────────────┴────────────┴──────────────┴────────────┴───────────────┴────-────────┘\n");
    }
    int main(void) {
        srand(time(NULL));
        int sizes[] = {10, 1000, 10000, 100000};
        int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
        double times[3][4];
        long long swaps[3][4];
        long long comparisons[3][4];
        printf("                           LABA №4 'CHTO-TO PRO SORTIROVKU'\n");
            printf("=====================================================================================\n");
        for (int i = 0; i < num_sizes; i++) {
            int n = sizes[i];
            printf("\nТест на массиве размером %d элементов:\n", n);
            int *originalArray = generateRandomArray(n);
            printTableHeader();
            if (n <= 10000) {
                testSort(puzir, originalArray, n, "Пузырьком",
                        &times[0][i], &swaps[0][i], &comparisons[0][i]);
                printTableRow(n, "Пузырьком", times[0][i], swaps[0][i], comparisons[0][i], 1);
            } else {
                times[0][i] = -1;
                swaps[0][i] = -1;
                comparisons[0][i] = -1;
                printf("│ %-11d │ %-10s  │ %-12s    │ %-10s │ %-13s │ %-12s │\n",
                       n, "Пузырьком", ">60 сек", "N/A", "N/A", "Ужасно     ");
            }
            if (n <= 10000) {
                testSort(vstavka, originalArray, n, "Вставками",
                        &times[1][i], &swaps[1][i], &comparisons[1][i]);
                printTableRow(n, "Вставками", times[1][i], swaps[1][i], comparisons[1][i], 1);
            } else {
                times[1][i] = -1;
                swaps[1][i] = -1;
                comparisons[1][i] = -1;
                printf("│ %-11d │ %-10s  │ %-12s    │ %-10s │ %-13s │ %-12s │\n",
                       n, "Вставками", ">60 сек", "N/A", "N/A", "Ужасно     ");
            }
            
            testSort(mergeSort, originalArray, n, "Слиянием",
                     &times[2][i], &swaps[2][i], &comparisons[2][i]);
                             printTableRow(n, "Слиянием ", times[2][i], swaps[2][i], comparisons[2][i], 1);
                             printTableFooter();
                             free(originalArray);
                             printf("\n");
                             printf("=====================================================================================\n");
            
                         }
                         printf("\n                SRAVNENIE\n");
                         printf("============================================\n");
                         printf("\nЛучшие результаты по времени выполнения:\n");
                         printf("┌─────────────┬────────────┬──────────────┐\n");
                         printf("│ Размер      │ Алгоритм   │ Время(сек)   │\n");
                         printf("├─────────────┼────────────┼──────────────┤\n");
                         
                         for (int i = 0; i < num_sizes; i++) {
                             int n = sizes[i];
                             double min_time = __DBL_MAX__;
                             const char* best_algo = "";
                             for (int j = 0; j < 3; j++) {
                                 if (times[j][i] > 0 && times[j][i] < min_time) {
                                     min_time = times[j][i];
                                     if (j == 0) best_algo = "Пузырьком";
                                     else if (j == 1) best_algo = "Вставками";
                                     else best_algo = "Слиянием ";
                                 }
                             }
                             printf("│ %-11d │ %-10s  │  %-12.6f│\n", n, best_algo, min_time);
                         }
                         printf("└─────────────┴────────────┴──────────────┘\n");
                         printf("\n=============================================\n");
    
                         printf("\nСравнение количества операций (для размера 10000):\n");
                         printf("┌────────────┬──────────────┬───────────────┐\n");
                         printf("│ Алгоритм   │ Перестановки │ Сравнения     │\n");
                         printf("├────────────┼──────────────┼───────────────┤\n");
                         printf("│ Пузырьком  │ %-12lld | %-13lld │\n", swaps[0][2], comparisons[0][2]);
                         printf("│ Вставками  │ %-12lld │ %-13lld │\n", swaps[1][2], comparisons[1][2]);
                         printf("│ Слиянием   │ %-12lld │ %-13lld │\n", swaps[2][2], comparisons[2][2]);
                         printf("└────────────┴──────────────┴───────────────┘\n");
                         
                         printf("\n=============================================\n");
                         
                         printf("\n                   ITOGI:\n");
                         printf("=============================================\n");
        
                         printf("\nСортировка СЛИЯНИЕМ - эффективна на больших массивах\n");
                         printf("Сортировка ПУЗЫРЬКОМ - простая, но очень медленная\n");
                         printf("Сортировка ВСТАВКАМИ - эффективна на небольших массивах\n");
                         
                         return 0;
                     }
