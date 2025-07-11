#include "utils.h"
#include "printf_macros.h"
void flush_stdin()
{
    int c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    };
}
bool write_field_prompt(
    char *field_content,            // The actual field data
    const char *field_display_name, // Human-readable field name
    size_t max_field_length,        // Maximum length for the field
    size_t display_name_buffer_size // Size of the name buffer
)
{
    char display_name_buffer[display_name_buffer_size];
    strncpy(display_name_buffer, field_display_name, display_name_buffer_size);
    display_name_buffer[display_name_buffer_size - 1] = '\0';
    printf("\nEnter a %s (max %zu characters)\n", display_name_buffer, max_field_length - 1);

    char *fgets_field;
    fgets_field = fgets(field_content, max_field_length, stdin);
    if (fgets_field == NULL)
    {
        // User didn't enter a value;
        PRINT_ERROR("Enter a name %s next time!\n", display_name_buffer);
        *field_content = '\0';
        return false;
    };
    size_t written_length = strlen(field_content);
    char *last_char_in_field;
    while (*field_content)
    {
        last_char_in_field = field_content;
        field_content++;
    }
    if (written_length == max_field_length - 1 && *last_char_in_field != '\n')
    {
        // User wrote characters bigger than the buffer so there are characters left in the std input
        // that could affect the next input
        PRINT_WARRNING("Warning: %s was truncated\n", display_name_buffer);
        // Clear remaining input from stdin
        flush_stdin();
    };
    if (written_length > 0 && *last_char_in_field == '\n')
    {
        *last_char_in_field = '\0';
    };
    return true;
}
bool user_logged_in(char *username)
{
    if (*username != '\0')
    {
        return true;
    }
    else
        return false;
}
bool user_not_logged_in(char *username)
{
    if (*username == '\0')
    {
        return true;
    }
    else
        return false;
}
