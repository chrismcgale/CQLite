#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"


typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;


uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void print_constants();
void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level);
void initialize_leaf_node(void* node);

NodeType get_node_type(void* node);
void set_node_type(void* node, NodeType type);

uint32_t* internal_node_num_keys(void* node);
uint32_t* internal_node_right_child(void* node);
uint32_t* internal_node_cell(void* node, uint32_t cell_num);
uint32_t* internal_node_child(void* node, uint32_t child_num);
uint32_t* internal_node_key(void* node, uint32_t key_num);
uint32_t get_node_max_key(void* node);

bool is_node_root(void* node);
void set_node_root(void* node, bool is_root);

#endif