#include "utils.h"
#include "auth.h"
AuthResult login(char username[USERNAME_BUFFER], char password[PASSWORD_BUFFER])
{
    AuthResult login;
    login.person = get_user_info(username);
    if (strcmp(login.person.password, password) == 0)
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
    AuthResult register_result;
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