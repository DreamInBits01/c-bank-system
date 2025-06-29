#include <stdio.h>
#include <string.h>
// read out from the file, write into file
#define READ_USER_FROM_FILE "name:%[^,], password:%[^,], age:%d\n"
#define READ_USERNAME_FROM_FILE "name:%[^,],"
#define WRITE_INTO_FILE "name:%s, password:%s, age:%d\n"
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
Person get_user_info(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("users.txt", "r");
    Person person;
    if (file == NULL)
    {
        printf("Error while opening the file (get_user_info)");
        return person;
    };
    int fscanf_result;
    fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age);
    while (fscanf_result == 3)
    {
        if (strcmp(person.name, username) == 0)
        {
            break;
        };
        fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age);
    };
    fclose(file);
    return person;
};
int does_user_exist(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error While opening the file...\n");
        return 0;
    }
    int found = 0;
    Person person = get_user_info(username);
    if (strcmp(person.name, username) == 0)
    {
        found = 1;
    };
    fclose(file);
    return found;
}
void save_user(const Person const *person)
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("Error while saving the user...\n");
        return;
    };
    int does_user_exist_result = does_user_exist(person->name);
    if (does_user_exist_result)
    {
        printf("Username is already taken\n");
        return;
    }
    fprintf(file, WRITE_INTO_FILE, person->name, person->password, person->age);
    printf("User is saved successfuly\n");
    fclose(file);
};
void main()
{
    Person person = create_user();
    printf("Added person -> %s, %s, %d\n", person.name, person.password, person.age);
    save_user(&person);
    Person founded = get_user_info(person.name);
    printf("founded %s", founded.name);
}
