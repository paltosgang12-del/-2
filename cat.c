#include "cat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void resize_database(Database *db);

Database* create_database(void) {
    Database *db = malloc(sizeof(Database));
    if (!db) return NULL;
    
    db->visitors = malloc(START_SIZE * sizeof(Visitor));
    if (!db->visitors) {
        free(db);
        return NULL;
    }
    
    db->count = 0;
    db->capacity = START_SIZE;
    db->next_id = 1;
    
    return db;
}

void free_database(Database *db) {
    if (db) {
        if (db->visitors) free(db->visitors);
        free(db);
    }
}

static void resize_database(Database *db) {
    if (!db) return;
    
    int new_capacity = db->capacity + GROW_BY;
    Visitor *new_array = realloc(db->visitors, new_capacity * sizeof(Visitor));
    
    if (!new_array) return;
    
    db->visitors = new_array;
    db->capacity = new_capacity;
}

void load_data(Database *db, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;
    
    Visitor temp;
    int loaded = 0;
    
    while (fread(&temp, sizeof(Visitor), 1, file) == 1) {
        if (db->count >= db->capacity) resize_database(db);
        
        db->visitors[db->count] = temp;
        db->count++;
        loaded++;
    }
    
    fclose(file);
    
    if (loaded > 0) {
        int max_id = db->visitors[0].id;
        for (int i = 1; i < db->count; i++) {
            if (db->visitors[i].id > max_id) max_id = db->visitors[i].id;
        }
        db->next_id = max_id + 1;
    }
}

void save_data(const Database *db, const char *filename) {
    if (!db || db->count == 0) return;
    
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    
    fwrite(db->visitors, sizeof(Visitor), db->count, file);
    fclose(file);
}

void show_all(const Database *db) {
    if (!db || db->count == 0) {
        printf("База данных пуста\n");
        return;
    }
    
    printf("\nВсего посетителей: %d\n\n", db->count);
    
    for (int i = 0; i < db->count; i++) {
        const Visitor *v = &db->visitors[i];
        printf("Посетитель #%d\n", i + 1);
        printf("ID: %d\n", v->id);
        printf("Имя: %s\n", v->name);
        printf("Кот: %s\n", v->cat_name);
        printf("Время: %d минут\n", v->minutes);
        printf("Сумма: %.2f руб.\n", v->money);
        printf("Напиток: %s\n", v->drink);
        printf("Постоянный: %s\n\n", v->is_regular ? "Да" : "Нет");
    }
}

void add_visitor(Database *db) {
    if (!db) return;
    
    if (db->count >= db->capacity) resize_database(db);
    
    Visitor *new = &db->visitors[db->count];
    new->id = db->next_id++;
    
    printf("Имя посетителя: ");
    fgets(new->name, MAX_NAME, stdin);
    new->name[strcspn(new->name, "\n")] = '\0';
    
    printf("Имя кота: ");
    fgets(new->cat_name, MAX_CAT_NAME, stdin);
    new->cat_name[strcspn(new->cat_name, "\n")] = '\0';
    
    printf("Время (минут): ");
    scanf("%d", &new->minutes);
    clear_input_buffer();
    
    printf("Сумма (руб): ");
    scanf("%f", &new->money);
    clear_input_buffer();
    
    printf("Напиток: ");
    fgets(new->drink, MAX_DRINK, stdin);
    new->drink[strcspn(new->drink, "\n")] = '\0';
    
    printf("Постоянный (1-Да, 0-Нет): ");
    scanf("%d", &new->is_regular);
    clear_input_buffer();
    
    db->count++;
    
    printf("Добавлен посетитель ID: %d\n", new->id);
}

int delete_visitor(Database *db, int id) {
    if (!db || db->count == 0) return 0;
    
    int index = find_by_id(db, id);
    if (index == -1) return 0;
    
    printf("Удалить посетителя ID %d? (1-Да, 0-Нет): ", id);
    int confirm;
    scanf("%d", &confirm);
    clear_input_buffer();
    
    if (confirm != 1) return 0;
    
    for (int i = index; i < db->count - 1; i++) {
        db->visitors[i] = db->visitors[i + 1];
    }
    
    db->count--;
    return 1;
}

