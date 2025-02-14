#include "table.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)


// Calculate sizes based on Row structure
#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)


#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)


/*
Common Node Header Layout
 */
#define NODE_TYPE_SIZE sizeof(uint8_t)
#define NODE_TYPE_OFFSET 0
#define IS_ROOT_SIZE sizeof(uint8_t)
#define IS_ROOT_OFFSET NODE_TYPE_SIZE
#define PARENT_POINTER_SIZE sizeof(uint32_t)
#define PARENT_POINTER_OFFSET IS_ROOT_OFFSET + IS_ROOT_SIZE
#define COMMON_NODE_HEADER_SIZE NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE


/* Leaf Node Header Layout*/
#define LEAF_NODE_NUM_CELLS_SIZE sizeof(uint32_t)
#define LEAF_NODE_NUM_CELLS_OFFSET COMMON_NODE_HEADER_SIZE
#define LEAF_NODE_HEADER_SIZE COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE

/*
 * Leaf Node Body Layout
 */
#define LEAF_NODE_KEY_SIZE sizeof(uint32_t)
#define LEAF_NODE_KEY_OFFSET 0
#define LEAF_NODE_VALUE_SIZE ROW_SIZE
#define LEAF_NODE_VALUE_OFFSET LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE
#define LEAF_NODE_CELL_SIZE LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE
#define LEAF_NODE_SPACE_FOR_CELLS PAGE_SIZE - LEAF_NODE_HEADER_SIZE
#define LEAF_NODE_MAX_CELLS LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE

