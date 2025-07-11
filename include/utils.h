#ifndef UTILS_H
#define UTILS_H
#define READ_USER "name:%[^,], password:%[^,], age:%d, amount:%d"
#define WRITE_USER "name:%s, password:%s, age:%d, amount:%d\n"
#define READ_TRANSACTION "from:%[^,], to:%[^,], amount:%d, date:%[^,]"
#define WRITE_TRANSACTION "from:%s, to:%s, amount:%d, date:%s\n"
#define USERNAME_BUFFER 31
#define PASSWORD_BUFFER 51
#define USER_FIELDS_NUMBER 4
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void flush_stdin();
bool write_field_prompt(
    char *field_content,            // The actual field data
    const char *field_display_name, // Human-readable field name
    size_t max_field_length,        // Maximum length for the field
    size_t display_name_buffer_size // Size of the name buffer
);
#endif