int edit_visitor(Database *db, int id) {
    int index = find_by_id(db, id);
    if (index == -1) return 0;
    
    Visitor *v = &db->visitors[index];
    
    printf("Текущие данные ID %d:\n", id);
    printf("Имя: %s\n", v->name);
    printf("Кот: %s\n", v->cat_name);
    printf("Время: %d мин\n", v->minutes);
    printf("Сумма: %.2f руб\n", v->money);
    printf("Напиток: %s\n", v->drink);
    printf("Постоянный: %s\n", v->is_regular ? "Да" : "Нет");
    
    char input[100];
    
    printf("\nНовые данные (Enter - оставить старое):\n");
    
    printf("Имя [%s]: ", v->name);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        strncpy(v->name, input, MAX_NAME - 1);
        v->name[MAX_NAME - 1] = '\0';
    }
    
    printf("Кот [%s]: ", v->cat_name);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        strncpy(v->cat_name, input, MAX_CAT_NAME - 1);
        v->cat_name[MAX_CAT_NAME - 1] = '\0';
    }
    
    printf("Время (%d мин) [0-не менять]: ", v->minutes);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        int new_time = atoi(input);
        if (new_time > 0) v->minutes = new_time;
    }
    
    printf("Сумма (%.2f руб) [-1-не менять]: ", v->money);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        float new_money = atof(input);
        if (new_money >= 0) v->money = new_money;
    }
    
    printf("Напиток [%s]: ", v->drink);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        strncpy(v->drink, input, MAX_DRINK - 1);
        v->drink[MAX_DRINK - 1] = '\0';
    }
    
    printf("Постоянный (%s) [-1-не менять]: ", v->is_regular ? "Да" : "Нет");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        int reg = atoi(input);
        if (reg == 0 || reg == 1) v->is_regular = reg;
    }
    
    printf("Данные обновлены\n");
    return 1;
}

int find_by_id(const Database *db, int id) {
    if (!db) return -1;
    
    for (int i = 0; i < db->count; i++) {
        if (db->visitors[i].id == id) return i;
    }
    
    return -1;
}

void search_by_name(const Database *db) {
    if (!db || db->count == 0) {
        printf("База данных пуста\n");
        return;
    }
    
    char query[MAX_NAME];
    printf("Введите имя для поиска: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';
    
    printf("Результаты поиска:\n");
    
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->visitors[i].name, query) != NULL) {
            printf("\nНайден посетитель:\n");
            printf("ID: %d\n", db->visitors[i].id);
            printf("Имя: %s\n", db->visitors[i].name);
            printf("Кот: %s\n", db->visitors[i].cat_name);
            found++;
        }
    }
    
    if (found == 0) printf("Ничего не найдено\n");
}

void search_by_cat(const Database *db) {
    if (!db || db->count == 0) {
        printf("База данных пуста\n");
        return;
    }
    
    char query[MAX_CAT_NAME];
    printf("Введите имя кота для поиска: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';
    
    printf("Результаты поиска:\n");
    
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->visitors[i].cat_name, query) != NULL) {
            printf("\nКот %s был с:\n", db->visitors[i].cat_name);
            printf("Имя посетителя: %s\n", db->visitors[i].name);
            printf("ID: %d\n", db->visitors[i].id);
            found++;
        }
    }
    
    if (found == 0) printf("Ничего не найдено\n");
}

void search_by_drink(const Database *db) {
    if (!db || db->count == 0) {
        printf("База данных пуста\n");
        return;
    }
    
    char query[MAX_DRINK];
    printf("Введите напиток для поиска: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';
    
    printf("Результаты поиска:\n");
    
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->visitors[i].drink, query) != NULL) {
            printf("\n%s (ID: %d)\n", db->visitors[i].name, db->visitors[i].id);
            printf("Любимый напиток: %s\n", db->visitors[i].drink);
            found++;
        }
    }
    
    if (found == 0) printf("Ничего не найдено\n");
}

void show_statistics(const Database *db) {
    if (!db || db->count == 0) {
        printf("Нет данных для статистики\n");
        return;
    }
    
    float total_money = 0.0f;
    int total_time = 0;
    int regulars = 0;
    
    for (int i = 0; i < db->count; i++) {
        total_money += db->visitors[i].money;
        total_time += db->visitors[i].minutes;
        if (db->visitors[i].is_regular) regulars++;
    }
    
    printf("Статистика:\n");
    printf("Всего посетителей: %d\n", db->count);
    printf("Постоянных клиентов: %d\n", regulars);
    printf("Общая выручка: %.2f руб.\n", total_money);
    printf("Общее время: %d ч. %d мин.\n", total_time / 60, total_time % 60);
    printf("Средний чек: %.2f руб.\n", total_money / db->count);
    printf("Среднее время: %.1f мин.\n", (float)total_time / db->count);
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
