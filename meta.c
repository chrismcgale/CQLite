#include "meta.h"
#include <string.h>

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table *table) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    close_input_buffer(input_buffer);
    db_close(table);
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED;
  }
}