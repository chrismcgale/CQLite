#ifndef META_H
#define META_H

#include "input.h"
#include "table.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

#endif