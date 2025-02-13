#ifndef STATEMENT_H
#define STATEMENT_H

#include "table.h"
#include "input.h"

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG
} PrepareResult;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_UNKNOWN_STATEMENT
} ExecuteResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
ExecuteResult execute_statement(Statement* statement, Table* table);

#endif