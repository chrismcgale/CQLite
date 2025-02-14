#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <stdio.h>
#include "constants.h"

uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void print_constants();
void print_leaf_node(void* node);
void initialize_leaf_node(void* node);

#endif