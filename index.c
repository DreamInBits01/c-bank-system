#include <stdio.h>
#include <string.h>
// read out from the file, write into file
#define READ_FROM_FILE "(name:%[^,], password:%[^,], age:%d)"
#define WRITE_INTO_FILE "(name:%s, password:%s, age:%d)\n"
#define USERNAME_BUFFER 31
#define PASSWORD_BUFFER 51
int option;
typedef struct
{
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    int age;
} Person;
void write_field_prompt(
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
        printf("Enter a name %s time!\n", display_name_buffer);
        *field_content = '\0';
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
        printf("Warning: Field was truncated\n");
        // Clear remaining input from stdin
        int c = getchar();
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        };
    };
    if (written_length > 0 && *last_char_in_field == '\n')
    {
        *last_char_in_field = '\0';
    };
}
Person create_user()
{
    Person person;
    person.age = 205;
    write_field_prompt(person.name, "name", USERNAME_BUFFER, 5);
    write_field_prompt(person.password, "password", PASSWORD_BUFFER, 9);
    return person;
};
Person find_user(char username[USERNAME_BUFFER])
{
    FILE *file = fopen("people.txt", "r\n");
    if (file == NULL)
    {
        perror("\nError While opening the file...\n");
    }
    Person result;
    fscanf(file, READ_FROM_FILE, result.name, &result.age);
    fclose(file);
    return result;
};
void save_user(const Person const *person)
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("Error while saving the user...\n");
        return;
    };
    fprintf(file, WRITE_INTO_FILE, person->name, person->password, person->age);
    printf("User is saved successfuly\n");
    fclose(file);
};
void main()
{
    Person person = create_user();
    printf("Added person -> %s, %s, %d", person.name, person.password, person.age);
    save_user(&person);
}
