#include "utils.h"
#include "auth.h"
AuthResult login(char username[USERNAME_BUFFER], char password[PASSWORD_BUFFER])
{
    AuthResult login = {0};
    login.person = get_user_info(username);
    if (strcmp(login.person.name, username) == 0 && strcmp(login.person.password, password) == 0)
    {
        login.is_valid = true;
    }
    else
    {
        login.is_valid = false;
    };
    return login;
};
AuthResult create_user()
{
    flush_stdin();
    AuthResult register_result = {0};
    register_result.person.age = 205;
    bool write_name_result = write_field_prompt(register_result.person.name, "name", USERNAME_BUFFER, 5);
    bool write_password_result = write_field_prompt(register_result.person.password, "password", PASSWORD_BUFFER, 9);
    if (!write_name_result || !write_password_result)
    {
        register_result.is_valid = false;
    }
    else
    {
        register_result.is_valid = true;
    }
    return register_result;
};
void save_user(const Person *person)
{
    FILE *file = fopen("db/users.txt", "a");
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
    fprintf(file, WRITE_USER, person->name, person->password, person->age, 0);
    printf("User is saved successfuly\n");
    fclose(file);
};