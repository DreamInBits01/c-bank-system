#include "utils.h"
#include "auth.h"
#include "error_messages.h"
#include "success_messages.h"
#include "printf_macros.h"
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
        PRINT_ERROR(USER_NOT_FOUND);
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
    int does_user_exist_result = does_user_exist(person->name);
    if (does_user_exist_result)
    {

        PRINT_ERROR(USERNAME_TAKEN);
        return;
    }
    FILE *file = fopen("db/users.txt", "a");
    if (file == NULL)
    {
        PRINT_ERROR(SAVE_USER_ERROR);
        return;
    };
    fprintf(file, WRITE_USER, person->name, person->password, person->age, 0);
    PRINT_SUCCESS(USER_SAVED);
    fclose(file);
};
bool logout(char *username, char *password, bool is_user_logged_in)
{
    if (!is_user_logged_in)
    {
        PRINT_ERROR(USER_NOT_LOGGED_IN_ERROR);
        return false;
    }
    while (*username)
    {
        *username = 0;
        username++;
    }
    while (*password)
    {
        *password = 0;
        password++;
    };
    PRINT_SUCCESS(USER_LOGGED_OUT);
    return true;
}