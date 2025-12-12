#include "cat.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "catcafe.dat"

void print_menu(void);
void search_menu(Database *db);
void wait_for_enter(void);

int main(void) {
    printf("\nБаза данных котокафе\n");
    
    Database *db = create_database();
    if (!db) {
        printf("Ошибка создания базы данных\n");
        return 1;
    }
    
    load_data(db, DATA_FILE);
    
    int choice;
    int id_input;
    
    do {
        print_menu();
        printf("Выберите: ");
        
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Ошибка ввода\n");
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                show_all(db);
                break;
                
            case 2:
                add_visitor(db);
                break;
                
            case 3:
                printf("Введите ID посетителя для удаления: ");
                if (scanf("%d", &id_input) == 1) {
                    delete_visitor(db, id_input);
                } else {
                    printf("Неверный ID\n");
                }
                clear_input_buffer();
                break;
                
            case 4:
                printf("ID посетителя для редактирования: ");
                if (scanf("%d", &id_input) == 1) {
                    clear_input_buffer();  // ОЧИСТКА БУФЕРА ПЕРЕД edit_visitor
                    edit_visitor(db, id_input);
                } else {
                    printf("Неверный ID\n");
                    clear_input_buffer();
                }
                break;
                
            case 5:
                search_menu(db);
                break;
                
            case 6:
                show_statistics(db);
                break;
                
            case 7:
                save_data(db, DATA_FILE);
                printf("Данные сохранены\n");
                break;
                
            case 8:
                printf("Выход\n");
                break;
                
            default:
                printf("Неверный выбор\n");
        }
        
        if (choice != 8) wait_for_enter();
        
    } while (choice != 8);
    
    save_data(db, DATA_FILE);
    free_database(db);
    
    printf("Программа завершена\n");
    return 0;
}

void print_menu(void) {
    printf("\nГлавное меню:\n");
    printf("1. Показать всех посетителей\n");
    printf("2. Добавить посетителя\n");
    printf("3. Удалить посетителя\n");
    printf("4. Редактировать посетителя\n");
    printf("5. Поиск\n");
    printf("6. Статистика\n");
    printf("7. Сохранить\n");
    printf("8. Выйти\n");
}

void search_menu(Database *db) {
    int choice;
    
    printf("\nПоиск:\n");
    printf("1. По имени посетителя\n");
    printf("2. По имени кота\n");
    printf("3. По напитку\n");
    printf("4. Назад\n");
    printf("Выберите: ");
    
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    switch (choice) {
        case 1:
            search_by_name(db);
            break;
        case 2:
            search_by_cat(db);
            break;
        case 3:
            search_by_drink(db);
            break;
        case 4:
            return;
        default:
            printf("Неверный выбор\n");
    }
}

void wait_for_enter(void) {
    printf("Нажмите Enter...");
    getchar();
}
