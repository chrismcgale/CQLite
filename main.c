#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input.h"
#include "table.h"
#include "statement.h"
#include "meta.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Must supply a database name\n");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];
  Table* table = db_open(filename);

  if (table == NULL) {
    printf("Error: table is NULL\n");
    exit(EXIT_FAILURE);
  }

  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
        switch (do_meta_command(input_buffer, table)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED):
                printf("Unrecognized command '%s'\n", input_buffer->buffer);
                continue;
        }
    }


    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_NEGATIVE_ID):
        printf("ID must be positive.\n");
        continue;
      case (PREPARE_STRING_TOO_LONG):
        printf("String is too long.\n");
        continue;
      case (PREPARE_SYNTAX_ERROR):
        printf("Syntax error. Could not parse statement.\n");
        continue;
      case (PREPARE_UNRECOGNIZED):
        printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
        continue;
    }
    switch (execute_statement(&statement, table)) {
      case (EXECUTE_SUCCESS):
        printf("Executed.\n");
        break;
      case (EXECUTE_TABLE_FULL):
        printf("Error: Table full.\n");
        break;
      case (EXECUTE_UNKNOWN_STATEMENT):
        printf("Error: Statement not recognized.\n");
        break;
      default:
        printf("Unknown error.\n");
        break;
    }
  }
}