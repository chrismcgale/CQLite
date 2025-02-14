#ifndef CURSOR_H
#define CURSOR_H

#include "table.h"
#include "node.h"
#include <stdbool.h>


typedef struct {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

void* get_page(Pager* pager, uint32_t page_num);
Cursor* table_start(Table* table);
Cursor* table_find(Table* table, uint32_t key);

void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif