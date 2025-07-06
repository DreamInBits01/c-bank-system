#ifndef UTILS_H
#define UTILS_H
#define READ_USER_FROM_FILE "name:%[^,], password:%[^,], age:%d\n"
#define READ_USERNAME_FROM_FILE "name:%[^,],"
#define WRITE_USER_INTO_FILE "name:%s, password:%s, age:%d\n"
#define USERNAME_BUFFER 31
#define PASSWORD_BUFFER 51
#include <stdio.h>
#include <stdbool.h>
void flush_stdin();
bool write_field_prompt(
    char *field_content,            // The actual field data
    const char *field_display_name, // Human-readable field name
    size_t max_field_length,        // Maximum length for the field
    size_t display_name_buffer_size // Size of the name buffer
);
#endif
