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

void rec1(int ppp, int end, bool firstnumber) {
    if (ppp > end) {
        if (firstnumber) {
            printf("В диапазоне нет избыточных чисел.\n");
        } else {
            printf("\n");
        }
        return;
    }
    if (func1(ppp)) {
        if (firstnumber) {
            printf("Цепочка избыточных чисел: ");
            printf("%d",ppp);
        } else {
            printf(" %d", ppp);
        }
        rec1(ppp + 1, end, false);
    } else {
        rec1(ppp + 1, end, firstnumber);
    }
}

void rec2(int ppp, int end) {
    if (ppp > end) {
        return;
    }
    if (func1(ppp)) {
        int sum = 0;
        printf("%d: делители ", ppp);
        
        bool first = true;
        for (int j = 1; j <= ppp / 2; j++) {
            if (ppp % j == 0) {
                if (!first) {
                    printf(", ");
                }
                printf("%d", j);
                sum += j;
                first = false;
            }
        }
        printf(" |сумма = %d > %d\n", sum, ppp);
    }
    rec2(ppp + 1, end);
}

bool func2(int N, int M) {
    if (N <= 0 || M <= 0) {
        printf("ERROR: числа должны быть натуральными (>0).\n");
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
    
    printf("\nДиапазон: от %d до %d\n", N, M);
    rec1(N, M, true);
    
    printf("Все избыточные числа в диапазоне:\n");
    rec2(N, M);
    return 0;
}
