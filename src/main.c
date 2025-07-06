#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
// read out from the file, write into file
#define READ_USER_FROM_FILE "name:%[^,], password:%[^,], age:%d\n"
#define READ_USERNAME_FROM_FILE "name:%[^,],"
#define WRITE_USER_INTO_FILE "name:%s, password:%s, age:%d\n"
#define USERNAME_BUFFER 31
#define PASSWORD_BUFFER 51
typedef struct
{
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    int age;
} Person;
typedef struct
{
    Person person;
    bool is_valid;
} AuthResult;
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
        printf("Enter a name %s time!\n", display_name_buffer);
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
        printf("Warning: %s was truncated\n", display_name_buffer);
        // Clear remaining input from stdin
        flush_stdin();
    };
    if (written_length > 0 && *last_char_in_field == '\n')
    {
        *last_char_in_field = '\0';
    };
    return true;
}
AuthResult create_user()
{
    flush_stdin();
    AuthResult register_result;
    register_result.person.age = 205;
    bool write_name_result = write_field_prompt(register_result.person.name, "name", USERNAME_BUFFER, 5);
    bool write_password_result = write_field_prompt(register_result.person.password, "password", PASSWORD_BUFFER, 9);
    if (!write_name_result || !write_password_result)
    {
        register_result.is_valid = false;
    }
    return register_result;
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
bool does_user_exist(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error While opening the file...\n");
        return 0;
    }
    bool found = false;
    Person person = get_user_info(username);
    if (strcmp(person.name, username) == 0)
    {
        found = true;
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
    fprintf(file, WRITE_USER_INTO_FILE, person->name, person->password, person->age);
    printf("User is saved successfuly\n");
    fclose(file);
};
AuthResult login(char username[USERNAME_BUFFER], char password[PASSWORD_BUFFER])
{
    AuthResult login;
    login.person = get_user_info(username);
    int success = 0;
    if (strcmp(login.person.password, password) == 0)
    {
        login.is_valid = true;
    }
    else
    {
        login.is_valid = false;
    };
    return login;
}

int main()
{
    int keep_running = true;
    char option;
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    printf("Welcome to the bank system\n");
    while (keep_running)
    {
        printf("----OPTIONS----\n");
        printf("----L for Login----\n");
        printf("----R for Register----\n");
        printf("----D for Deposit----\n");
        printf("----T for Transfer----\n");
        printf("----D for Withdraw----\n");
        printf("----Q for Quit----\n");
        scanf(" %c", &option);

        switch (option)
        {
        case 'L':
            printf("----Login was selected----\n");
            flush_stdin();
            write_field_prompt(name, "name", USERNAME_BUFFER, 5);
            write_field_prompt(password, "password", PASSWORD_BUFFER, 9);
            AuthResult login_result = login(name, password);
            if (login_result.is_valid)
            {
                printf("Logged in successfuly with the credentials (name:%s, password:%s)\n", name, password);
            }
            else
            {
                printf("Error while logging in, please check your credentials (name:%s, password:%s)\n", name, password);
            }
            break;
        case 'R':
            printf("----Register was selected----\n");
            AuthResult create_user_result = create_user();
            if (create_user_result.is_valid)
            {
                save_user(&create_user_result.person);
            }
            else
            {
                printf("Error while creating a user!\n");
            };
            break;
        case 'Q':
            keep_running = false;
            exit(0);
        default:
            printf("Please select a valid option\n");
            break;
        }
    }
}
