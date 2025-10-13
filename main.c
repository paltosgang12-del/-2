#include <stdio.h>
#include <stdbool.h>

bool func1(int num) {
    if (num < 1) return false;
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum > num;
}

void rec(int start, int end, bool ppp) {
    if (start > end) {
        if (!ppp) {
            printf("В диапазоне нет избыточных чисел.\n");
        }
        return;
    }
    
    if (func1(start)) {
        if (!ppp) {
            printf("Цепочка избыточных чисел: ");
            ppp = true;
        }
        printf("%d ", start);
        
        rec(start + 1, end, ppp);
    } else {
        if (ppp) {
            printf("\n");
            return;
        } else {
            rec(start + 1, end, ppp);
        }
    }
}

bool func2(int N, int M) {
    if (N <= 0 || M <= 0) {
        printf("ERROR: числа должны быть натуральными.\n");
        return false;
    }
    if (N > M) {
        printf("ERROR: первое число должно быть <= второму.\n");
        return false;
    }
    return true;
}

int main() {
    int N, M;
    printf("Введите натуральное число N: ");
    if (scanf("%d", &N) != 1) {
        printf("ERROR: некорректное N.\n");
        return 1;
    }
    printf("Введите натуральное число M: ");
    if (scanf("%d", &M) != 1) {
        printf("ERROR: некорректное M.\n");
        return 1;
    }
    if (!func2(N, M)) {
        return 1;
    }
    
    rec(N, M, false);
    printf("\n\nИзбыточные числа в диапазоне:\n");
    for (int i = N; i <= M; i++) {
        if (func1(i)) {
            int sum = 0;
            printf("%d: делители ", i);
            for (int j = 1; j <= i / 2; j++) {
                if (i % j == 0) {
                    printf("%d", j);
                    sum += j;
                    if (j < i / 2) printf(", ");
                }
            }
            printf(" | сумма = %d > %d\n", sum, i);
        }
    }
    return 0;
}
