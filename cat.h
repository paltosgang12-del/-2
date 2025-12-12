#ifndef CAT_H
#define CAT_H

#include <stdbool.h>

#define MAX_NAME 50
#define MAX_CAT_NAME 35
#define MAX_DRINK 25
#define START_SIZE 5
#define GROW_BY 4

typedef struct Visitor {
    int id;
    char name[MAX_NAME];
    char cat_name[MAX_CAT_NAME];
    int minutes;
    float money;
    char drink[MAX_DRINK];
    int is_regular;
} Visitor;

typedef struct Database {
    Visitor *visitors;
    int count;
    int capacity;
    int next_id;
} Database;

Database* create_database(void);
void free_database(Database *db);
void load_data(Database *db, const char *filename);
void save_data(const Database *db, const char *filename);
void show_all(const Database *db);
void add_visitor(Database *db);
int delete_visitor(Database *db, int id);
int edit_visitor(Database *db, int id);
int find_by_id(const Database *db, int id);
void search_by_name(const Database *db);
void search_by_cat(const Database *db);
void search_by_drink(const Database *db);
void show_statistics(const Database *db);
void clear_input_buffer(void);

#endif
